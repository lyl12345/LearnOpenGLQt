#include "course_4_9_2_geometry_shader_exploding.h"
#include <QDir>
#include <QDebug>
#include "stb_image.h"

Course_4_9_2_geometry_shader_exploding::Course_4_9_2_geometry_shader_exploding()
    :CourseWithCamera()
{
    initializeOpenGLFunctions();
    glEnable(GL_DEPTH_TEST);

    QString shaderPath = QDir::currentPath() + "/shaders/4.advanced_opengl/9.2.geometry_shader_exploding/";
    mProgram.addShaderFromSourceFile(QOpenGLShader::Vertex,shaderPath+"9.2.geometry_shader.vs");
    mProgram.addShaderFromSourceFile(QOpenGLShader::Fragment,shaderPath+"9.2.geometry_shader.fs");
    mProgram.addShaderFromSourceFile(QOpenGLShader::Geometry,shaderPath+"9.2.geometry_shader.gs");
    mProgram.link();

    QString path = QDir::currentPath() + "/resources/objects/nanosuit/nanosuit.obj";
    mModel = new Model(path.toStdString().c_str());

    mCamera = QVector3D(0, 0, 36);
}

Course_4_9_2_geometry_shader_exploding::~Course_4_9_2_geometry_shader_exploding()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    delete mModel;
}

void Course_4_9_2_geometry_shader_exploding::render()
{
    Course::render();

    processInput();

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // configure transformation matrices
    QMatrix4x4 projection;
    projection.perspective(mCamera.Zoom, 800 / 600, 0.1f, 100);
    QMatrix4x4 view = mCamera.GetViewMatrix();
    QMatrix4x4 model;

    mProgram.bind();
    mProgram.setUniformValue("projection", projection);
    mProgram.setUniformValue("view", view);
    mProgram.setUniformValue("model", model);
    // add time component to geometry shader in the form of a uniform
    mProgram.setUniformValue("time", (float)mDuration);

    // draw model
    mModel->Draw(&mProgram);

}

QList<QtProperty *> Course_4_9_2_geometry_shader_exploding::getPropertyList(QtVariantPropertyManager *manager)
{
    GETPROPERTYLIST(Course_4_9_2_geometry_shader_exploding)
}
