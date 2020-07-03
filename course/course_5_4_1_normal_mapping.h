#ifndef COURSE_5_4_1_NORMAL_MAPPING_H
#define COURSE_5_4_1_NORMAL_MAPPING_H

#include "course.h"
#include <QOpenGLExtraFunctions>
#include <QOpenGLShaderProgram>
#include <QMatrix4x4>
#include "core/camera.h"
#include "coursewithcamera.h"

class Course_5_4_1_normal_mapping : public CourseWithCamera
{
public:
    Course_5_4_1_normal_mapping();
    virtual ~Course_5_4_1_normal_mapping();

    void render() override;
    virtual QList<QtProperty*> getPropertyList(QtVariantPropertyManager *manager) override;
private:
    void renderQuad();
private:
    unsigned int diffuseMap, normalMap;
    QVector3D lightPos;
    unsigned int quadVAO;
    unsigned int quadVBO;
    QOpenGLShaderProgram shader;
};

#endif // COURSE_5_4_1_NORMAL_MAPPING_H
