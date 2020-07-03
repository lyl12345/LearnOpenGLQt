#ifndef COURSE_4_1_1_DEPTH_TESTING_H
#define COURSE_4_1_1_DEPTH_TESTING_H

#include "course.h"
#include <QOpenGLExtraFunctions>
#include <QOpenGLShaderProgram>
#include <QMatrix4x4>
#include "core/camera.h"
#include "coursewithcamera.h"

class Course_4_1_1_depth_testing : public CourseWithCamera
{
public:
    Course_4_1_1_depth_testing();
    virtual ~Course_4_1_1_depth_testing();

    void render() override;
    virtual QList<QtProperty*> getPropertyList(QtVariantPropertyManager *manager) override;
private:
    unsigned int cubeVAO, cubeVBO;
    unsigned int planeVAO, planeVBO;
    unsigned int cubeTexture, floorTexture;

    QOpenGLShaderProgram mProgram;
};

#endif // COURSE_4_1_1_DEPTH_TESTING_H
