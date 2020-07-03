#ifndef COURSE_5_5_2_STEEP_PARALLAX_MAPPING_H
#define COURSE_5_5_2_STEEP_PARALLAX_MAPPING_H

#include "course.h"
#include <QOpenGLExtraFunctions>
#include <QOpenGLShaderProgram>
#include <QMatrix4x4>
#include "core/camera.h"
#include "coursewithcamera.h"

class Course_5_5_2_steep_parallax_mapping : public CourseWithCamera
{
public:
    Course_5_5_2_steep_parallax_mapping();
    virtual ~Course_5_5_2_steep_parallax_mapping();

    void render() override;
    virtual QList<QtProperty*> getPropertyList(QtVariantPropertyManager *manager) override;
protected:
    void processInput() override;
private:
    void renderQuad();
private:
    unsigned int diffuseMap, normalMap, heightMap;
    QVector3D lightPos;
    unsigned int quadVAO;
    unsigned int quadVBO;
    float heightScale;
    QOpenGLShaderProgram shader;
};

#endif // COURSE_5_5_2_STEEP_PARALLAX_MAPPING_H
