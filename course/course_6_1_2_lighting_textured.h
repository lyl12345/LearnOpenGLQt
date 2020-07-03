#ifndef COURSE_6_1_2_LIGHTING_TEXTURED_H
#define COURSE_6_1_2_LIGHTING_TEXTURED_H

#include "course.h"
#include <QOpenGLExtraFunctions>
#include <QOpenGLShaderProgram>
#include <QMatrix4x4>
#include "core/camera.h"
#include "coursewithcamera.h"

class Course_6_1_2_lighting_textured : public CourseWithCamera
{
public:
    Course_6_1_2_lighting_textured();
    virtual ~Course_6_1_2_lighting_textured();

    void init(GlWindow *glWindow = nullptr) override;
    void render() override;
    virtual QList<QtProperty*> getPropertyList(QtVariantPropertyManager *manager) override;
private:
    void renderSphere();
private:
    QVector<QVector3D> lightPositions;
    QVector<QVector3D> lightColors;
    int nrRows, nrColumns;
    float spacing;
    unsigned int albedo, normal, metallic, roughness, ao;
    unsigned int sphereVAO;
    unsigned int vbo, ebo;
    unsigned int indexCount;
    QOpenGLShaderProgram shader;
};

#endif // COURSE_6_1_2_LIGHTING_TEXTURED_H
