#include "course_5_1_1_advanced_lighting.h"
#include <QDir>
#include <QDebug>
#include "stb_image.h"

Course_5_1_1_advanced_lighting::Course_5_1_1_advanced_lighting()
    :CourseWithCamera()
    ,blinn(false)
    ,blinnKeyPressed(false)
{
    initializeOpenGLFunctions();
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    QString shaderPath = QDir::currentPath() + "/shaders/5.advanced_lighting/1.advanced_lighting/";
    mProgram.addShaderFromSourceFile(QOpenGLShader::Vertex,shaderPath+"1.advanced_lighting.vs");
    mProgram.addShaderFromSourceFile(QOpenGLShader::Fragment,shaderPath+"1.advanced_lighting.fs");
    mProgram.link();

    float planeVertices[] = {
        // positions            // normals         // texcoords
         10.0f, -0.5f,  10.0f,  0.0f, 1.0f, 0.0f,  10.0f,  0.0f,
        -10.0f, -0.5f,  10.0f,  0.0f, 1.0f, 0.0f,   0.0f,  0.0f,
        -10.0f, -0.5f, -10.0f,  0.0f, 1.0f, 0.0f,   0.0f, 10.0f,

         10.0f, -0.5f,  10.0f,  0.0f, 1.0f, 0.0f,  10.0f,  0.0f,
        -10.0f, -0.5f, -10.0f,  0.0f, 1.0f, 0.0f,   0.0f, 10.0f,
         10.0f, -0.5f, -10.0f,  0.0f, 1.0f, 0.0f,  10.0f, 10.0f
    };

    glGenVertexArrays(1, &planeVAO);
    glGenBuffers(1, &planeVBO);
    glBindVertexArray(planeVAO);
    glBindBuffer(GL_ARRAY_BUFFER, planeVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(planeVertices), planeVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glBindVertexArray(0);

    QString path = QDir::currentPath() + "/resources/textures/wood.png";
    floorTexture = loadTexture(path.toStdString().c_str());
    mProgram.bind();
    mProgram.setUniformValue("texture1", 0);
    mProgram.release();

    lightPos = QVector3D(0.0f, 0.0f, 0.0f);
}

Course_5_1_1_advanced_lighting::~Course_5_1_1_advanced_lighting()
{
    glDisable(GL_BLEND);
    glDeleteVertexArrays(1, &planeVAO);
    glDeleteBuffers(1, &planeVBO);
    glDeleteTextures(1, &floorTexture);
}

void Course_5_1_1_advanced_lighting::render()
{
    Course::render();

    processInput();

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // draw objects
    mProgram.bind();
    QMatrix4x4 projection;
    projection.perspective(mCamera.Zoom, 800 / 600, 1.0f, 100.0f);
    QMatrix4x4 view = mCamera.GetViewMatrix();
    mProgram.bind();
    mProgram.setUniformValue("projection", projection);
    mProgram.setUniformValue("view", view);
    // set light uniforms
    mProgram.setUniformValue("viewPos", mCamera.Position);
    mProgram.setUniformValue("lightPos", lightPos);
    mProgram.setUniformValue("blinn", blinn);
    // floor
    glBindVertexArray(planeVAO);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, floorTexture);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

QList<QtProperty *> Course_5_1_1_advanced_lighting::getPropertyList(QtVariantPropertyManager *manager)
{
    GETPROPERTYLIST(Course_5_1_1_advanced_lighting)
}

void Course_5_1_1_advanced_lighting::processInput()
{
    CourseWithCamera::processInput();

    if (mPressedKey.contains(Qt::Key_B) && !blinnKeyPressed){
        blinn = !blinn;
        blinnKeyPressed = true;
    }
    if (!mPressedKey.contains(Qt::Key_B)){
        blinnKeyPressed = false;
    }
}
