#include "course_5_6_1_hdr.h"
#include <QDir>
#include <QDebug>
#include "stb_image.h"
#include <QResizeEvent>

Course_5_6_1_hdr::Course_5_6_1_hdr()
    :CourseWithCamera()
    ,cubeVAO(0)
    ,cubeVBO(0)
    ,quadVAO(0)
    ,quadVBO(0)
    ,hdr(true)
    ,hdrKeyPressed(false)
    ,exposure(1.0f)
{
    initializeOpenGLFunctions();
}

Course_5_6_1_hdr::~Course_5_6_1_hdr()
{
    glDeleteTextures(1, &woodTexture);
    glDeleteFramebuffers(1, &hdrFBO);
    glDeleteTextures(1, &colorBuffer);
    glDeleteRenderbuffers(1, &rboDepth);
    glDeleteVertexArrays(1, &quadVAO);
    glDeleteBuffers(1, &quadVBO);
    glDeleteVertexArrays(1, &cubeVAO);
    glDeleteBuffers(1, &cubeVBO);
}

void Course_5_6_1_hdr::init(GlWindow *glWindow)
{
    setGlWindow(glWindow);
    mCamera = Camera(QVector3D(0.0f, 0.0f, 5.0f));
    glEnable(GL_DEPTH_TEST);

    QString shaderPath = QDir::currentPath() + "/shaders/5.advanced_lighting/6.1.hdr/";
    shader.addShaderFromSourceFile(QOpenGLShader::Vertex,shaderPath+"6.lighting.vs");
    shader.addShaderFromSourceFile(QOpenGLShader::Fragment,shaderPath+"6.lighting.fs");
    shader.link();

    hdrShader.addShaderFromSourceFile(QOpenGLShader::Vertex,shaderPath+"6.hdr.vs");
    hdrShader.addShaderFromSourceFile(QOpenGLShader::Fragment,shaderPath+"6.hdr.fs");
    hdrShader.link();

    QString path = QDir::currentPath() + "/resources/textures/wood.png";
    woodTexture = loadTexture(path.toStdString().c_str());

    int SCR_WIDTH = 0;
    int SCR_HEIGHT = 0;
    QSize size = contextSize();
    if (size.width() > 0)
        SCR_WIDTH = size.width();
    if (size.height() > 0)
        SCR_HEIGHT = size.height();

    glGenFramebuffers(1, &hdrFBO);
    // create floating point color buffer
    glGenTextures(1, &colorBuffer);
    glBindTexture(GL_TEXTURE_2D, colorBuffer);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, SCR_WIDTH, SCR_HEIGHT, 0, GL_RGBA, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // create depth buffer (renderbuffer)
    glGenRenderbuffers(1, &rboDepth);
    glBindRenderbuffer(GL_RENDERBUFFER, rboDepth);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, SCR_WIDTH, SCR_HEIGHT);
    // attach buffers
    glBindFramebuffer(GL_FRAMEBUFFER, hdrFBO);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, colorBuffer, 0);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rboDepth);
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        qDebug() << "Framebuffer not complete!";
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    // positions
    lightPositions.push_back(QVector3D( 0.0f,  0.0f, 49.5f)); // back light
    lightPositions.push_back(QVector3D(-1.4f, -1.9f, 9.0f));
    lightPositions.push_back(QVector3D( 0.0f, -1.8f, 4.0f));
    lightPositions.push_back(QVector3D( 0.8f, -1.7f, 6.0f));
    // colors
    lightColors.push_back(QVector3D(200.0f, 200.0f, 200.0f));
    lightColors.push_back(QVector3D(0.1f, 0.0f, 0.0f));
    lightColors.push_back(QVector3D(0.0f, 0.0f, 0.2f));
    lightColors.push_back(QVector3D(0.0f, 0.1f, 0.0f));

    shader.bind();
    shader.setUniformValue("diffuseTexture", 0);
    hdrShader.bind();
    hdrShader.setUniformValue("hdrBuffer", 0);
}

void Course_5_6_1_hdr::render()
{
    Course::render();

    processInput();

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // 1. render scene into floating point framebuffer
    // -----------------------------------------------
    glBindFramebuffer(GL_FRAMEBUFFER, hdrFBO);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    QMatrix4x4 projection;
    projection.perspective(mCamera.Zoom, 800/600, 0.1f, 100.0f);
    QMatrix4x4 view = mCamera.GetViewMatrix();
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
    // render tunnel
    QMatrix4x4 model;
    model.translate(QVector3D(0.0f, 0.0f, 25.0));
    model.scale(QVector3D(2.5f, 2.5f, 27.5f));
    shader.setUniformValue("model", model);
    shader.setUniformValue("inverse_normals", true);
    renderCube();
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    // 2. now render floating point color buffer to 2D quad and tonemap HDR colors to default framebuffer's (clamped) color range
    // --------------------------------------------------------------------------------------------------------------------------
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    hdrShader.bind();
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, colorBuffer);
    hdrShader.setUniformValue("hdr", hdr);
    hdrShader.setUniformValue("exposure", exposure);
    renderQuad();
}

QList<QtProperty *> Course_5_6_1_hdr::getPropertyList(QtVariantPropertyManager *manager)
{
    GETPROPERTYLIST(Course_5_6_1_hdr)
}

void Course_5_6_1_hdr::processInput()
{
    CourseWithCamera::processInput();

    if (mPressedKey.contains(Qt::Key_Space) && !hdrKeyPressed){
        hdr = !hdr;
        hdrKeyPressed = true;
    }
    if (!mPressedKey.contains(Qt::Key_Space)){
        hdrKeyPressed = false;
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

void Course_5_6_1_hdr::Resize(QResizeEvent *event)
{
    int SCR_WIDTH = 0;
    int SCR_HEIGHT = 0;
    QSize size = event->size();
    if (size.width() > 0)
        SCR_WIDTH = size.width();
    if (size.height() > 0)
        SCR_HEIGHT = size.height();

    glBindTexture(GL_TEXTURE_2D, colorBuffer);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, SCR_WIDTH, SCR_HEIGHT, 0, GL_RGBA, GL_FLOAT, NULL);

    glBindRenderbuffer(GL_RENDERBUFFER, rboDepth);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, SCR_WIDTH, SCR_HEIGHT);
}

void Course_5_6_1_hdr::renderCube()
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

void Course_5_6_1_hdr::renderQuad()
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
