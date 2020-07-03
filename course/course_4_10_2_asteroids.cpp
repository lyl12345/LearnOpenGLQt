#include "course_4_10_2_asteroids.h"
#include <QDir>
#include <QDebug>
#include "stb_image.h"

Course_4_10_2_asteroids::Course_4_10_2_asteroids()
    :CourseWithCamera()
{
    mCamera = Camera(QVector3D(0.0f, 0.0f, 55.0f));
    initializeOpenGLFunctions();
    glEnable(GL_DEPTH_TEST);

    QString shaderPath = QDir::currentPath() + "/shaders/4.advanced_opengl/10.2.asteroids/";
    mProgram.addShaderFromSourceFile(QOpenGLShader::Vertex,shaderPath+"10.2.instancing.vs");
    mProgram.addShaderFromSourceFile(QOpenGLShader::Fragment,shaderPath+"10.2.instancing.fs");
    mProgram.link();

    QString path = QDir::currentPath() + "/resources/objects/rock/rock.obj";
    mRock = new Model(path.toStdString().c_str());
    path = QDir::currentPath() + "/resources/objects/planet/planet.obj";
    mPlanet = new Model(path.toStdString().c_str());

    amount = 1000;
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

}

Course_4_10_2_asteroids::~Course_4_10_2_asteroids()
{
    delete mRock;
    delete mPlanet;
    delete[] modelMatrices;
}

void Course_4_10_2_asteroids::render()
{
    Course::render();

    processInput();

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // configure transformation matrices
    QMatrix4x4 projection;
    projection.perspective(45.0f, 800 / 600 , 0.1f , 100);
    QMatrix4x4 view = mCamera.GetViewMatrix();
    mProgram.bind();
    mProgram.setUniformValue("projection", projection);
    mProgram.setUniformValue("view", view);

    // draw planet
    QMatrix4x4 model;
    model.translate(QVector3D(0.0f, -3.0f, 0.0f));
    model.scale(QVector3D(4.0f, 4.0f, 4.0f));
    mProgram.setUniformValue("model", model);
    mPlanet->Draw(&mProgram);

    // draw meteorites
    for (unsigned int i = 0; i < amount; i++)
    {
        mProgram.setUniformValue("model", modelMatrices[i]);
        mRock->Draw(&mProgram);
    }
}

QList<QtProperty *> Course_4_10_2_asteroids::getPropertyList(QtVariantPropertyManager *manager)
{
    GETPROPERTYLIST(Course_4_10_2_asteroids)
}
