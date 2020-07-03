#ifndef COURSE_4_10_1_INSTANCING_QUADS_H
#define COURSE_4_10_1_INSTANCING_QUADS_H

#include "course.h"
#include <QOpenGLExtraFunctions>
#include <QOpenGLShaderProgram>
#include <QMatrix4x4>
#include "core/camera.h"
#include "coursewithcamera.h"

class Course_4_10_1_instancing_quads : public CourseWithCamera
{
public:
    Course_4_10_1_instancing_quads();
    virtual ~Course_4_10_1_instancing_quads();

    void render() override;
    virtual QList<QtProperty*> getPropertyList(QtVariantPropertyManager *manager) override;
private:
    unsigned int instanceVBO;
    unsigned int quadVAO, quadVBO;

    QOpenGLShaderProgram mProgram;
};

#endif // COURSE_4_10_1_INSTANCING_QUADS_H
