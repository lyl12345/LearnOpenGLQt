#include "course_2_3_1_materials.h"
#include <QDir>
#include <QDebug>
#include "stb_image.h"
#include <QMouseEvent>
#include <qmath.h>
#include <QVector3D>

Course_2_3_1_materials::Course_2_3_1_materials()
    :CourseWithCamera()
    ,lightPos(QVector3D(1.2f, 1.0f, 2.0f))
{
    initializeOpenGLFunctions();

    glEnable(GL_DEPTH_TEST);

    QString shaderPath = QDir::currentPath() + "/shaders/2.lighting/3.1.materials/";
    mLightingProgram.addShaderFromSourceFile(QOpenGLShader::Vertex,shaderPath+"3.1.materials.vs");
    mLightingProgram.addShaderFromSourceFile(QOpenGLShader::Fragment,shaderPath+"3.1.materials.fs");
    mLightingProgram.link();

    mLightCubeProgram.addShaderFromSourceFile(QOpenGLShader::Vertex,shaderPath+"3.1.light_cube.vs");
    mLightCubeProgram.addShaderFromSourceFile(QOpenGLShader::Fragment,shaderPath+"3.1.light_cube.fs");
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
    // first, configure the cube's VAO (and VBO)
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


    // second, configure the light's VAO (VBO stays the same; the vertices are the same for the light object which is also a 3D cube)
    glGenVertexArrays(1, &lightCubeVAO);
    glBindVertexArray(lightCubeVAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // note that we update the lamp's position attribute's stride to reflect the updated buffer data
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

}

Course_2_3_1_materials::~Course_2_3_1_materials()
{
    glDeleteVertexArrays(1, &cubeVAO);
    glDeleteVertexArrays(1, &lightCubeVAO);
    glDeleteBuffers(1, &VBO);
}

void Course_2_3_1_materials::render()
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
    QVector3D lightColor;
    lightColor.setX(sin(mDuration * 2.0f));
    lightColor.setY(sin(mDuration * 0.7f));
    lightColor.setZ(sin(mDuration * 1.3f));
    QVector3D diffuseColor = lightColor * QVector3D(0.5f, 0.5f, 0.5f); // decrease the influence
    QVector3D ambientColor = diffuseColor * QVector3D(0.2f, 0.2f, 0.2f);// low influence
    mLightingProgram.setUniformValue("light.ambient", ambientColor);
    mLightingProgram.setUniformValue("light.diffuse", diffuseColor);
    mLightingProgram.setUniformValue("light.specular", 1.0f, 1.0f, 1.0f);

    // material properties
    mLightingProgram.setUniformValue("material.ambient", 1.0f, 0.5f, 0.31f);
    mLightingProgram.setUniformValue("material.diffuse", 1.0f, 0.5f, 0.31f);
    mLightingProgram.setUniformValue("material.specular", 0.5f, 0.5f, 0.5f); // specular lighting doesn't have full effect on this object's material
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

QList<QtProperty *> Course_2_3_1_materials::getPropertyList(QtVariantPropertyManager *manager)
{
    GETPROPERTYLIST(Course_2_3_1_materials)
}
