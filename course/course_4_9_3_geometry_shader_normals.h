#ifndef COURSE_4_9_3_GEOMETRY_SHADER_NORMALS_H
#define COURSE_4_9_3_GEOMETRY_SHADER_NORMALS_H

#include "course.h"
#include <QOpenGLExtraFunctions>
#include <QOpenGLShaderProgram>
#include <QMatrix4x4>
#include "core/camera.h"
#include "coursewithcamera.h"
#include "core/model.h"

class Course_4_9_3_geometry_shader_normals : public CourseWithCamera
{
public:
    Course_4_9_3_geometry_shader_normals();
    virtual ~Course_4_9_3_geometry_shader_normals();

    void render() override;
    virtual QList<QtProperty*> getPropertyList(QtVariantPropertyManager *manager) override;
private:
    QOpenGLShaderProgram mProgram, mNormalProgram;
    Model *mModel;
};

#endif // COURSE_4_9_3_GEOMETRY_SHADER_NORMALS_H
