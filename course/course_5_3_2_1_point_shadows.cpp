#include "course_5_3_2_1_point_shadows.h"
#include <QDir>
#include <QDebug>
#include "stb_image.h"

Course_5_3_2_1_point_shadows::Course_5_3_2_1_point_shadows()
    :CourseWithCamera()
    ,cubeVAO(0)
    ,cubeVBO(0)
    ,shadows(true)
    ,shadowsKeyPressed(false)
{
    initializeOpenGLFunctions();

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    QString shaderPath = QDir::currentPath() + "/shaders/5.advanced_lighting/3.2.1.point_shadows/";
    shader.addShaderFromSourceFile(QOpenGLShader::Vertex,shaderPath+"3.2.1.point_shadows.vs");
    shader.addShaderFromSourceFile(QOpenGLShader::Fragment,shaderPath+"3.2.1.point_shadows.fs");
    shader.link();

    simpleDepthShader.addShaderFromSourceFile(QOpenGLShader::Vertex,shaderPath+"3.2.1.point_shadows_depth.vs");
    simpleDepthShader.addShaderFromSourceFile(QOpenGLShader::Fragment,shaderPath+"3.2.1.point_shadows_depth.fs");
    simpleDepthShader.addShaderFromSourceFile(QOpenGLShader::Geometry,shaderPath+"3.2.1.point_shadows_depth.gs");
    simpleDepthShader.link();

    QString path = QDir::currentPath() + "/resources/textures/wood.png";
    woodTexture = loadTexture2(path.toStdString().c_str());

    // configure depth map FBO
    // -----------------------
    const unsigned int SHADOW_WIDTH = 1024, SHADOW_HEIGHT = 1024;
    glGenFramebuffers(1, &depthMapFBO);
    // create depth cubemap texture
    glGenTextures(1, &depthCubemap);
    glBindTexture(GL_TEXTURE_CUBE_MAP, depthCubemap);
    for (unsigned int i = 0; i < 6; ++i)
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_DEPTH_COMPONENT, SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    // attach depth texture as FBO's depth buffer
    glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
    glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, depthCubemap, 0);
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    shader.bind();
    shader.setUniformValue("diffuseTexture", 0);
    shader.setUniformValue("depthMap", 1);
    shader.release();

    lightPos = QVector3D(0.0f, 0.0f, 0.0f);
}

Course_5_3_2_1_point_shadows::~Course_5_3_2_1_point_shadows()
{
    glDisable(GL_CULL_FACE);
    glDeleteTextures(1, &woodTexture);
    glDeleteTextures(1, &depthCubemap);
    glDeleteVertexArrays(1, &cubeVAO);
    glDeleteBuffers(1, &cubeVBO);
    glDeleteFramebuffers(1, &depthMapFBO);
}

void Course_5_3_2_1_point_shadows::render()
{
    Course::render();

    processInput();
    lightPos.setZ(sin(mDuration * 0.5) * 3.0);
    // render
    // ------
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // 0. create depth cubemap transformation matrices
    // -----------------------------------------------
    float near_plane = 1.0f;
    float far_plane  = 25.0f;
    QMatrix4x4 shadowProj;
    shadowProj.perspective(90.0f, (float)1024 / (float)1024, near_plane, far_plane);
    QVector<QMatrix4x4> shadowTransforms;
    QMatrix4x4 view;
    view.setToIdentity();
    view.lookAt(lightPos, lightPos + QVector3D(1.0f,  0.0f,  0.0f), QVector3D(0.0f, -1.0f,  0.0f));
    view = shadowProj * view;
    shadowTransforms.push_back(view);
    view.setToIdentity();
    view.lookAt(lightPos, lightPos + QVector3D(-1.0f,  0.0f,  0.0f), QVector3D(0.0f, -1.0f,  0.0f));
    view = shadowProj * view;
    shadowTransforms.push_back(view);
    view.setToIdentity();
    view.lookAt(lightPos, lightPos + QVector3D(0.0f,  1.0f,  0.0f), QVector3D(0.0f,  0.0f,  1.0f));
    view = shadowProj * view;
    shadowTransforms.push_back(view);
    view.setToIdentity();
    view.lookAt(lightPos, lightPos + QVector3D(0.0f, -1.0f,  0.0f), QVector3D(0.0f,  0.0f, -1.0f));
    view = shadowProj * view;
    shadowTransforms.push_back(view);
    view.setToIdentity();
    view.lookAt(lightPos, lightPos + QVector3D(0.0f,  0.0f,  1.0f), QVector3D(0.0f, -1.0f,  0.0f));
    view = shadowProj * view;
    shadowTransforms.push_back(view);
    view.setToIdentity();
    view.lookAt(lightPos, lightPos + QVector3D(0.0f,  0.0f, -1.0f), QVector3D(0.0f, -1.0f,  0.0f));
    view = shadowProj * view;
    shadowTransforms.push_back(view);

    // 1. render scene to depth cubemap
    // --------------------------------
    glViewport(0, 0, 1024, 1024);
    glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
    glClear(GL_DEPTH_BUFFER_BIT);
    simpleDepthShader.bind();
    for (unsigned int i = 0; i < 6; ++i){
        QString name = "shadowMatrices[" + QString::number(i) + "]";
        simpleDepthShader.setUniformValue(name.toStdString().c_str(), shadowTransforms[i]);
    }
    simpleDepthShader.setUniformValue("far_plane", far_plane);
    simpleDepthShader.setUniformValue("lightPos", lightPos);
    renderScene(simpleDepthShader);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    // 2. render scene as normal
    // -------------------------
    unsigned int SCR_WIDTH = 800;
    unsigned int SCR_HEIGHT = 600;
    QSize size = contextSize();
    if (size.width() != -1){
        SCR_WIDTH = size.width();
        SCR_HEIGHT = size.height();
    }
    glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    shader.bind();
    QMatrix4x4 projection;
    projection.perspective(mCamera.Zoom, 800 / 600, 0.1f, 100.0f);
    view = mCamera.GetViewMatrix();
    shader.setUniformValue("projection", projection);
    shader.setUniformValue("view", view);
    // set lighting uniforms
    shader.setUniformValue("lightPos", lightPos);
    shader.setUniformValue("viewPos", mCamera.Position);
    shader.setUniformValue("shadows", shadows); // enable/disable shadows by pressing 'SPACE'
    shader.setUniformValue("far_plane", far_plane);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, woodTexture);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_CUBE_MAP, depthCubemap);
    renderScene(shader);
}

QList<QtProperty *> Course_5_3_2_1_point_shadows::getPropertyList(QtVariantPropertyManager *manager)
{
    GETPROPERTYLIST(Course_5_3_2_1_point_shadows)
}

void Course_5_3_2_1_point_shadows::processInput()
{
    CourseWithCamera::processInput();

    if (mPressedKey.contains(Qt::Key_Space) && !shadowsKeyPressed){
        shadows = !shadows;
        shadowsKeyPressed = true;
    }
    if (!mPressedKey.contains(Qt::Key_Space)){
        shadowsKeyPressed = false;
    }
}

void Course_5_3_2_1_point_shadows::renderScene(QOpenGLShaderProgram &shader)
{
    // room cube
    QMatrix4x4 model;
    model.scale(QVector3D(5.0f,5.0f,5.0f));
    shader.setUniformValue("model", model);
    glDisable(GL_CULL_FACE); // note that we disable culling here since we render 'inside' the cube instead of the usual 'outside' which throws off the normal culling methods.
    shader.setUniformValue("reverse_normals", 1); // A small little hack to invert normals when drawing cube from the inside so lighting still works.
    renderCube();
    shader.setUniformValue("reverse_normals", 0); // and of course disable it
    glEnable(GL_CULL_FACE);
    // cubes
    model.setToIdentity();
    model.translate(QVector3D(4.0f, -3.5f, 0.0));
    model.scale(QVector3D(0.5f,0.5f,0.5f));
    shader.setUniformValue("model", model);
    renderCube();
    model.setToIdentity();
    model.translate(QVector3D(2.0f, 3.0f, 1.0));
    model.scale(QVector3D(0.75f,0.75f,0.75f));
    shader.setUniformValue("model", model);
    renderCube();
    model.setToIdentity();
    model.translate(QVector3D(-3.0f, -1.0f, 0.0));
    model.scale(QVector3D(0.5f,0.5f,0.5f));
    shader.setUniformValue("model", model);
    renderCube();
    model.setToIdentity();
    model.translate(QVector3D(-1.5f, 1.0f, 1.5));
    model.scale(QVector3D(0.5f,0.5f,0.5f));
    shader.setUniformValue("model", model);
    renderCube();
    model.setToIdentity();
    model.translate(QVector3D(-1.5f, 2.0f, -3.0));
    model.rotate(60.0f, QVector3D(1.0, 0.0, 1.0).normalized());
    model.scale(QVector3D(0.75f, 0.75f, 0.75f));
    shader.setUniformValue("model", model);
    renderCube();
}

void Course_5_3_2_1_point_shadows::renderCube()
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
