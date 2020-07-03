#ifndef COURSE_2_5_2_LIGHT_CASTERS_POINT_H
#define COURSE_2_5_2_LIGHT_CASTERS_POINT_H

#include "course.h"
#include <QOpenGLExtraFunctions>
#include <QOpenGLShaderProgram>
#include <QMatrix4x4>
#include "core/camera.h"
#include "coursewithcamera.h"

class Course_2_5_2_light_casters_point  : public CourseWithCamera
{
public:
    Course_2_5_2_light_casters_point();
    virtual ~Course_2_5_2_light_casters_point();

    void render() override;
    virtual QList<QtProperty*> getPropertyList(QtVariantPropertyManager *manager) override;

private:
    unsigned int VBO, cubeVAO;
    unsigned int lightCubeVAO;
    unsigned int diffuseMap, specularMap;
    QVector3D lightPos;

    QOpenGLShaderProgram mLightingProgram, mLightCubeProgram;
};

#endif // COURSE_2_5_2_LIGHT_CASTERS_POINT_H
