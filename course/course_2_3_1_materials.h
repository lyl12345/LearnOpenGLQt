#ifndef COURSE_2_3_1_MATERIALS_H
#define COURSE_2_3_1_MATERIALS_H

#include "course.h"
#include <QOpenGLExtraFunctions>
#include <QOpenGLShaderProgram>
#include <QMatrix4x4>
#include "core/camera.h"
#include "coursewithcamera.h"

class Course_2_3_1_materials : public CourseWithCamera
{
public:
    Course_2_3_1_materials();
    virtual ~Course_2_3_1_materials();

    void render() override;
    virtual QList<QtProperty*> getPropertyList(QtVariantPropertyManager *manager) override;
private:
    unsigned int VBO, cubeVAO;
    unsigned int lightCubeVAO;
    QVector3D lightPos;

    QOpenGLShaderProgram mLightingProgram, mLightCubeProgram;
};

#endif // COURSE_2_3_1_MATERIALS_H
