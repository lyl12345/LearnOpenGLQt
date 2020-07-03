#ifndef COURSE_1_7_4_CAMERA_CLASS_H
#define COURSE_1_7_4_CAMERA_CLASS_H

#include "course.h"
#include <QOpenGLExtraFunctions>
#include <QOpenGLShaderProgram>
#include <QMatrix4x4>
#include "core/camera.h"

class Course_1_7_4_camera_class : public Course, protected QOpenGLExtraFunctions
{
public:
    Course_1_7_4_camera_class();
    virtual ~Course_1_7_4_camera_class();

    void render() override;
    virtual QList<QtProperty*> getPropertyList(QtVariantPropertyManager *manager) override;

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void wheelEvent(QWheelEvent*event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;

    void processInput();

private:
    unsigned int VBO, VAO;
    unsigned int texture1, texture2;
    QMatrix4x4 mModel, mView, mProjection;
    QOpenGLShaderProgram *mProgram;

    QSet<int> mPressedKey;

    bool mMousePressed;
    float  mLastX, mLastY;
    Camera mCamera;
};

#endif // COURSE_1_7_4_CAMERA_CLASS_H
