#ifndef COURSE_4_11_1_ANTI_ALIASING_MSAA_H
#define COURSE_4_11_1_ANTI_ALIASING_MSAA_H

#include "course.h"
#include <QOpenGLExtraFunctions>
#include <QOpenGLShaderProgram>
#include <QMatrix4x4>
#include "core/camera.h"
#include "coursewithcamera.h"

class Course_4_11_1_anti_aliasing_msaa : public CourseWithCamera
{
public:
    Course_4_11_1_anti_aliasing_msaa();
    virtual ~Course_4_11_1_anti_aliasing_msaa();

    void render() override;
    virtual QList<QtProperty*> getPropertyList(QtVariantPropertyManager *manager) override;
private:
    unsigned int cubeVAO, cubeVBO;
    QOpenGLShaderProgram mProgram;
};

#endif // COURSE_4_11_1_ANTI_ALIASING_MSAA_H
