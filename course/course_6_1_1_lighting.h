#ifndef COURSE_6_1_1_LIGHTING_H
#define COURSE_6_1_1_LIGHTING_H

#include "course.h"
#include <QOpenGLExtraFunctions>
#include <QOpenGLShaderProgram>
#include <QMatrix4x4>
#include "core/camera.h"
#include "coursewithcamera.h"

class Course_6_1_1_lighting : public CourseWithCamera
{
public:
    Course_6_1_1_lighting();
    virtual ~Course_6_1_1_lighting();

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
    unsigned int sphereVAO;
    unsigned int vbo, ebo;
    unsigned int indexCount;
    QOpenGLShaderProgram shader;
};

#endif // COURSE_6_1_1_LIGHTING_H
