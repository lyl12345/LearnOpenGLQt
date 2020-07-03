#ifndef COURSE_2_2_2_BASIC_LIGHTING_SPECULAR_H
#define COURSE_2_2_2_BASIC_LIGHTING_SPECULAR_H

#include "course.h"
#include <QOpenGLExtraFunctions>
#include <QOpenGLShaderProgram>
#include <QMatrix4x4>
#include "core/camera.h"
#include "coursewithcamera.h"

class Course_2_2_2_basic_lighting_specular : public CourseWithCamera
{
public:
    Course_2_2_2_basic_lighting_specular();
    virtual ~Course_2_2_2_basic_lighting_specular();

    void render() override;
    virtual QList<QtProperty*> getPropertyList(QtVariantPropertyManager *manager) override;
private:
    unsigned int VBO, cubeVAO;
    unsigned int lightCubeVAO;
    QVector3D lightPos;

    QOpenGLShaderProgram mLightingProgram, mLightCubeProgram;
};

#endif // COURSE_2_2_2_BASIC_LIGHTING_SPECULAR_H
