#include "course_4_11_1_anti_aliasing_msaa.h"
#include <QDir>
#include <QDebug>
#include "stb_image.h"

Course_4_11_1_anti_aliasing_msaa::Course_4_11_1_anti_aliasing_msaa()
    :CourseWithCamera()
{
    initializeOpenGLFunctions();
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_MULTISAMPLE); // enabled by default on some drivers, but not all so always enable to make sure

    QString shaderPath = QDir::currentPath() + "/shaders/4.advanced_opengl/11.1.anti_aliasing_msaa/";
    mProgram.addShaderFromSourceFile(QOpenGLShader::Vertex,shaderPath+"11.1.anti_aliasing.vs");
    mProgram.addShaderFromSourceFile(QOpenGLShader::Fragment,shaderPath+"11.1.anti_aliasing.fs");
    mProgram.link();

    float cubeVertices[] = {
        // positions
        -0.5f, -0.5f, -0.5f,
        0.5f, -0.5f, -0.5f,
        0.5f,  0.5f, -0.5f,
        0.5f,  0.5f, -0.5f,
        -0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,

        -0.5f, -0.5f,  0.5f,
        0.5f, -0.5f,  0.5f,
        0.5f,  0.5f,  0.5f,
        0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
        -0.5f, -0.5f,  0.5f,

        -0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,

        0.5f,  0.5f,  0.5f,
        0.5f,  0.5f, -0.5f,
        0.5f, -0.5f, -0.5f,
        0.5f, -0.5f, -0.5f,
        0.5f, -0.5f,  0.5f,
        0.5f,  0.5f,  0.5f,

        -0.5f, -0.5f, -0.5f,
        0.5f, -0.5f, -0.5f,
        0.5f, -0.5f,  0.5f,
        0.5f, -0.5f,  0.5f,
        -0.5f, -0.5f,  0.5f,
        -0.5f, -0.5f, -0.5f,

        -0.5f,  0.5f, -0.5f,
        0.5f,  0.5f, -0.5f,
        0.5f,  0.5f,  0.5f,
        0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f, -0.5f
    };

    glGenVertexArrays(1, &cubeVAO);
    glGenBuffers(1, &cubeVBO);
    glBindVertexArray(cubeVAO);
    glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), &cubeVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
}

Course_4_11_1_anti_aliasing_msaa::~Course_4_11_1_anti_aliasing_msaa()
{
    glDeleteVertexArrays(1, &cubeVAO);
    glDeleteBuffers(1, &cubeVBO);
}

void Course_4_11_1_anti_aliasing_msaa::render()
{
    Course::render();

    processInput();

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // set transformation matrices
    mProgram.bind();
    QMatrix4x4 model;
    QMatrix4x4 projection;
    projection.perspective(mCamera.Zoom, 800 / 600, 0.1f, 100);
    mProgram.setUniformValue("projection", projection);
    mProgram.setUniformValue("view", mCamera.GetViewMatrix());
    mProgram.setUniformValue("model", model);

    glBindVertexArray(cubeVAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
}

QList<QtProperty *> Course_4_11_1_anti_aliasing_msaa::getPropertyList(QtVariantPropertyManager *manager)
{
    GETPROPERTYLIST(Course_4_11_1_anti_aliasing_msaa)
}
