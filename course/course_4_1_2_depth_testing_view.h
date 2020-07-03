#ifndef COURSE_4_1_1_DEPTH_TESTING_VIEW_H
#define COURSE_4_1_1_DEPTH_TESTING_VIEW_H

#include "course.h"
#include <QOpenGLExtraFunctions>
#include <QOpenGLShaderProgram>
#include <QMatrix4x4>
#include "core/camera.h"
#include "coursewithcamera.h"

class Course_4_1_2_depth_testing_view : public CourseWithCamera
{
public:
    Course_4_1_2_depth_testing_view();
    virtual ~Course_4_1_2_depth_testing_view();

    void render() override;
    virtual QList<QtProperty*> getPropertyList(QtVariantPropertyManager *manager) override;
private:
    unsigned int cubeVAO, cubeVBO;
    unsigned int planeVAO, planeVBO;
    unsigned int cubeTexture, floorTexture;

    QOpenGLShaderProgram mProgram;
};

#endif // COURSE_4_1_1_DEPTH_TESTING_VIEW_H
