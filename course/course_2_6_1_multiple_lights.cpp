#include "course_2_6_1_multiple_lights.h"
#include <QDir>
#include <QDebug>
#include "stb_image.h"
#include <qmath.h>

Course_2_6_1_multiple_lights::Course_2_6_1_multiple_lights()
    :CourseWithCamera()
{
    initializeOpenGLFunctions();

    glEnable(GL_DEPTH_TEST);

    QString shaderPath = QDir::currentPath() + "/shaders/2.lighting/6.multiple_lights/";
    mLightingProgram.addShaderFromSourceFile(QOpenGLShader::Vertex,shaderPath+"6.multiple_lights.vs");
    mLightingProgram.addShaderFromSourceFile(QOpenGLShader::Fragment,shaderPath+"6.multiple_lights.fs");
    mLightingProgram.link();

    mLightCubeProgram.addShaderFromSourceFile(QOpenGLShader::Vertex,shaderPath+"6.light_cube.vs");
    mLightCubeProgram.addShaderFromSourceFile(QOpenGLShader::Fragment,shaderPath+"6.light_cube.fs");
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

Course_2_6_1_multiple_lights::~Course_2_6_1_multiple_lights()
{
    glDeleteVertexArrays(1, &cubeVAO);
    glDeleteVertexArrays(1, &lightCubeVAO);
    glDeleteTextures(1, &diffuseMap);
    glDeleteTextures(1, &specularMap);
    glDeleteBuffers(1, &VBO);
}

void Course_2_6_1_multiple_lights::render()
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
    // positions of the point lights
    QVector3D pointLightPositions[] = {
        QVector3D( 0.7f,  0.2f,  2.0f),
        QVector3D( 2.3f, -3.3f, -4.0f),
        QVector3D(-4.0f,  2.0f, -12.0f),
        QVector3D( 0.0f,  0.0f, -3.0f)
    };

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // be sure to activate shader when setting uniforms/drawing objects
    mLightingProgram.bind();
    mLightingProgram.setUniformValue("viewPos", mCamera.Position);
    mLightingProgram.setUniformValue("material.shininess", 32.0f);

    /*
       Here we set all the uniforms for the 5/6 types of lights we have. We have to set them manually and index
       the proper PointLight struct in the array to set each uniform variable. This can be done more code-friendly
       by defining light types as classes and set their values in there, or by using a more efficient uniform approach
       by using 'Uniform buffer objects', but that is something we'll discuss in the 'Advanced GLSL' tutorial.
    */
    // directional light
    mLightingProgram.setUniformValue("dirLight.direction", -0.2f, -1.0f, -0.3f);
    mLightingProgram.setUniformValue("dirLight.ambient", 0.05f, 0.05f, 0.05f);
    mLightingProgram.setUniformValue("dirLight.diffuse", 0.4f, 0.4f, 0.4f);
    mLightingProgram.setUniformValue("dirLight.specular", 0.5f, 0.5f, 0.5f);
    // point light 1
    mLightingProgram.setUniformValue("pointLights[0].position", pointLightPositions[0]);
    mLightingProgram.setUniformValue("pointLights[0].ambient", 0.05f, 0.05f, 0.05f);
    mLightingProgram.setUniformValue("pointLights[0].diffuse", 0.8f, 0.8f, 0.8f);
    mLightingProgram.setUniformValue("pointLights[0].specular", 1.0f, 1.0f, 1.0f);
    mLightingProgram.setUniformValue("pointLights[0].constant", 1.0f);
    mLightingProgram.setUniformValue("pointLights[0].linear", 0.09f);
    mLightingProgram.setUniformValue("pointLights[0].quadratic", 0.032f);
    // point light 2
    mLightingProgram.setUniformValue("pointLights[1].position", pointLightPositions[1]);
    mLightingProgram.setUniformValue("pointLights[1].ambient", 0.05f, 0.05f, 0.05f);
    mLightingProgram.setUniformValue("pointLights[1].diffuse", 0.8f, 0.8f, 0.8f);
    mLightingProgram.setUniformValue("pointLights[1].specular", 1.0f, 1.0f, 1.0f);
    mLightingProgram.setUniformValue("pointLights[1].constant", 1.0f);
    mLightingProgram.setUniformValue("pointLights[1].linear", 0.09f);
    mLightingProgram.setUniformValue("pointLights[1].quadratic", 0.032f);
    // point light 3
    mLightingProgram.setUniformValue("pointLights[2].position", pointLightPositions[2]);
    mLightingProgram.setUniformValue("pointLights[2].ambient", 0.05f, 0.05f, 0.05f);
    mLightingProgram.setUniformValue("pointLights[2].diffuse", 0.8f, 0.8f, 0.8f);
    mLightingProgram.setUniformValue("pointLights[2].specular", 1.0f, 1.0f, 1.0f);
    mLightingProgram.setUniformValue("pointLights[2].constant", 1.0f);
    mLightingProgram.setUniformValue("pointLights[2].linear", 0.09f);
    mLightingProgram.setUniformValue("pointLights[2].quadratic", 0.032f);
    // point light 4
    mLightingProgram.setUniformValue("pointLights[3].position", pointLightPositions[3]);
    mLightingProgram.setUniformValue("pointLights[3].ambient", 0.05f, 0.05f, 0.05f);
    mLightingProgram.setUniformValue("pointLights[3].diffuse", 0.8f, 0.8f, 0.8f);
    mLightingProgram.setUniformValue("pointLights[3].specular", 1.0f, 1.0f, 1.0f);
    mLightingProgram.setUniformValue("pointLights[3].constant", 1.0f);
    mLightingProgram.setUniformValue("pointLights[3].linear", 0.09f);
    mLightingProgram.setUniformValue("pointLights[3].quadratic", 0.032f);
    // spotLight
    mLightingProgram.setUniformValue("spotLight.position", mCamera.Position);
    mLightingProgram.setUniformValue("spotLight.direction", mCamera.Front);
    mLightingProgram.setUniformValue("spotLight.ambient", 0.0f, 0.0f, 0.0f);
    mLightingProgram.setUniformValue("spotLight.diffuse", 1.0f, 1.0f, 1.0f);
    mLightingProgram.setUniformValue("spotLight.specular", 1.0f, 1.0f, 1.0f);
    mLightingProgram.setUniformValue("spotLight.constant", 1.0f);
    mLightingProgram.setUniformValue("spotLight.linear", 0.09f);
    mLightingProgram.setUniformValue("spotLight.quadratic", 0.032f);
    mLightingProgram.setUniformValue("spotLight.cutOff", (float)cos(qDegreesToRadians(12.5f)));
    mLightingProgram.setUniformValue("spotLight.outerCutOff", (float)cos(qDegreesToRadians(15.0f)));

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

     // also draw the lamp object(s)
     mLightCubeProgram.bind();
     mLightCubeProgram.setUniformValue("projection", projection);
     mLightCubeProgram.setUniformValue("view", view);

     // we now draw as many light bulbs as we have point lights.
     glBindVertexArray(lightCubeVAO);
     for (unsigned int i = 0; i < 4; i++)
     {
         model.setToIdentity();
         model.translate(pointLightPositions[i]);
         model.scale(QVector3D(0.2f, 0.2f, 0.2f));
         mLightCubeProgram.setUniformValue("model", model);

         glDrawArrays(GL_TRIANGLES, 0, 36);
     }
}

QList<QtProperty *> Course_2_6_1_multiple_lights::getPropertyList(QtVariantPropertyManager *manager)
{
    GETPROPERTYLIST(Course_2_6_1_multiple_lights)
}
