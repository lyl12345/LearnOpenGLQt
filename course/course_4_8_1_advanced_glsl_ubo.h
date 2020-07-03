#ifndef COURSE_4_8_1_ADVANCED_GLSL_UBO_H
#define COURSE_4_8_1_ADVANCED_GLSL_UBO_H

#include "course.h"
#include <QOpenGLExtraFunctions>
#include <QOpenGLShaderProgram>
#include <QMatrix4x4>
#include "core/camera.h"
#include "coursewithcamera.h"

class Course_4_8_1_advanced_glsl_ubo : public CourseWithCamera
{
public:
    Course_4_8_1_advanced_glsl_ubo();
    virtual ~Course_4_8_1_advanced_glsl_ubo();

    void render() override;
    virtual QList<QtProperty*> getPropertyList(QtVariantPropertyManager *manager) override;
private:
    unsigned int cubeVAO, cubeVBO;
    unsigned int uboMatrices;
    QOpenGLShaderProgram mRedProgram, mGreenProgram, mBlueProgram, mYellowProgram;
};

#endif // COURSE_4_8_1_ADVANCED_GLSL_UBO_H
