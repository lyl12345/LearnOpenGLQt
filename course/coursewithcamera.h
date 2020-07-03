#ifndef COURSEWITHCAMERA_H
#define COURSEWITHCAMERA_H

#include "course.h"
#include <QOpenGLExtraFunctions>
#include <QOpenGLShaderProgram>
#include <QMatrix4x4>
#include "core/camera.h"

class CourseWithCamera : public Course, protected QOpenGLExtraFunctions
{
public:
    CourseWithCamera(QObject *parent = nullptr);
    virtual ~CourseWithCamera();

protected:
    void enter(QEvent *event) override;
    void leave(QEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void wheelEvent(QWheelEvent*event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;

    virtual void processInput();
    virtual unsigned int loadTexture(char const * path, bool gammaCorrection = false);
    virtual unsigned int loadTexture2(char const * path, bool gammaCorrection = false);
    virtual unsigned int loadTexture3(char const * path, bool gammaCorrection = false);
    virtual unsigned int loadCubemap(QVector<QString> faces);
protected:
    Camera mCamera;
    float  mLastX, mLastY;
    bool mMousePressed;
    QSet<int> mPressedKey;
};

#endif // COURSEWITHCAMERA_H
