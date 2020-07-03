#ifndef COURSE_1_7_2_CAMERA_KEYBOARD_DT_H
#define COURSE_1_7_2_CAMERA_KEYBOARD_DT_H

#include "course.h"
#include <QOpenGLExtraFunctions>
#include <QOpenGLShaderProgram>
#include <QMatrix4x4>

class Course_1_7_2_camera_keyboard_dt : public Course, protected QOpenGLExtraFunctions
{
public:
    Course_1_7_2_camera_keyboard_dt();
    ~Course_1_7_2_camera_keyboard_dt();

    void render() override;
    virtual QList<QtProperty*> getPropertyList(QtVariantPropertyManager *manager) override;

protected:
    void leave(QEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
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
};

#endif // COURSE_1_7_2_CAMERA_KEYBOARD_DT_H
