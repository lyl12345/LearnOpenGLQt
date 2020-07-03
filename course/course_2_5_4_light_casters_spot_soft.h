#ifndef COURSE_2_5_4_LIGHT_CASTERS_SPOT_SOFT_H
#define COURSE_2_5_4_LIGHT_CASTERS_SPOT_SOFT_H

#include "course.h"
#include <QOpenGLExtraFunctions>
#include <QOpenGLShaderProgram>
#include <QMatrix4x4>
#include "core/camera.h"
#include "coursewithcamera.h"

class Course_2_5_4_light_casters_spot_soft : public CourseWithCamera
{
public:
    Course_2_5_4_light_casters_spot_soft();
    virtual ~Course_2_5_4_light_casters_spot_soft();

    void render() override;
    virtual QList<QtProperty*> getPropertyList(QtVariantPropertyManager *manager) override;
private:
    unsigned int VBO, cubeVAO;
    unsigned int lightCubeVAO;
    unsigned int diffuseMap, specularMap;
    QVector3D lightPos;

    QOpenGLShaderProgram mLightingProgram, mLightCubeProgram;
};

#endif // COURSE_2_5_4_LIGHT_CASTERS_SPOT_SOFT_H
