#include "course_4_10_3_asteroids_instanced.h"
#include <QDir>
#include <QDebug>
#include "stb_image.h"

Course_4_10_3_asteroids_instanced::Course_4_10_3_asteroids_instanced()
    :CourseWithCamera()
{
    mCamera = Camera(QVector3D(0.0f, 0.0f, 155.0f));
    initializeOpenGLFunctions();
    glEnable(GL_DEPTH_TEST);

    QString shaderPath = QDir::currentPath() + "/shaders/4.advanced_opengl/10.3.asteroids_instanced/";
    mAsteroidProgram.addShaderFromSourceFile(QOpenGLShader::Vertex,shaderPath+"10.3.asteroids.vs");
    mAsteroidProgram.addShaderFromSourceFile(QOpenGLShader::Fragment,shaderPath+"10.3.asteroids.fs");
    mAsteroidProgram.link();

    mPlanetProgram.addShaderFromSourceFile(QOpenGLShader::Vertex,shaderPath+"10.3.planet.vs");
    mPlanetProgram.addShaderFromSourceFile(QOpenGLShader::Fragment,shaderPath+"10.3.planet.fs");
    mPlanetProgram.link();

    QString path = QDir::currentPath() + "/resources/objects/rock/rock.obj";
    mRock = new Model(path.toStdString().c_str());
    path = QDir::currentPath() + "/resources/objects/planet/planet.obj";
    mPlanet = new Model(path.toStdString().c_str());

    amount = 100000;
    modelMatrices = new QMatrix4x4[amount];
    srand(mDuration); // initialize random seed
    float radius = 50.0;
    float offset = 2.5f;
    for (unsigned int i = 0; i < amount; i++)
    {
        QMatrix4x4 model;
        // 1. translation: displace along circle with 'radius' in range [-offset, offset]
        float angle = (float)i / (float)amount * 360.0f;
        float displacement = (rand() % (int)(2 * offset * 100)) / 100.0f - offset;
        float x = sin(angle) * radius + displacement;
        displacement = (rand() % (int)(2 * offset * 100)) / 100.0f - offset;
        float y = displacement * 0.4f; // keep height of asteroid field smaller compared to width of x and z
        displacement = (rand() % (int)(2 * offset * 100)) / 100.0f - offset;
        float z = cos(angle) * radius + displacement;
        model.translate(QVector3D(x, y, z));

        // 2. scale: Scale between 0.05 and 0.25f
        float scale = (rand() % 20) / 100.0f + 0.05;
        model.scale(QVector3D(scale, scale, scale));

        // 3. rotation: add random rotation around a (semi)randomly picked rotation axis vector
        float rotAngle = (rand() % 360);
        model.rotate(rotAngle, QVector3D(0.4f, 0.6f, 0.8f));

        // 4. now add to list of matrices
        modelMatrices[i] = model;
    }

    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, amount * sizeof(QMatrix4x4), &modelMatrices[0], GL_STATIC_DRAW);

    for (unsigned int i = 0; i < mRock->meshes.size(); i++)
    {
        unsigned int VAO = mRock->meshes[i].VAO;
        glBindVertexArray(VAO);
        // set attribute pointers for matrix (4 times vec4)
        glEnableVertexAttribArray(3);
        glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(QMatrix4x4), (void*)0);
        glEnableVertexAttribArray(4);
        glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(QMatrix4x4), (void*)(sizeof(QVector4D)));
        glEnableVertexAttribArray(5);
        glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(QMatrix4x4), (void*)(2 * sizeof(QVector4D)));
        glEnableVertexAttribArray(6);
        glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(QMatrix4x4), (void*)(3 * sizeof(QVector4D)));

        glVertexAttribDivisor(3, 1);
        glVertexAttribDivisor(4, 1);
        glVertexAttribDivisor(5, 1);
        glVertexAttribDivisor(6, 1);

        glBindVertexArray(0);
    }
}

Course_4_10_3_asteroids_instanced::~Course_4_10_3_asteroids_instanced()
{
    glDeleteBuffers(1, &buffer);
    delete mRock;
    delete mPlanet;
    delete [] modelMatrices;
}

void Course_4_10_3_asteroids_instanced::render()
{
    Course::render();

    processInput();

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // configure transformation matrices
    QMatrix4x4 projection;
    projection.perspective(45.0f, (float)800 / (float)600, 0.1f, 1000.0f);
    QMatrix4x4 view = mCamera.GetViewMatrix();
    mAsteroidProgram.bind();
    mAsteroidProgram.setUniformValue("projection", projection);
    mAsteroidProgram.setUniformValue("view", view);
    mPlanetProgram.bind();
    mPlanetProgram.setUniformValue("projection", projection);
    mPlanetProgram.setUniformValue("view", view);

    // draw planet
    QMatrix4x4 model;
    model.translate(QVector3D(0.0f, -3.0f, 0.0f));
    model.scale(QVector3D(4.0f, 4.0f, 4.0f));
    mPlanetProgram.setUniformValue("model", model);
    mPlanet->Draw(&mPlanetProgram);

    // draw meteorites
    mAsteroidProgram.bind();
    mAsteroidProgram.setUniformValue("texture_diffuse1", 0);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, mRock->textures_loaded[0].id); // note: we also made the textures_loaded vector public (instead of private) from the model class.
    for (unsigned int i = 0; i < mRock->meshes.size(); i++)
    {
        glBindVertexArray(mRock->meshes[i].VAO);
        glDrawElementsInstanced(GL_TRIANGLES, mRock->meshes[i].indices.size(), GL_UNSIGNED_INT, 0, amount);
        glBindVertexArray(0);
    }
}

QList<QtProperty *> Course_4_10_3_asteroids_instanced::getPropertyList(QtVariantPropertyManager *manager)
{
    GETPROPERTYLIST(Course_4_10_3_asteroids_instanced)
}
