#include "course_6_2_2_2_ibl_specular_textured.h"
#include <QDir>
#include <QDebug>
#include "stb_image.h"

Course_6_2_2_2_ibl_specular_textured::Course_6_2_2_2_ibl_specular_textured()
    :CourseWithCamera()
    ,sphereVAO(0)
    ,cubeVAO(0)
    ,cubeVBO(0)
    ,quadVAO(0)
{
    initializeOpenGLFunctions();
}

Course_6_2_2_2_ibl_specular_textured::~Course_6_2_2_2_ibl_specular_textured()
{
    glDepthFunc(GL_LESS);
    glDisable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
    glDeleteTextures(1,&ironAlbedoMap);
    glDeleteTextures(1,&ironNormalMap);
    glDeleteTextures(1,&ironMetallicMap);
    glDeleteTextures(1,&ironRoughnessMap);
    glDeleteTextures(1,&ironAOMap);

    glDeleteTextures(1,&goldAlbedoMap);
    glDeleteTextures(1,&goldNormalMap);
    glDeleteTextures(1,&goldMetallicMap);
    glDeleteTextures(1,&goldRoughnessMap);
    glDeleteTextures(1,&goldAOMap);

    glDeleteTextures(1,&grassAlbedoMap);
    glDeleteTextures(1,&grassNormalMap);
    glDeleteTextures(1,&grassMetallicMap);
    glDeleteTextures(1,&grassRoughnessMap);
    glDeleteTextures(1,&grassAOMap);

    glDeleteTextures(1,&plasticAlbedoMap);
    glDeleteTextures(1,&plasticNormalMap);
    glDeleteTextures(1,&plasticMetallicMap);
    glDeleteTextures(1,&plasticRoughnessMap);
    glDeleteTextures(1,&plasticAOMap);

    glDeleteTextures(1,&wallAlbedoMap);
    glDeleteTextures(1,&wallNormalMap);
    glDeleteTextures(1,&wallMetallicMap);
    glDeleteTextures(1,&wallRoughnessMap);
    glDeleteTextures(1,&wallAOMap);

    glDeleteFramebuffers(1, &captureFBO);
    glDeleteRenderbuffers(1, &captureRBO);
    glDeleteTextures(1, &hdrTexture);
    glDeleteTextures(1, &envCubemap);
    glDeleteTextures(1, &irradianceMap);

    glDeleteVertexArrays(1, &sphereVAO);
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &ebo);
    glDeleteVertexArrays(1, &cubeVAO);
    glDeleteBuffers(1, &cubeVBO);
}

void Course_6_2_2_2_ibl_specular_textured::init(GlWindow *glWindow)
{
    setGlWindow(glWindow);
    glEnable(GL_DEPTH_TEST);
    // set depth function to less than AND equal for skybox depth trick.
    glDepthFunc(GL_LEQUAL);
    // enable seamless cubemap sampling for lower mip levels in the pre-filter map.
    glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);

    QString shaderPath = QDir::currentPath() + "/shaders/6.pbr/2.2.2.ibl_specular_textured/";
    pbrShader.addShaderFromSourceFile(QOpenGLShader::Vertex,shaderPath+"2.2.2.pbr.vs");
    pbrShader.addShaderFromSourceFile(QOpenGLShader::Fragment,shaderPath+"2.2.2.pbr.fs");
    pbrShader.link();
    equirectangularToCubemapShader.addShaderFromSourceFile(QOpenGLShader::Vertex,shaderPath+"2.2.2.cubemap.vs");
    equirectangularToCubemapShader.addShaderFromSourceFile(QOpenGLShader::Fragment,shaderPath+"2.2.2.equirectangular_to_cubemap.fs");
    equirectangularToCubemapShader.link();
    irradianceShader.addShaderFromSourceFile(QOpenGLShader::Vertex,shaderPath+"2.2.2.cubemap.vs");
    irradianceShader.addShaderFromSourceFile(QOpenGLShader::Fragment,shaderPath+"2.2.2.irradiance_convolution.fs");
    irradianceShader.link();
    prefilterShader.addShaderFromSourceFile(QOpenGLShader::Vertex,shaderPath+"2.2.2.cubemap.vs");
    prefilterShader.addShaderFromSourceFile(QOpenGLShader::Fragment,shaderPath+"2.2.2.prefilter.fs");
    prefilterShader.link();
    brdfShader.addShaderFromSourceFile(QOpenGLShader::Vertex,shaderPath+"2.2.2.brdf.vs");
    brdfShader.addShaderFromSourceFile(QOpenGLShader::Fragment,shaderPath+"2.2.2.brdf.fs");
    brdfShader.link();
    backgroundShader.addShaderFromSourceFile(QOpenGLShader::Vertex,shaderPath+"2.2.2.background.vs");
    backgroundShader.addShaderFromSourceFile(QOpenGLShader::Fragment,shaderPath+"2.2.2.background.fs");
    backgroundShader.link();

    pbrShader.bind();
    pbrShader.setUniformValue("irradianceMap", 0);
    pbrShader.setUniformValue("prefilterMap", 1);
    pbrShader.setUniformValue("brdfLUT", 2);
    pbrShader.setUniformValue("albedoMap", 3);
    pbrShader.setUniformValue("normalMap", 4);
    pbrShader.setUniformValue("metallicMap", 5);
    pbrShader.setUniformValue("roughnessMap", 6);
    pbrShader.setUniformValue("aoMap", 7);

    backgroundShader.bind();
    backgroundShader.setUniformValue("environmentMap", 0);

    QString path = QDir::currentPath() + "/resources/textures/pbr/rusted_iron/albedo.png";
    ironAlbedoMap = loadTexture(path.toStdString().c_str());
    path = QDir::currentPath() + "/resources/textures/pbr/rusted_iron/normal.png";
    ironNormalMap = loadTexture(path.toStdString().c_str());
    path = QDir::currentPath() + "/resources/textures/pbr/rusted_iron/metallic.png";
    ironMetallicMap = loadTexture(path.toStdString().c_str());
    path = QDir::currentPath() + "/resources/textures/pbr/rusted_iron/roughness.png";
    ironRoughnessMap = loadTexture(path.toStdString().c_str());
    path = QDir::currentPath() + "/resources/textures/pbr/rusted_iron/ao.png";
    ironAOMap = loadTexture(path.toStdString().c_str());

    path = QDir::currentPath() + "/resources/textures/pbr/gold/albedo.png";
    goldAlbedoMap = loadTexture(path.toStdString().c_str());
    path = QDir::currentPath() + "/resources/textures/pbr/gold/normal.png";
    goldNormalMap = loadTexture(path.toStdString().c_str());
    path = QDir::currentPath() + "/resources/textures/pbr/gold/metallic.png";
    goldMetallicMap = loadTexture(path.toStdString().c_str());
    path = QDir::currentPath() + "/resources/textures/pbr/gold/roughness.png";
    goldRoughnessMap = loadTexture(path.toStdString().c_str());
    path = QDir::currentPath() + "/resources/textures/pbr/gold/ao.png";
    goldAOMap = loadTexture(path.toStdString().c_str());

    path = QDir::currentPath() + "/resources/textures/pbr/grass/albedo.png";
    grassAlbedoMap = loadTexture(path.toStdString().c_str());
    path = QDir::currentPath() + "/resources/textures/pbr/grass/normal.png";
    grassNormalMap = loadTexture(path.toStdString().c_str());
    path = QDir::currentPath() + "/resources/textures/pbr/grass/metallic.png";
    grassMetallicMap = loadTexture(path.toStdString().c_str());
    path = QDir::currentPath() + "/resources/textures/pbr/grass/roughness.png";
    grassRoughnessMap = loadTexture(path.toStdString().c_str());
    path = QDir::currentPath() + "/resources/textures/pbr/grass/ao.png";
    grassAOMap = loadTexture(path.toStdString().c_str());

    path = QDir::currentPath() + "/resources/textures/pbr/plastic/albedo.png";
    plasticAlbedoMap = loadTexture(path.toStdString().c_str());
    path = QDir::currentPath() + "/resources/textures/pbr/plastic/normal.png";
    plasticNormalMap = loadTexture(path.toStdString().c_str());
    path = QDir::currentPath() + "/resources/textures/pbr/plastic/metallic.png";
    plasticMetallicMap = loadTexture(path.toStdString().c_str());
    path = QDir::currentPath() + "/resources/textures/pbr/plastic/roughness.png";
    plasticRoughnessMap = loadTexture(path.toStdString().c_str());
    path = QDir::currentPath() + "/resources/textures/pbr/plastic/ao.png";
    plasticAOMap = loadTexture(path.toStdString().c_str());

    path = QDir::currentPath() + "/resources/textures/pbr/wall/albedo.png";
    wallAlbedoMap = loadTexture(path.toStdString().c_str());
    path = QDir::currentPath() + "/resources/textures/pbr/wall/normal.png";
    wallNormalMap = loadTexture(path.toStdString().c_str());
    path = QDir::currentPath() + "/resources/textures/pbr/wall/metallic.png";
    wallMetallicMap = loadTexture(path.toStdString().c_str());
    path = QDir::currentPath() + "/resources/textures/pbr/wall/roughness.png";
    wallRoughnessMap = loadTexture(path.toStdString().c_str());
    path = QDir::currentPath() + "/resources/textures/pbr/wall/ao.png";
    wallAOMap = loadTexture(path.toStdString().c_str());

    lightPositions.push_back(QVector3D(-10.0f,  10.0f, 10.0f));
    lightPositions.push_back(QVector3D( 10.0f,  10.0f, 10.0f));
    lightPositions.push_back(QVector3D(-10.0f, -10.0f, 10.0f));
    lightPositions.push_back(QVector3D( 10.0f, -10.0f, 10.0f));

    lightColors.push_back(QVector3D(300.0f, 300.0f, 300.0f));
    lightColors.push_back(QVector3D(300.0f, 300.0f, 300.0f));
    lightColors.push_back(QVector3D(300.0f, 300.0f, 300.0f));
    lightColors.push_back(QVector3D(300.0f, 300.0f, 300.0f));

    // pbr: setup framebuffer
    // ----------------------
    glGenFramebuffers(1, &captureFBO);
    glGenRenderbuffers(1, &captureRBO);

    glBindFramebuffer(GL_FRAMEBUFFER, captureFBO);
    glBindRenderbuffer(GL_RENDERBUFFER, captureRBO);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, 512, 512);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, captureRBO);

    // pbr: load the HDR environment map
    // ---------------------------------
    stbi_set_flip_vertically_on_load(true);
    int width, height, nrComponents;
    path = QDir::currentPath() + "/resources/textures/hdr/newport_loft.hdr";
    float *data = stbi_loadf(path.toStdString().c_str(), &width, &height, &nrComponents, 0);
    unsigned int hdrTexture;
    if (data)
    {
        glGenTextures(1, &hdrTexture);
        glBindTexture(GL_TEXTURE_2D, hdrTexture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, width, height, 0, GL_RGB, GL_FLOAT, data); // note how we specify the texture's data value to be float

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    }
    else
    {
        qDebug() << "Failed to load HDR image.";
    }
    // pbr: setup cubemap to render to and attach to framebuffer
    // ---------------------------------------------------------
    glGenTextures(1, &envCubemap);
    glBindTexture(GL_TEXTURE_CUBE_MAP, envCubemap);
    for (unsigned int i = 0; i < 6; ++i)
    {
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB16F, 512, 512, 0, GL_RGB, GL_FLOAT, nullptr);
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR); // enable pre-filter mipmap sampling (combatting visible dots artifact)
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // pbr: set up projection and view matrices for capturing data onto the 6 cubemap face directions
    // ----------------------------------------------------------------------------------------------
    QMatrix4x4 captureProjection;
    captureProjection.perspective(90.0f, 1.0f, 0.1f, 10.0f);
    QVector<QMatrix4x4> captureViews;
    QMatrix4x4 temp;
    temp.setToIdentity();
    temp.lookAt(QVector3D(0.0f, 0.0f, 0.0f), QVector3D( 1.0f,  0.0f,  0.0f), QVector3D(0.0f, -1.0f,  0.0f));
    captureViews.push_back(temp);
    temp.setToIdentity();
    temp.lookAt(QVector3D(0.0f, 0.0f, 0.0f), QVector3D(-1.0f,  0.0f,  0.0f), QVector3D(0.0f, -1.0f,  0.0f));
    captureViews.push_back(temp);
    temp.setToIdentity();
    temp.lookAt(QVector3D(0.0f, 0.0f, 0.0f), QVector3D( 0.0f,  1.0f,  0.0f), QVector3D(0.0f,  0.0f,  1.0f));
    captureViews.push_back(temp);
    temp.setToIdentity();
    temp.lookAt(QVector3D(0.0f, 0.0f, 0.0f), QVector3D( 0.0f, -1.0f,  0.0f), QVector3D(0.0f,  0.0f, -1.0f));
    captureViews.push_back(temp);
    temp.setToIdentity();
    temp.lookAt(QVector3D(0.0f, 0.0f, 0.0f), QVector3D( 0.0f,  0.0f,  1.0f), QVector3D(0.0f, -1.0f,  0.0f));
    captureViews.push_back(temp);
    temp.setToIdentity();
    temp.lookAt(QVector3D(0.0f, 0.0f, 0.0f), QVector3D( 0.0f,  0.0f, -1.0f), QVector3D(0.0f, -1.0f,  0.0f));
    captureViews.push_back(temp);
    // pbr: convert HDR equirectangular environment map to cubemap equivalent
    // ----------------------------------------------------------------------
    equirectangularToCubemapShader.bind();
    equirectangularToCubemapShader.setUniformValue("equirectangularMap", 0);
    equirectangularToCubemapShader.setUniformValue("projection", captureProjection);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, hdrTexture);

    glViewport(0, 0, 512, 512); // don't forget to configure the viewport to the capture dimensions.
    glBindFramebuffer(GL_FRAMEBUFFER, captureFBO);
    for (unsigned int i = 0; i < 6; ++i)
    {
        equirectangularToCubemapShader.setUniformValue("view", captureViews[i]);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, envCubemap, 0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        renderCube();
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    // then let OpenGL generate mipmaps from first mip face (combatting visible dots artifact)
    glBindTexture(GL_TEXTURE_CUBE_MAP, envCubemap);
    glGenerateMipmap(GL_TEXTURE_CUBE_MAP);
    // pbr: create an irradiance cubemap, and re-scale capture FBO to irradiance scale.
    // --------------------------------------------------------------------------------
    glGenTextures(1, &irradianceMap);
    glBindTexture(GL_TEXTURE_CUBE_MAP, irradianceMap);
    for (unsigned int i = 0; i < 6; ++i)
    {
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB16F, 32, 32, 0, GL_RGB, GL_FLOAT, nullptr);
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glBindFramebuffer(GL_FRAMEBUFFER, captureFBO);
    glBindRenderbuffer(GL_RENDERBUFFER, captureRBO);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, 32, 32);
    // pbr: solve diffuse integral by convolution to create an irradiance (cube)map.
    // -----------------------------------------------------------------------------
    irradianceShader.bind();
    irradianceShader.setUniformValue("environmentMap", 0);
    irradianceShader.setUniformValue("projection", captureProjection);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, envCubemap);

    glViewport(0, 0, 32, 32); // don't forget to configure the viewport to the capture dimensions.
    glBindFramebuffer(GL_FRAMEBUFFER, captureFBO);
    for (unsigned int i = 0; i < 6; ++i)
    {
        irradianceShader.setUniformValue("view", captureViews[i]);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, irradianceMap, 0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        renderCube();
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    // pbr: create a pre-filter cubemap, and re-scale capture FBO to pre-filter scale.
    // --------------------------------------------------------------------------------
    glGenTextures(1, &prefilterMap);
    glBindTexture(GL_TEXTURE_CUBE_MAP, prefilterMap);
    for (unsigned int i = 0; i < 6; ++i)
    {
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB16F, 128, 128, 0, GL_RGB, GL_FLOAT, nullptr);
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR); // be sure to set minifcation filter to mip_linear
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // generate mipmaps for the cubemap so OpenGL automatically allocates the required memory.
    glGenerateMipmap(GL_TEXTURE_CUBE_MAP);
    // pbr: run a quasi monte-carlo simulation on the environment lighting to create a prefilter (cube)map.
    // ----------------------------------------------------------------------------------------------------
    prefilterShader.bind();
    prefilterShader.setUniformValue("environmentMap", 0);
    prefilterShader.setUniformValue("projection", captureProjection);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, envCubemap);

    glBindFramebuffer(GL_FRAMEBUFFER, captureFBO);
    unsigned int maxMipLevels = 5;
    for (unsigned int mip = 0; mip < maxMipLevels; ++mip)
    {
        // reisze framebuffer according to mip-level size.
        unsigned int mipWidth  = 128 * std::pow(0.5, mip);
        unsigned int mipHeight = 128 * std::pow(0.5, mip);
        glBindRenderbuffer(GL_RENDERBUFFER, captureRBO);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, mipWidth, mipHeight);
        glViewport(0, 0, mipWidth, mipHeight);

        float roughness = (float)mip / (float)(maxMipLevels - 1);
        prefilterShader.setUniformValue("roughness", roughness);
        for (unsigned int i = 0; i < 6; ++i)
        {
            prefilterShader.setUniformValue("view", captureViews[i]);
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, prefilterMap, mip);

            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            renderCube();
        }
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    // pbr: generate a 2D LUT from the BRDF equations used.
    // ----------------------------------------------------
    glGenTextures(1, &brdfLUTTexture);

    // pre-allocate enough memory for the LUT texture.
    glBindTexture(GL_TEXTURE_2D, brdfLUTTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RG16F, 512, 512, 0, GL_RG, GL_FLOAT, 0);
    // be sure to set wrapping mode to GL_CLAMP_TO_EDGE
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // then re-configure capture framebuffer object and render screen-space quad with BRDF shader.
    glBindFramebuffer(GL_FRAMEBUFFER, captureFBO);
    glBindRenderbuffer(GL_RENDERBUFFER, captureRBO);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, 512, 512);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, brdfLUTTexture, 0);

    glViewport(0, 0, 512, 512);
    brdfShader.bind();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    renderQuad();

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    // initialize static shader uniforms before rendering
    // --------------------------------------------------
    QMatrix4x4 projection;
    projection.perspective(mCamera.Zoom, 800/600, 0.1f, 100.0f);
    pbrShader.bind();
    pbrShader.setUniformValue("projection", projection);
    backgroundShader.bind();
    backgroundShader.setUniformValue("projection", projection);

    // then before rendering, configure the viewport to the original framebuffer's screen dimensions
    SCR_WIDTH = 0;
    SCR_HEIGHT = 0;
    QSize size = contextSize();
    if (size.width() > 0)
        SCR_WIDTH = size.width();
    if (size.height() > 0)
        SCR_HEIGHT = size.height();
    glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);

    stbi_set_flip_vertically_on_load(false);
}

void Course_6_2_2_2_ibl_specular_textured::render()
{
    Course::render();

    processInput();

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // render scene, supplying the convoluted irradiance map to the final shader.
    // ------------------------------------------------------------------------------------------
    pbrShader.bind();
    QMatrix4x4 model;
    QMatrix4x4 view = mCamera.GetViewMatrix();
    pbrShader.setUniformValue("view", view);
    pbrShader.setUniformValue("camPos", mCamera.Position);

    // bind pre-computed IBL data
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, irradianceMap);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_CUBE_MAP, prefilterMap);
    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, brdfLUTTexture);

    // rusted iron
    glActiveTexture(GL_TEXTURE3);
    glBindTexture(GL_TEXTURE_2D, ironAlbedoMap);
    glActiveTexture(GL_TEXTURE4);
    glBindTexture(GL_TEXTURE_2D, ironNormalMap);
    glActiveTexture(GL_TEXTURE5);
    glBindTexture(GL_TEXTURE_2D, ironMetallicMap);
    glActiveTexture(GL_TEXTURE6);
    glBindTexture(GL_TEXTURE_2D, ironRoughnessMap);
    glActiveTexture(GL_TEXTURE7);
    glBindTexture(GL_TEXTURE_2D, ironAOMap);

    model.setToIdentity();
    model.translate(QVector3D(-5.0, 0.0, 2.0));
    pbrShader.setUniformValue("model", model);
    renderSphere();

    // gold
    glActiveTexture(GL_TEXTURE3);
    glBindTexture(GL_TEXTURE_2D, goldAlbedoMap);
    glActiveTexture(GL_TEXTURE4);
    glBindTexture(GL_TEXTURE_2D, goldNormalMap);
    glActiveTexture(GL_TEXTURE5);
    glBindTexture(GL_TEXTURE_2D, goldMetallicMap);
    glActiveTexture(GL_TEXTURE6);
    glBindTexture(GL_TEXTURE_2D, goldRoughnessMap);
    glActiveTexture(GL_TEXTURE7);
    glBindTexture(GL_TEXTURE_2D, goldAOMap);

    model.setToIdentity();
    model.translate(QVector3D(-3.0, 0.0, 2.0));
    pbrShader.setUniformValue("model", model);
    renderSphere();

    // grass
    glActiveTexture(GL_TEXTURE3);
    glBindTexture(GL_TEXTURE_2D, grassAlbedoMap);
    glActiveTexture(GL_TEXTURE4);
    glBindTexture(GL_TEXTURE_2D, grassNormalMap);
    glActiveTexture(GL_TEXTURE5);
    glBindTexture(GL_TEXTURE_2D, grassMetallicMap);
    glActiveTexture(GL_TEXTURE6);
    glBindTexture(GL_TEXTURE_2D, grassRoughnessMap);
    glActiveTexture(GL_TEXTURE7);
    glBindTexture(GL_TEXTURE_2D, grassAOMap);

    model.setToIdentity();
    model.translate(QVector3D(-1.0, 0.0, 2.0));
    pbrShader.setUniformValue("model", model);
    renderSphere();

    // plastic
    glActiveTexture(GL_TEXTURE3);
    glBindTexture(GL_TEXTURE_2D, plasticAlbedoMap);
    glActiveTexture(GL_TEXTURE4);
    glBindTexture(GL_TEXTURE_2D, plasticNormalMap);
    glActiveTexture(GL_TEXTURE5);
    glBindTexture(GL_TEXTURE_2D, plasticMetallicMap);
    glActiveTexture(GL_TEXTURE6);
    glBindTexture(GL_TEXTURE_2D, plasticRoughnessMap);
    glActiveTexture(GL_TEXTURE7);
    glBindTexture(GL_TEXTURE_2D, plasticAOMap);

    model.setToIdentity();
    model.translate(QVector3D(1.0, 0.0, 2.0));
    pbrShader.setUniformValue("model", model);
    renderSphere();

    // wall
    glActiveTexture(GL_TEXTURE3);
    glBindTexture(GL_TEXTURE_2D, wallAlbedoMap);
    glActiveTexture(GL_TEXTURE4);
    glBindTexture(GL_TEXTURE_2D, wallNormalMap);
    glActiveTexture(GL_TEXTURE5);
    glBindTexture(GL_TEXTURE_2D, wallMetallicMap);
    glActiveTexture(GL_TEXTURE6);
    glBindTexture(GL_TEXTURE_2D, wallRoughnessMap);
    glActiveTexture(GL_TEXTURE7);
    glBindTexture(GL_TEXTURE_2D, wallAOMap);

    model.setToIdentity();
    model.translate(QVector3D(3.0, 0.0, 2.0));
    pbrShader.setUniformValue("model", model);
    renderSphere();

    // render light source (simply re-render sphere at light positions)
    // this looks a bit off as we use the same shader, but it'll make their positions obvious and
    // keeps the codeprint small.
    for (unsigned int i = 0; i < lightPositions.size(); ++i)
    {
        QVector3D newPos = lightPositions[i] + QVector3D(sin(mDuration * 5.0) * 5.0, 0.0, 0.0);
        newPos = lightPositions[i];
        QString name = "lightPositions[" + QString::number(i) + "]";
        pbrShader.setUniformValue(name.toStdString().c_str(), newPos);
        name = "lightColors[" + QString::number(i) + "]";
        pbrShader.setUniformValue(name.toStdString().c_str(), lightColors[i]);

        model.setToIdentity();
        model.translate(newPos);
        model.scale(QVector3D(0.5f, 0.5f, 0.5f));
        pbrShader.setUniformValue("model", model);
        renderSphere();
    }

    // render skybox (render as last to prevent overdraw)
    backgroundShader.bind();

    backgroundShader.setUniformValue("view", view);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, envCubemap);
    //glBindTexture(GL_TEXTURE_CUBE_MAP, irradianceMap); // display irradiance map
    //glBindTexture(GL_TEXTURE_CUBE_MAP, prefilterMap); // display prefilter map
    renderCube();
}

QList<QtProperty *> Course_6_2_2_2_ibl_specular_textured::getPropertyList(QtVariantPropertyManager *manager)
{
    GETPROPERTYLIST(Course_6_2_2_2_ibl_specular_textured)
}

void Course_6_2_2_2_ibl_specular_textured::renderSphere()
{
    if (sphereVAO == 0)
    {
        glGenVertexArrays(1, &sphereVAO);

        glGenBuffers(1, &vbo);
        glGenBuffers(1, &ebo);

        QVector<QVector3D> positions;
        QVector<QVector2D> uv;
        QVector<QVector3D> normals;
        std::vector<unsigned int> indices;

        const unsigned int X_SEGMENTS = 64;
        const unsigned int Y_SEGMENTS = 64;
        const float PI = 3.14159265359;
        for (unsigned int y = 0; y <= Y_SEGMENTS; ++y)
        {
            for (unsigned int x = 0; x <= X_SEGMENTS; ++x)
            {
                float xSegment = (float)x / (float)X_SEGMENTS;
                float ySegment = (float)y / (float)Y_SEGMENTS;
                float xPos = std::cos(xSegment * 2.0f * PI) * std::sin(ySegment * PI);
                float yPos = std::cos(ySegment * PI);
                float zPos = std::sin(xSegment * 2.0f * PI) * std::sin(ySegment * PI);

                positions.push_back(QVector3D(xPos, yPos, zPos));
                uv.push_back(QVector2D(xSegment, ySegment));
                normals.push_back(QVector3D(xPos, yPos, zPos));
            }
        }

        bool oddRow = false;
        for (unsigned int y = 0; y < Y_SEGMENTS; ++y)
        {
            if (!oddRow) // even rows: y == 0, y == 2; and so on
            {
                for (unsigned int x = 0; x <= X_SEGMENTS; ++x)
                {
                    indices.push_back(y       * (X_SEGMENTS + 1) + x);
                    indices.push_back((y + 1) * (X_SEGMENTS + 1) + x);
                }
            }
            else
            {
                for (int x = X_SEGMENTS; x >= 0; --x)
                {
                    indices.push_back((y + 1) * (X_SEGMENTS + 1) + x);
                    indices.push_back(y       * (X_SEGMENTS + 1) + x);
                }
            }
            oddRow = !oddRow;
        }
        indexCount = indices.size();

        std::vector<float> data;
        for (std::size_t i = 0; i < positions.size(); ++i)
        {
            data.push_back(positions[i].x());
            data.push_back(positions[i].y());
            data.push_back(positions[i].z());
            if (uv.size() > 0)
            {
                data.push_back(uv[i].x());
                data.push_back(uv[i].y());
            }
            if (normals.size() > 0)
            {
                data.push_back(normals[i].x());
                data.push_back(normals[i].y());
                data.push_back(normals[i].z());
            }
        }
        glBindVertexArray(sphereVAO);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), &data[0], GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
        float stride = (3 + 2 + 3) * sizeof(float);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void*)0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, stride, (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, stride, (void*)(5 * sizeof(float)));
    }

    glBindVertexArray(sphereVAO);
    glDrawElements(GL_TRIANGLE_STRIP, indexCount, GL_UNSIGNED_INT, 0);
}

void Course_6_2_2_2_ibl_specular_textured::renderCube()
{
    // initialize (if necessary)
    if (cubeVAO == 0)
    {
        float vertices[] = {
            // back face
            -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f, // bottom-left
             1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f, // top-right
             1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 1.0f, 0.0f, // bottom-right
             1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f, // top-right
            -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f, // bottom-left
            -1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 0.0f, 1.0f, // top-left
            // front face
            -1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 0.0f, // bottom-left
             1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, 0.0f, // bottom-right
             1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, 1.0f, // top-right
             1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, 1.0f, // top-right
            -1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 1.0f, // top-left
            -1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 0.0f, // bottom-left
            // left face
            -1.0f,  1.0f,  1.0f, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-right
            -1.0f,  1.0f, -1.0f, -1.0f,  0.0f,  0.0f, 1.0f, 1.0f, // top-left
            -1.0f, -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-left
            -1.0f, -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-left
            -1.0f, -1.0f,  1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 0.0f, // bottom-right
            -1.0f,  1.0f,  1.0f, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-right
            // right face
             1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-left
             1.0f, -1.0f, -1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-right
             1.0f,  1.0f, -1.0f,  1.0f,  0.0f,  0.0f, 1.0f, 1.0f, // top-right
             1.0f, -1.0f, -1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-right
             1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-left
             1.0f, -1.0f,  1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 0.0f, // bottom-left
            // bottom face
            -1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f, // top-right
             1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f, 1.0f, 1.0f, // top-left
             1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f, // bottom-left
             1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f, // bottom-left
            -1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f, 0.0f, 0.0f, // bottom-right
            -1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f, // top-right
            // top face
            -1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f, // top-left
             1.0f,  1.0f , 1.0f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f, // bottom-right
             1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f, 1.0f, 1.0f, // top-right
             1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f, // bottom-right
            -1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f, // top-left
            -1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 0.0f  // bottom-left
        };
        glGenVertexArrays(1, &cubeVAO);
        glGenBuffers(1, &cubeVBO);
        // fill buffer
        glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        // link vertex attributes
        glBindVertexArray(cubeVAO);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }
    // render Cube
    glBindVertexArray(cubeVAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
}

void Course_6_2_2_2_ibl_specular_textured::renderQuad()
{
    if (quadVAO == 0)
    {
        float quadVertices[] = {
            // positions        // texture Coords
            -1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
            -1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
             1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
             1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
        };
        // setup plane VAO
        glGenVertexArrays(1, &quadVAO);
        glGenBuffers(1, &quadVBO);
        glBindVertexArray(quadVAO);
        glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    }
    glBindVertexArray(quadVAO);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glBindVertexArray(0);
}
