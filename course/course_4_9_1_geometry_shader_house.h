#ifndef COURSE_4_9_1_GEOMETRY_SHADER_HOUSE_H
#define COURSE_4_9_1_GEOMETRY_SHADER_HOUSE_H

#include "course.h"
#include <QOpenGLExtraFunctions>
#include <QOpenGLShaderProgram>
#include <QMatrix4x4>
#include "core/camera.h"
#include "coursewithcamera.h"

class Course_4_9_1_geometry_shader_house : public CourseWithCamera
{
public:
    Course_4_9_1_geometry_shader_house();
    virtual ~Course_4_9_1_geometry_shader_house();

    void render() override;
    virtual QList<QtProperty*> getPropertyList(QtVariantPropertyManager *manager) override;
private:
    unsigned int VBO, VAO;
    QOpenGLShaderProgram mProgram;
};

#endif // COURSE_4_9_1_GEOMETRY_SHADER_HOUSE_H
