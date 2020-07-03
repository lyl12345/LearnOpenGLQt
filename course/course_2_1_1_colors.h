#ifndef COURSE_2_1_1_COLORS_H
#define COURSE_2_1_1_COLORS_H

#include "course.h"
#include <QOpenGLExtraFunctions>
#include <QOpenGLShaderProgram>
#include <QMatrix4x4>
#include "core/camera.h"
#include "coursewithcamera.h"

class Course_2_1_1_colors : public CourseWithCamera
{
public:
    Course_2_1_1_colors();
    virtual ~Course_2_1_1_colors();

    void render() override;
    virtual QList<QtProperty*> getPropertyList(QtVariantPropertyManager *manager) override;
private:
    unsigned int VBO, cubeVAO;
    unsigned int lightCubeVAO;
    QVector3D lightPos;

    QOpenGLShaderProgram mLightingProgram, mLightCubeProgram;
};

#endif // COURSE_2_1_1_COLORS_H
