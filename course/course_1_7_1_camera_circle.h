#ifndef COURSE_1_7_1_CAMERA_CIRCLE_H
#define COURSE_1_7_1_CAMERA_CIRCLE_H

#include "course.h"
#include <QOpenGLExtraFunctions>
#include <QOpenGLShaderProgram>
#include <QMatrix4x4>

class Course_1_7_1_camera_circle : public Course, protected QOpenGLExtraFunctions
{
public:
    Course_1_7_1_camera_circle();
    virtual ~Course_1_7_1_camera_circle();

    void render() override;
    virtual QList<QtProperty*> getPropertyList(QtVariantPropertyManager *manager) override;
private:
    unsigned int VBO, VAO;
    unsigned int texture1, texture2;
    QMatrix4x4 mModel, mView, mProjection;
    QOpenGLShaderProgram *mProgram;
};

#endif // COURSE_1_7_1_CAMERA_CIRCLE_H
