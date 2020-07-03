#include "course_4_9_3_geometry_shader_normals.h"
#include <QDir>
#include <QDebug>
#include "stb_image.h"

Course_4_9_3_geometry_shader_normals::Course_4_9_3_geometry_shader_normals()
    :CourseWithCamera()
{
    initializeOpenGLFunctions();
    mCamera = Camera(QVector3D(0,0,8));
    glEnable(GL_DEPTH_TEST);

    QString shaderPath = QDir::currentPath() + "/shaders/4.advanced_opengl/9.3.geometry_shader_normals/";
    mProgram.addShaderFromSourceFile(QOpenGLShader::Vertex,shaderPath+"9.3.default.vs");
    mProgram.addShaderFromSourceFile(QOpenGLShader::Fragment,shaderPath+"9.3.default.fs");
    mProgram.link();

    mNormalProgram.addShaderFromSourceFile(QOpenGLShader::Vertex,shaderPath+"9.3.normal_visualization.vs");
    mNormalProgram.addShaderFromSourceFile(QOpenGLShader::Fragment,shaderPath+"9.3.normal_visualization.fs");
    mNormalProgram.addShaderFromSourceFile(QOpenGLShader::Geometry,shaderPath+"9.3.normal_visualization.gs");
    mProgram.link();

    stbi_set_flip_vertically_on_load(true);
    QString path = QDir::currentPath() + "/resources/objects/backpack/backpack.obj";
    mModel = new Model(path.toStdString().c_str());
    stbi_set_flip_vertically_on_load(false);
}

Course_4_9_3_geometry_shader_normals::~Course_4_9_3_geometry_shader_normals()
{
    delete mModel;
}

void Course_4_9_3_geometry_shader_normals::render()
{
    Course::render();

    processInput();

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // configure transformation matrices
    QMatrix4x4 projection;
    projection.perspective(45.0f, 800 / 600, 1.0f, 100.0f);
    QMatrix4x4 view = mCamera.GetViewMatrix();
    QMatrix4x4 model;
    mProgram.bind();
    mProgram.setUniformValue("projection", projection);
    mProgram.setUniformValue("view", view);
    mProgram.setUniformValue("model", model);

    // draw model as usual
    mModel->Draw(&mProgram);

    // then draw model with normal visualizing geometry shader
    mNormalProgram.bind();
    mNormalProgram.setUniformValue("projection", projection);
    mNormalProgram.setUniformValue("view", view);
    mNormalProgram.setUniformValue("model", model);

    mModel->Draw(&mNormalProgram);
}

QList<QtProperty *> Course_4_9_3_geometry_shader_normals::getPropertyList(QtVariantPropertyManager *manager)
{
    GETPROPERTYLIST(Course_4_9_3_geometry_shader_normals)
}
