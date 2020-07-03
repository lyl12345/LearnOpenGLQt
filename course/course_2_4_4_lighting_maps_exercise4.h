#ifndef COURSE_2_4_4_LIGHTING_MAPS_EXERCISES_H
#define COURSE_2_4_4_LIGHTING_MAPS_EXERCISES_H

#include "course.h"
#include <QOpenGLExtraFunctions>
#include <QOpenGLShaderProgram>
#include <QMatrix4x4>
#include "core/camera.h"
#include "coursewithcamera.h"

class Course_2_4_4_lighting_maps_exercises4 : public CourseWithCamera
{
public:
    Course_2_4_4_lighting_maps_exercises4();
    virtual ~Course_2_4_4_lighting_maps_exercises4();

    void render() override;
    virtual QList<QtProperty*> getPropertyList(QtVariantPropertyManager *manager) override;

private:
    unsigned int VBO, cubeVAO;
    unsigned int lightCubeVAO;
    unsigned int diffuseMap, specularMap, emissionMap;
    QVector3D lightPos;

    QOpenGLShaderProgram mLightingProgram, mLightCubeProgram;
};

#endif // COURSE_2_4_4_LIGHTING_MAPS_EXERCISES_H
