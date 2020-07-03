#include "course_4_8_1_advanced_glsl_ubo.h"
#include <QDir>
#include <QDebug>
#include "stb_image.h"

Course_4_8_1_advanced_glsl_ubo::Course_4_8_1_advanced_glsl_ubo()
    :CourseWithCamera()
{
    initializeOpenGLFunctions();

    glEnable(GL_DEPTH_TEST);

    QString shaderPath = QDir::currentPath() + "/shaders/4.advanced_opengl/8.advanced_glsl_ubo/";
    mRedProgram.addShaderFromSourceFile(QOpenGLShader::Vertex,shaderPath+"8.advanced_glsl.vs");
    mRedProgram.addShaderFromSourceFile(QOpenGLShader::Fragment,shaderPath+"8.red.fs");
    mRedProgram.link();

    mGreenProgram.addShaderFromSourceFile(QOpenGLShader::Vertex,shaderPath+"8.advanced_glsl.vs");
    mGreenProgram.addShaderFromSourceFile(QOpenGLShader::Fragment,shaderPath+"8.green.fs");
    mGreenProgram.link();

    mBlueProgram.addShaderFromSourceFile(QOpenGLShader::Vertex,shaderPath+"8.advanced_glsl.vs");
    mBlueProgram.addShaderFromSourceFile(QOpenGLShader::Fragment,shaderPath+"8.blue.fs");
    mBlueProgram.link();

    mYellowProgram.addShaderFromSourceFile(QOpenGLShader::Vertex,shaderPath+"8.advanced_glsl.vs");
    mYellowProgram.addShaderFromSourceFile(QOpenGLShader::Fragment,shaderPath+"8.yellow.fs");
    mYellowProgram.link();

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
         -0.5f,  0.5f, -0.5f,
     };

    glGenVertexArrays(1, &cubeVAO);
    glGenBuffers(1, &cubeVBO);
    glBindVertexArray(cubeVAO);
    glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), &cubeVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    unsigned int uniformBlockIndexRed = glGetUniformBlockIndex(mRedProgram.programId(), "Matrices");
    unsigned int uniformBlockIndexGreen = glGetUniformBlockIndex(mGreenProgram.programId(), "Matrices");
    unsigned int uniformBlockIndexBlue = glGetUniformBlockIndex(mBlueProgram.programId(), "Matrices");
    unsigned int uniformBlockIndexYellow = glGetUniformBlockIndex(mYellowProgram.programId(), "Matrices");
    // then we link each shader's uniform block to this uniform binding point
    glUniformBlockBinding(mRedProgram.programId(), uniformBlockIndexRed, 0);
    glUniformBlockBinding(mGreenProgram.programId(), uniformBlockIndexGreen, 0);
    glUniformBlockBinding(mBlueProgram.programId(), uniformBlockIndexBlue, 0);
    glUniformBlockBinding(mYellowProgram.programId(), uniformBlockIndexYellow, 0);
    // Now actually create the buffer
    glGenBuffers(1, &uboMatrices);
    glBindBuffer(GL_UNIFORM_BUFFER, uboMatrices);
    glBufferData(GL_UNIFORM_BUFFER, 2 * 64, NULL, GL_STATIC_DRAW);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
    // define the range of the buffer that links to a uniform binding point
    glBindBufferRange(GL_UNIFORM_BUFFER, 0, uboMatrices, 0, 2 * 64);

    // store the projection matrix (we only do this once now) (note: we're not using zoom anymore by changing the FoV)
    QMatrix4x4 projection;
    projection.perspective(45.0f, (float)800 / (float)600, 0.1f, 100.0f);
    glBindBuffer(GL_UNIFORM_BUFFER, uboMatrices);
    glBufferSubData(GL_UNIFORM_BUFFER, 0, 64, projection.data());
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

Course_4_8_1_advanced_glsl_ubo::~Course_4_8_1_advanced_glsl_ubo()
{
    glDeleteVertexArrays(1, &cubeVAO);
    glDeleteBuffers(1, &cubeVBO);
    glDeleteBuffers(1, &uboMatrices);
}

void Course_4_8_1_advanced_glsl_ubo::render()
{
    Course::render();

    processInput();

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // set the view and projection matrix in the uniform block - we only have to do this once per loop iteration.
    QMatrix4x4 view = mCamera.GetViewMatrix();
    glBindBuffer(GL_UNIFORM_BUFFER, uboMatrices);
    glBufferSubData(GL_UNIFORM_BUFFER, 64, 64, view.data());
    glBindBuffer(GL_UNIFORM_BUFFER, 0);

    // draw 4 cubes
    // RED
    glBindVertexArray(cubeVAO);
    mRedProgram.bind();
    QMatrix4x4 model;
    model.translate(QVector3D(-0.75f, 0.75f, 0.0f)); // move top-left
    mRedProgram.setUniformValue("model", model);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    // GREEN
    mGreenProgram.bind();
    model.setToIdentity();
    model.translate(QVector3D(0.75f, 0.75f, 0.0f)); // move top-right
    mGreenProgram.setUniformValue("model", model);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    // YELLOW
    mYellowProgram.bind();
    model.setToIdentity();
    model.translate(QVector3D(-0.75f, -0.75f, 0.0f)); // move bottom-left
    mYellowProgram.setUniformValue("model", model);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    // BLUE
    mBlueProgram.bind();
    model.setToIdentity();
    model.translate(QVector3D(0.75f, -0.75f, 0.0f)); // move bottom-right
    mBlueProgram.setUniformValue("model", model);
    glDrawArrays(GL_TRIANGLES, 0, 36);
}

QList<QtProperty *> Course_4_8_1_advanced_glsl_ubo::getPropertyList(QtVariantPropertyManager *manager)
{
    GETPROPERTYLIST(Course_4_8_1_advanced_glsl_ubo)
}
