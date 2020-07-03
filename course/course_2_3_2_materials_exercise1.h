#ifndef COURSE_2_3_2_MATERIALS_EXERCISE1_H
#define COURSE_2_3_2_MATERIALS_EXERCISE1_H

#include "course.h"
#include <QOpenGLExtraFunctions>
#include <QOpenGLShaderProgram>
#include <QMatrix4x4>
#include "core/camera.h"
#include "coursewithcamera.h"

class Course_2_3_2_materials_exercise1 : public CourseWithCamera
{
public:
    Course_2_3_2_materials_exercise1();
    virtual ~Course_2_3_2_materials_exercise1();

    void render() override;
    virtual QList<QtProperty*> getPropertyList(QtVariantPropertyManager *manager) override;
private:
    unsigned int VBO, cubeVAO;
    unsigned int lightCubeVAO;
    QVector3D lightPos;

    QOpenGLShaderProgram mLightingProgram, mLightCubeProgram;
};

#endif // COURSE_2_3_2_MATERIALS_EXERCISE1_H
