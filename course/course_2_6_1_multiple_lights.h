#ifndef COURSE_2_6_1_MULTIPLE_LIGHTS_H
#define COURSE_2_6_1_MULTIPLE_LIGHTS_H

#include "course.h"
#include <QOpenGLExtraFunctions>
#include <QOpenGLShaderProgram>
#include <QMatrix4x4>
#include "core/camera.h"
#include "coursewithcamera.h"

class Course_2_6_1_multiple_lights : public CourseWithCamera
{
public:
    Course_2_6_1_multiple_lights();
    virtual ~Course_2_6_1_multiple_lights();

    void render() override;
    virtual QList<QtProperty*> getPropertyList(QtVariantPropertyManager *manager) override;
private:
    unsigned int VBO, cubeVAO;
    unsigned int lightCubeVAO;
    unsigned int diffuseMap, specularMap;
    QVector3D lightPos;

    QOpenGLShaderProgram mLightingProgram, mLightCubeProgram;
};

#endif // COURSE_2_6_1_MULTIPLE_LIGHTS_H
