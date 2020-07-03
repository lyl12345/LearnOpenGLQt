#ifndef COURSE_1_7_3_CAMERA_MOUSE_ZOOM_H
#define COURSE_1_7_3_CAMERA_MOUSE_ZOOM_H

#include "course.h"
#include <QOpenGLExtraFunctions>
#include <QOpenGLShaderProgram>
#include <QMatrix4x4>

class Course_1_7_3_camera_mouse_zoom : public Course, protected QOpenGLExtraFunctions
{
public:
    Course_1_7_3_camera_mouse_zoom();
    virtual ~Course_1_7_3_camera_mouse_zoom();

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

    QVector3D mCameraPos, mCameraFront, mCameraUp;
    QSet<int> mPressedKey;

    bool mMousePressed;
    float mYaw, mPitch, mLastX, mLastY, mFov;
};

#endif // COURSE_1_7_3_CAMERA_MOUSE_ZOOM_H
