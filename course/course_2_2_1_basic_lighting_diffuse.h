#ifndef COURSE_2_2_1_BASIC_LIGHTING_DIFFUSE_H
#define COURSE_2_2_1_BASIC_LIGHTING_DIFFUSE_H

#include "course.h"
#include <QOpenGLExtraFunctions>
#include <QOpenGLShaderProgram>
#include <QMatrix4x4>
#include "core/camera.h"
#include "coursewithcamera.h"

class Course_2_2_1_basic_lighting_diffuse : public CourseWithCamera
{
public:
    Course_2_2_1_basic_lighting_diffuse();
    virtual ~Course_2_2_1_basic_lighting_diffuse();

    void render() override;
    virtual QList<QtProperty*> getPropertyList(QtVariantPropertyManager *manager) override;
private:
    unsigned int VBO, cubeVAO;
    unsigned int lightCubeVAO;
    QVector3D lightPos;

    QOpenGLShaderProgram mLightingProgram, mLightCubeProgram;
};

#endif // COURSE_2_2_1_BASIC_LIGHTING_DIFFUSE_H
