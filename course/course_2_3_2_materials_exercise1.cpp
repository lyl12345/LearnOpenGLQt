#include "course_2_3_2_materials_exercise1.h"
#include <QDir>
#include <QDebug>
#include "stb_image.h"
#include <QMouseEvent>
#include <qmath.h>
#include <QVector3D>

Course_2_3_2_materials_exercise1::Course_2_3_2_materials_exercise1()
    :CourseWithCamera()
    ,lightPos(QVector3D(1.2f, 1.0f, 2.0f))
{
    initializeOpenGLFunctions();

    glEnable(GL_DEPTH_TEST);

    QString shaderPath = QDir::currentPath() + "/shaders/2.lighting/3.2.materials_exercise1/";
    mLightingProgram.addShaderFromSourceFile(QOpenGLShader::Vertex,shaderPath+"3.2.materials.vs");
    mLightingProgram.addShaderFromSourceFile(QOpenGLShader::Fragment,shaderPath+"3.2.materials.fs");
    mLightingProgram.link();

    mLightCubeProgram.addShaderFromSourceFile(QOpenGLShader::Vertex,shaderPath+"3.2.light_cube.vs");
    mLightCubeProgram.addShaderFromSourceFile(QOpenGLShader::Fragment,shaderPath+"3.2.light_cube.fs");
    mLightCubeProgram.link();

    float vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
    };

    glGenVertexArrays(1, &cubeVAO);
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindVertexArray(cubeVAO);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // normal attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glGenVertexArrays(1, &lightCubeVAO);
    glBindVertexArray(lightCubeVAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // note that we update the lamp's position attribute's stride to reflect the updated buffer data
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
}

Course_2_3_2_materials_exercise1::~Course_2_3_2_materials_exercise1()
{
    glDeleteVertexArrays(1, &cubeVAO);
    glDeleteVertexArrays(1, &lightCubeVAO);
    glDeleteBuffers(1, &VBO);
}

void Course_2_3_2_materials_exercise1::render()
{
    Course::render();

    processInput();

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // be sure to activate shader when setting uniforms/drawing objects
    mLightingProgram.bind();
    mLightingProgram.setUniformValue("light.position", lightPos);
    mLightingProgram.setUniformValue("viewPos", mCamera.Position);

    // light properties
    mLightingProgram.setUniformValue("light.ambient", 1.0f, 1.0f, 1.0f); // note that all light colors are set at full intensity
    mLightingProgram.setUniformValue("light.diffuse", 1.0f, 1.0f, 1.0f);
    mLightingProgram.setUniformValue("light.specular", 1.0f, 1.0f, 1.0f);

    // material properties
    mLightingProgram.setUniformValue("material.ambient", 0.0f, 0.1f, 0.06f);
    mLightingProgram.setUniformValue("material.diffuse", 0.0f, 0.50980392f, 0.50980392f);
    mLightingProgram.setUniformValue("material.specular", 0.50196078f, 0.50196078f, 0.50196078f);
    mLightingProgram.setUniformValue("material.shininess", 32.0f);

    // view/projection transformations
    QMatrix4x4 projection;
    projection.perspective(mCamera.Zoom, 800 / 600, 0.1f, 100.0f);
    QMatrix4x4 view = mCamera.GetViewMatrix();
    mLightingProgram.setUniformValue("projection", projection);
    mLightingProgram.setUniformValue("view", view);

    // world transformation
    QMatrix4x4 model;
    mLightingProgram.setUniformValue("model", model);

    // render the cube
    glBindVertexArray(cubeVAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);


    // also draw the lamp object
    mLightCubeProgram.bind();
    mLightCubeProgram.setUniformValue("projection", projection);
    mLightCubeProgram.setUniformValue("view", view);
    model.translate(lightPos);
    model.scale(QVector3D(0.2f, 0.2f, 0.2f));
    mLightCubeProgram.setUniformValue("model", model);

    glBindVertexArray(lightCubeVAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
}

QList<QtProperty *> Course_2_3_2_materials_exercise1::getPropertyList(QtVariantPropertyManager *manager)
{
    GETPROPERTYLIST(Course_2_3_2_materials_exercise1)
}
