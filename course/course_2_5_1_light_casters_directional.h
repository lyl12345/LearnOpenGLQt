#ifndef COURSE_2_5_1_LIGHT_CASTERS_DIRECTIONAL_H
#define COURSE_2_5_1_LIGHT_CASTERS_DIRECTIONAL_H

#include "course.h"
#include <QOpenGLExtraFunctions>
#include <QOpenGLShaderProgram>
#include <QMatrix4x4>
#include "core/camera.h"
#include "coursewithcamera.h"

class Course_2_5_1_light_casters_directional : public CourseWithCamera
{
public:
    Course_2_5_1_light_casters_directional();
    virtual ~Course_2_5_1_light_casters_directional();

    void render() override;
    virtual QList<QtProperty*> getPropertyList(QtVariantPropertyManager *manager) override;

private:
    unsigned int VBO, cubeVAO;
    unsigned int lightCubeVAO;
    unsigned int diffuseMap, specularMap;
    QVector3D lightPos;

    QOpenGLShaderProgram mLightingProgram, mLightCubeProgram;
};

#endif // COURSE_2_5_1_LIGHT_CASTERS_DIRECTIONAL_H
