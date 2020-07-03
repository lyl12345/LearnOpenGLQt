#include "course_3_1_1_model_loading.h"
#include <QDir>
#include <QDebug>
#include "stb_image.h"

Course_3_1_1_model_loading::Course_3_1_1_model_loading()
    :CourseWithCamera()
{
    initializeOpenGLFunctions();
    mCamera = Camera(QVector3D(0,0,8));
    glEnable(GL_DEPTH_TEST);

    QString shaderPath = QDir::currentPath() + "/shaders/3.model_loading/1.model_loading/";
    mProgram.addShaderFromSourceFile(QOpenGLShader::Vertex,shaderPath+"1.model_loading.vs");
    mProgram.addShaderFromSourceFile(QOpenGLShader::Fragment,shaderPath+"1.model_loading.fs");
    mProgram.link();

    stbi_set_flip_vertically_on_load(true);
    QString path = QDir::currentPath() + "/resources/objects/backpack/backpack.obj";
    mModel = new Model(path.toStdString().c_str());
    stbi_set_flip_vertically_on_load(false);
}

Course_3_1_1_model_loading::~Course_3_1_1_model_loading()
{

    delete mModel;
}

void Course_3_1_1_model_loading::render()
{
    Course::render();

    processInput();

    glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // don't forget to enable shader before setting uniforms
    mProgram.bind();

    // view/projection transformations
    QMatrix4x4 projection;
    projection.perspective(mCamera.Zoom, 800/600, 0.1f, 100.0f);
    QMatrix4x4 view = mCamera.GetViewMatrix();
    mProgram.setUniformValue("projection", projection);
    mProgram.setUniformValue("view", view);

    // render the loaded model
    QMatrix4x4 model;
    model.translate(QVector3D(0.0f, 0.0f, 0.0f));
    model.scale(QVector3D(1.0f, 1.0f, 1.0f));

    mProgram.setUniformValue("model", model);
    mModel->Draw(&mProgram);
    mProgram.release();
}

QList<QtProperty *> Course_3_1_1_model_loading::getPropertyList(QtVariantPropertyManager *manager)
{
    GETPROPERTYLIST(Course_3_1_1_model_loading)
}
