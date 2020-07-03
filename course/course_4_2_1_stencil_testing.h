#ifndef COURSE_4_2_1_STENCIL_TESTING_H
#define COURSE_4_2_1_STENCIL_TESTING_H

#include "course.h"
#include <QOpenGLExtraFunctions>
#include <QOpenGLShaderProgram>
#include <QMatrix4x4>
#include "core/camera.h"
#include "coursewithcamera.h"

class Course_4_2_1_stencil_testing : public CourseWithCamera
{
public:
    Course_4_2_1_stencil_testing();
    virtual ~Course_4_2_1_stencil_testing();

    void render() override;
    virtual QList<QtProperty*> getPropertyList(QtVariantPropertyManager *manager) override;
private:
    unsigned int cubeVAO, cubeVBO;
    unsigned int planeVAO, planeVBO;
    unsigned int cubeTexture, floorTexture;

    QOpenGLShaderProgram mProgram, mSingleColorProgram;
};

#endif // COURSE_4_2_1_STENCIL_TESTING_H
