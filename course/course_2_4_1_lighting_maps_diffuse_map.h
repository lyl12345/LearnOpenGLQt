#ifndef COURSE_2_4_1_LIGHTING_MAPS_DIFFUSE_MAP_H
#define COURSE_2_4_1_LIGHTING_MAPS_DIFFUSE_MAP_H

#include "course.h"
#include <QOpenGLExtraFunctions>
#include <QOpenGLShaderProgram>
#include <QMatrix4x4>
#include "core/camera.h"
#include "coursewithcamera.h"

class Course_2_4_1_lighting_maps_diffuse_map : public CourseWithCamera
{
public:
    Course_2_4_1_lighting_maps_diffuse_map();
    virtual ~Course_2_4_1_lighting_maps_diffuse_map();

    void render() override;
    virtual QList<QtProperty*> getPropertyList(QtVariantPropertyManager *manager) override;

private:
    unsigned int VBO, cubeVAO;
    unsigned int lightCubeVAO;
    unsigned int diffuseMap;
    QVector3D lightPos;

    QOpenGLShaderProgram mLightingProgram, mLightCubeProgram;
};

#endif // COURSE_2_4_1_LIGHTING_MAPS_DIFFUSE_MAP_H
