#ifndef COURSE_4_9_2_GEOMETRY_SHADER_EXPLODING_H
#define COURSE_4_9_2_GEOMETRY_SHADER_EXPLODING_H

#include "course.h"
#include <QOpenGLExtraFunctions>
#include <QOpenGLShaderProgram>
#include <QMatrix4x4>
#include "core/camera.h"
#include "coursewithcamera.h"
#include "core/model.h"

class Course_4_9_2_geometry_shader_exploding : public CourseWithCamera
{
public:
    Course_4_9_2_geometry_shader_exploding();
    virtual ~Course_4_9_2_geometry_shader_exploding();

    void render() override;
    virtual QList<QtProperty*> getPropertyList(QtVariantPropertyManager *manager) override;
private:
    unsigned int VBO, VAO;
    QOpenGLShaderProgram mProgram;
    Model *mModel;
};

#endif // COURSE_4_9_2_GEOMETRY_SHADER_EXPLODING_H
