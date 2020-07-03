#include "course_2_1_1_colors.h"
#include <QDir>
#include <QDebug>
#include "stb_image.h"
#include <QMouseEvent>
#include <qmath.h>
#include <QVector3D>

Course_2_1_1_colors::Course_2_1_1_colors()
    :lightPos(1.2f, 1.0f, 2.0f)
{
    initializeOpenGLFunctions();

    QString shaderPath = QDir::currentPath() + "/shaders/2.lighting/1.colors/";
    mLightingProgram.addShaderFromSourceFile(QOpenGLShader::Vertex,shaderPath+"1.colors.vs");
    mLightingProgram.addShaderFromSourceFile(QOpenGLShader::Fragment,shaderPath+"1.colors.fs");
    mLightingProgram.link();

    mLightCubeProgram.addShaderFromSourceFile(QOpenGLShader::Vertex,shaderPath+"1.light_cube.vs");
    mLightCubeProgram.addShaderFromSourceFile(QOpenGLShader::Fragment,shaderPath+"1.light_cube.fs");
    mLightCubeProgram.link();

    float vertices[] = {
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
        -0.5f,  0.5f, -0.5f,
    };

    glGenVertexArrays(1, &cubeVAO);
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindVertexArray(cubeVAO);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glGenVertexArrays(1, &lightCubeVAO);
    glBindVertexArray(lightCubeVAO);

    // we only need to bind to the VBO (to link it with glVertexAttribPointer), no need to fill it; the VBO's data already contains all we need (it's already bound, but we do it again for educational purposes)
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

}

Course_2_1_1_colors::~Course_2_1_1_colors()
{
    glDeleteVertexArrays(1, &cubeVAO);
    glDeleteVertexArrays(1, &lightCubeVAO);
    glDeleteBuffers(1, &VBO);
}

void Course_2_1_1_colors::render()
{
    Course::render();

    processInput();

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // be sure to activate shader when setting uniforms/drawing objects
    mLightingProgram.bind();
    mLightingProgram.setUniformValue("objectColor", QVector3D(1.0f, 0.5f, 0.31f));
    mLightingProgram.setUniformValue("lightColor", QVector3D(1.0f, 1.0f, 1.0f));

    // view/projection transformations
    QMatrix4x4 projection;
    projection.perspective(mCamera.Zoom, 800 / 600, 0.1f, 100.0f);
    mLightingProgram.setUniformValue("projection", projection);
    mLightingProgram.setUniformValue("view", mCamera.GetViewMatrix());

    // world transformation
    mLightingProgram.setUniformValue("model", QMatrix4x4());

    // render the cube
    glBindVertexArray(cubeVAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);


    // also draw the lamp object
    mLightCubeProgram.bind();
    mLightCubeProgram.setUniformValue("projection", projection);
    mLightCubeProgram.setUniformValue("view", mCamera.GetViewMatrix());

    QMatrix4x4 model;
    model.translate(lightPos);
    model.scale(QVector3D(0.2f, 0.2f, 0.2f));
    mLightCubeProgram.setUniformValue("model", model);

    glBindVertexArray(lightCubeVAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
}

QList<QtProperty *> Course_2_1_1_colors::getPropertyList(QtVariantPropertyManager *manager)
{
    GETPROPERTYLIST(Course_2_1_1_colors)
}
