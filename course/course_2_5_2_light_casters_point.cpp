#include "course_2_5_2_light_casters_point.h"
#include <QDir>
#include <QDebug>
#include "stb_image.h"
#include <QMouseEvent>
#include <qmath.h>
#include <QVector3D>

Course_2_5_2_light_casters_point::Course_2_5_2_light_casters_point()
    :CourseWithCamera()
    ,lightPos(QVector3D(1.2f, 1.0f, 2.0f))
{
    initializeOpenGLFunctions();

    glEnable(GL_DEPTH_TEST);

    QString shaderPath = QDir::currentPath() + "/shaders/2.lighting/5.2.light_casters_point/";
    mLightingProgram.addShaderFromSourceFile(QOpenGLShader::Vertex,shaderPath+"5.2.light_casters.vs");
    mLightingProgram.addShaderFromSourceFile(QOpenGLShader::Fragment,shaderPath+"5.2.light_casters.fs");
    mLightingProgram.link();

    mLightCubeProgram.addShaderFromSourceFile(QOpenGLShader::Vertex,shaderPath+"5.2.light_cube.vs");
    mLightCubeProgram.addShaderFromSourceFile(QOpenGLShader::Fragment,shaderPath+"5.2.light_cube.fs");
    mLightCubeProgram.link();

    float vertices[] = {
        // positions          // normals           // texture coords
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
        0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
        0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
        0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
        0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

        0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
        0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
        0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
        0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
        0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
        0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
        0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
        0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
        0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
    };

    glGenVertexArrays(1, &cubeVAO);
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindVertexArray(cubeVAO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glGenVertexArrays(1, &lightCubeVAO);
    glBindVertexArray(lightCubeVAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // note that we update the lamp's position attribute's stride to reflect the updated buffer data
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    QString texturePath = QDir::currentPath() + "/resources/textures/container2.png";
    diffuseMap = loadTexture(texturePath.toStdString().c_str());
    texturePath = QDir::currentPath() + "/resources/textures/container2_specular.png";
    specularMap = loadTexture(texturePath.toStdString().c_str());

    mLightingProgram.bind();
    mLightingProgram.setUniformValue("material.diffuse", 0);
    mLightingProgram.setUniformValue("material.specular", 1);
}

Course_2_5_2_light_casters_point::~Course_2_5_2_light_casters_point()
{
    glDeleteVertexArrays(1, &cubeVAO);
    glDeleteVertexArrays(1, &lightCubeVAO);
    glDeleteTextures(1, &diffuseMap);
    glDeleteTextures(1, &specularMap);
    glDeleteBuffers(1, &VBO);
}

void Course_2_5_2_light_casters_point::render()
{
    Course::render();

    processInput();

    // positions all containers
    QVector3D cubePositions[] = {
        QVector3D( 0.0f,  0.0f,  0.0f),
        QVector3D( 2.0f,  5.0f, -15.0f),
        QVector3D(-1.5f, -2.2f, -2.5f),
        QVector3D(-3.8f, -2.0f, -12.3f),
        QVector3D( 2.4f, -0.4f, -3.5f),
        QVector3D(-1.7f,  3.0f, -7.5f),
        QVector3D( 1.3f, -2.0f, -2.5f),
        QVector3D( 1.5f,  2.0f, -2.5f),
        QVector3D( 1.5f,  0.2f, -1.5f),
        QVector3D(-1.3f,  1.0f, -1.5f)
    };

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // be sure to activate shader when setting uniforms/drawing objects
    mLightingProgram.bind();
    mLightingProgram.setUniformValue("light.position", lightPos);
    mLightingProgram.setUniformValue("viewPos", mCamera.Position);

    // light properties
    mLightingProgram.setUniformValue("light.ambient", 0.2f, 0.2f, 0.2f);
    mLightingProgram.setUniformValue("light.diffuse", 0.5f, 0.5f, 0.5f);
    mLightingProgram.setUniformValue("light.specular", 1.0f, 1.0f, 1.0f);
    mLightingProgram.setUniformValue("light.constant", 1.0f);
    mLightingProgram.setUniformValue("light.linear", 0.09f);
    mLightingProgram.setUniformValue("light.quadratic", 0.032f);

    // material properties
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

    // bind diffuse map
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, diffuseMap);
    // bind specular map
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, specularMap);

    // render containers
    glBindVertexArray(cubeVAO);
    for (unsigned int i = 0; i < 10; i++)
    {
        // calculate the model matrix for each object and pass it to shader before drawing
        model.setToIdentity();
        model.translate(cubePositions[i]);
        float angle = 20.0f * i;
        model.rotate(angle, QVector3D(1.0f, 0.3f, 0.5f));
        mLightingProgram.setUniformValue("model", model);

        glDrawArrays(GL_TRIANGLES, 0, 36);
    }

    // also draw the lamp object
    mLightCubeProgram.bind();
    mLightCubeProgram.setUniformValue("projection", projection);
    mLightCubeProgram.setUniformValue("view", view);
    model.setToIdentity();
    model.translate(lightPos);
    model.scale(QVector3D(0.2f, 0.2f, 0.2f));
    mLightCubeProgram.setUniformValue("model", model);

    glBindVertexArray(lightCubeVAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
}

QList<QtProperty *> Course_2_5_2_light_casters_point::getPropertyList(QtVariantPropertyManager *manager)
{
    GETPROPERTYLIST(Course_2_5_2_light_casters_point)
}
