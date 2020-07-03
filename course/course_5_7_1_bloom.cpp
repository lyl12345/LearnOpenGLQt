#include "course_5_7_1_bloom.h"
#include <QDir>
#include <QDebug>
#include "stb_image.h"
#include <QResizeEvent>

Course_5_7_1_bloom::Course_5_7_1_bloom()
    :CourseWithCamera()
    ,bloom(true)
    ,bloomKeyPressed(false)
    ,exposure(1.0)
    ,cubeVAO(0)
    ,cubeVBO(0)
    ,quadVAO(0)
    ,quadVBO(0)
{
    initializeOpenGLFunctions();
}

Course_5_7_1_bloom::~Course_5_7_1_bloom()
{
    glDeleteTextures(1, &woodTexture);
    glDeleteTextures(1, &containerTexture);
    glDeleteFramebuffers(1, &hdrFBO);
    glDeleteBuffers(2, colorBuffers);
    glDeleteRenderbuffers(1, &rboDepth);
    glDeleteFramebuffers(2, pingpongFBO);
    glDeleteTextures(2, pingpongColorbuffers);
    glDeleteVertexArrays(1, &cubeVAO);
    glDeleteBuffers(1, &cubeVBO);
    glDeleteVertexArrays(1, &quadVAO);
    glDeleteBuffers(1, &quadVBO);
}

void Course_5_7_1_bloom::init(GlWindow *glWindow)
{
    setGlWindow(glWindow);

    mCamera = Camera(QVector3D(0.0f, 0.0f, 5.0f));
    glEnable(GL_DEPTH_TEST);

    QString shaderPath = QDir::currentPath() + "/shaders/5.advanced_lighting/7.1.bloom/";
    shader.addShaderFromSourceFile(QOpenGLShader::Vertex,shaderPath+"7.bloom.vs");
    shader.addShaderFromSourceFile(QOpenGLShader::Fragment,shaderPath+"7.bloom.fs");
    shader.link();

    shaderLight.addShaderFromSourceFile(QOpenGLShader::Vertex,shaderPath+"7.bloom.vs");
    shaderLight.addShaderFromSourceFile(QOpenGLShader::Fragment,shaderPath+"7.light_box.fs");
    shaderLight.link();

    shaderBlur.addShaderFromSourceFile(QOpenGLShader::Vertex,shaderPath+"7.blur.vs");
    shaderBlur.addShaderFromSourceFile(QOpenGLShader::Fragment,shaderPath+"7.blur.fs");
    shaderBlur.link();

    shaderBloomFinal.addShaderFromSourceFile(QOpenGLShader::Vertex,shaderPath+"7.bloom_final.vs");
    shaderBloomFinal.addShaderFromSourceFile(QOpenGLShader::Fragment,shaderPath+"7.bloom_final.fs");
    shaderBloomFinal.link();

    QString path = QDir::currentPath() + "/resources/textures/wood.png";
    woodTexture = loadTexture3(path.toStdString().c_str(), true);
    path = QDir::currentPath() + "/resources/textures/container2.png";
    containerTexture = loadTexture3(path.toStdString().c_str(), true);

    int SCR_WIDTH = 0;
    int SCR_HEIGHT = 0;
    QSize size = contextSize();
    if (size.width() > 0)
        SCR_WIDTH = size.width();
    if (size.height() > 0)
        SCR_HEIGHT = size.height();

    // configure (floating point) framebuffers
    glGenFramebuffers(1, &hdrFBO);
    glBindFramebuffer(GL_FRAMEBUFFER, hdrFBO);
    // create 2 floating point color buffers (1 for normal rendering, other for brightness treshold values)
    glGenTextures(2, colorBuffers);
    for (unsigned int i = 0; i < 2; i++)
    {
        glBindTexture(GL_TEXTURE_2D, colorBuffers[i]);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, SCR_WIDTH, SCR_HEIGHT, 0, GL_RGBA, GL_FLOAT, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);  // we clamp to the edge as the blur filter would otherwise sample repeated texture values!
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        // attach texture to framebuffer
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, colorBuffers[i], 0);
    }
    // create and attach depth buffer (renderbuffer)
    glGenRenderbuffers(1, &rboDepth);
    glBindRenderbuffer(GL_RENDERBUFFER, rboDepth);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, SCR_WIDTH, SCR_HEIGHT);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rboDepth);
    // tell OpenGL which color attachments we'll use (of this framebuffer) for rendering
    attachments[0] = GL_COLOR_ATTACHMENT0;
    attachments[1] = GL_COLOR_ATTACHMENT1;
    glDrawBuffers(2, attachments);
    // finally check if framebuffer is complete
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        qDebug() << "Framebuffer not complete!";
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    // ping-pong-framebuffer for blurring
    glGenFramebuffers(2, pingpongFBO);
    glGenTextures(2, pingpongColorbuffers);
    for (unsigned int i = 0; i < 2; i++)
    {
        glBindFramebuffer(GL_FRAMEBUFFER, pingpongFBO[i]);
        glBindTexture(GL_TEXTURE_2D, pingpongColorbuffers[i]);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, SCR_WIDTH, SCR_HEIGHT, 0, GL_RGBA, GL_FLOAT, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // we clamp to the edge as the blur filter would otherwise sample repeated texture values!
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, pingpongColorbuffers[i], 0);
        // also check if framebuffers are complete (no need for depth buffer)
        if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
            qDebug() << "Framebuffer not complete!";
    }

    lightPositions.push_back(QVector3D( 0.0f, 0.5f,  1.5f));
    lightPositions.push_back(QVector3D(-4.0f, 0.5f, -3.0f));
    lightPositions.push_back(QVector3D( 3.0f, 0.5f,  1.0f));
    lightPositions.push_back(QVector3D(-.8f,  2.4f, -1.0f));

    lightColors.push_back(QVector3D(5.0f,   5.0f,  5.0f));
    lightColors.push_back(QVector3D(10.0f,  0.0f,  0.0f));
    lightColors.push_back(QVector3D(0.0f,   0.0f,  15.0f));
    lightColors.push_back(QVector3D(0.0f,   5.0f,  0.0f));

    shader.bind();
    shader.setUniformValue("diffuseTexture", 0);
    shaderBlur.bind();
    shaderBlur.setUniformValue("image", 0);
    shaderBloomFinal.bind();
    shaderBloomFinal.setUniformValue("scene", 0);
    shaderBloomFinal.setUniformValue("bloomBlur", 1);
}

void Course_5_7_1_bloom::render()
{
    Course::render();

    processInput();

    // render
    // ------
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // 1. render scene into floating point framebuffer
    // -----------------------------------------------
    glBindFramebuffer(GL_FRAMEBUFFER, hdrFBO);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    QMatrix4x4 projection;
    projection.perspective(mCamera.Zoom, 800/600, 0.1f, 100.0f);
    QMatrix4x4 view = mCamera.GetViewMatrix();
    QMatrix4x4 model;
    shader.bind();
    shader.setUniformValue("projection", projection);
    shader.setUniformValue("view", view);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, woodTexture);
    // set lighting uniforms
    for (unsigned int i = 0; i < lightPositions.size(); i++)
    {
        QString name = "lights[" + QString::number(i) + "].Position";
        shader.setUniformValue(name.toStdString().c_str(), lightPositions[i]);
        name = "lights[" + QString::number(i) + "].Color";
        shader.setUniformValue(name.toStdString().c_str(), lightColors[i]);
    }
    shader.setUniformValue("viewPos", mCamera.Position);
    // create one large cube that acts as the floor
    model.setToIdentity();
    model.translate(QVector3D(0.0f, -1.0f, 0.0));
    model.scale(QVector3D(12.5f, 0.5f, 12.5f));
    shader.setUniformValue("model", model);
    renderCube();
    // then create multiple cubes as the scenery
    glBindTexture(GL_TEXTURE_2D, containerTexture);
    model.setToIdentity();
    model.translate(QVector3D(0.0f, 1.5f, 0.0));
    model.scale(QVector3D(0.5f, 0.5f, 0.5f));
    shader.setUniformValue("model", model);
    renderCube();

    model.setToIdentity();
    model.translate(QVector3D(2.0f, 0.0f, 1.0));
    model.scale(QVector3D(0.5f, 0.5f, 0.5f));
    shader.setUniformValue("model", model);
    renderCube();

    model.setToIdentity();
    model.translate(QVector3D(-1.0f, -1.0f, 2.0));
    model.rotate(60.0f, QVector3D(1.0, 0.0, 1.0).normalized());
    shader.setUniformValue("model", model);
    renderCube();

    model.setToIdentity();
    model.translate(QVector3D(0.0f, 2.7f, 4.0));
    model.rotate(23.0f, QVector3D(1.0, 0.0, 1.0).normalized());
    model.scale(QVector3D(1.25f, 1.25f, 1.25f));
    shader.setUniformValue("model", model);
    renderCube();

    model.setToIdentity();
    model.translate(QVector3D(-2.0f, 1.0f, -3.0));
    model.rotate(124.0f, QVector3D(1.0, 0.0, 1.0).normalized());
    shader.setUniformValue("model", model);
    renderCube();

    model.setToIdentity();
    model.translate(QVector3D(-3.0f, 0.0f, 0.0));
    model.scale(QVector3D(0.5f, 0.5f, 0.5f));
    shader.setUniformValue("model", model);
    renderCube();

    // finally show all the light sources as bright cubes
    shaderLight.bind();
    shaderLight.setUniformValue("projection", projection);
    shaderLight.setUniformValue("view", view);

    for (unsigned int i = 0; i < lightPositions.size(); i++)
    {
        model.setToIdentity();
        model.translate(lightPositions[i]);
        model.scale(QVector3D(0.25f, 0.25f, 0.25f));
        shaderLight.setUniformValue("model", model);
        shaderLight.setUniformValue("lightColor", lightColors[i]);
        renderCube();
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    // 2. blur bright fragments with two-pass Gaussian Blur
    // --------------------------------------------------
    bool horizontal = true, first_iteration = true;
    unsigned int amount = 10;
    shaderBlur.bind();
    for (unsigned int i = 0; i < amount; i++)
    {
        glBindFramebuffer(GL_FRAMEBUFFER, pingpongFBO[horizontal]);
        shaderBlur.setUniformValue("horizontal", horizontal);
        glBindTexture(GL_TEXTURE_2D, first_iteration ? colorBuffers[1] : pingpongColorbuffers[!horizontal]);  // bind texture of other framebuffer (or scene if first iteration)
        renderQuad();
        horizontal = !horizontal;
        if (first_iteration)
            first_iteration = false;
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    // 3. now render floating point color buffer to 2D quad and tonemap HDR colors to default framebuffer's (clamped) color range
    // --------------------------------------------------------------------------------------------------------------------------
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    shaderBloomFinal.bind();
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, colorBuffers[0]);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, pingpongColorbuffers[!horizontal]);
    shaderBloomFinal.setUniformValue("bloom", bloom);
    shaderBloomFinal.setUniformValue("exposure", exposure);
    renderQuad();
}

QList<QtProperty *> Course_5_7_1_bloom::getPropertyList(QtVariantPropertyManager *manager)
{
    GETPROPERTYLIST(Course_5_7_1_bloom)
}

void Course_5_7_1_bloom::processInput()
{
    CourseWithCamera::processInput();

    if (mPressedKey.contains(Qt::Key_Space) && !bloomKeyPressed){
        bloom = !bloom;
        bloomKeyPressed = true;
    }
    if (!mPressedKey.contains(Qt::Key_Space)){
        bloomKeyPressed = false;
    }

    if (mPressedKey.contains(Qt::Key_Q)){
        if (exposure > 0.0f)
            exposure -= 0.01f;
        else
            exposure = 0.0f;
    }else if (mPressedKey.contains(Qt::Key_E)){
        exposure += 0.01f;
    }
}

void Course_5_7_1_bloom::Resize(QResizeEvent *event)
{
    int SCR_WIDTH = 0;
    int SCR_HEIGHT = 0;
    QSize size = event->size();
    if (size.width() > 0)
        SCR_WIDTH = size.width();
    if (size.height() > 0)
        SCR_HEIGHT = size.height();

    glBindFramebuffer(GL_FRAMEBUFFER, hdrFBO);
    for (unsigned int i = 0; i < 2; i++)
    {
        glBindTexture(GL_TEXTURE_2D, colorBuffers[i]);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, SCR_WIDTH, SCR_HEIGHT, 0, GL_RGBA, GL_FLOAT, NULL);
    }
    glBindRenderbuffer(GL_RENDERBUFFER, rboDepth);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, SCR_WIDTH, SCR_HEIGHT);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    for (unsigned int i = 0; i < 2; i++)
    {
        glBindFramebuffer(GL_FRAMEBUFFER, pingpongFBO[i]);
        glBindTexture(GL_TEXTURE_2D, pingpongColorbuffers[i]);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, SCR_WIDTH, SCR_HEIGHT, 0, GL_RGBA, GL_FLOAT, NULL);
    }
}

void Course_5_7_1_bloom::renderCube()
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

void Course_5_7_1_bloom::renderQuad()
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
