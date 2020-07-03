#ifndef COURSE_1_6_2_COORDINATE_SYSTEMS_DEPTH_H
#define COURSE_1_6_2_COORDINATE_SYSTEMS_DEPTH_H

#include "course.h"
#include <QOpenGLExtraFunctions>
#include <QOpenGLShaderProgram>
#include <QMatrix4x4>

class Course_1_6_2_coordinate_systems_depth : public Course, protected QOpenGLExtraFunctions
{
public:
    Course_1_6_2_coordinate_systems_depth();
    virtual ~Course_1_6_2_coordinate_systems_depth();

    void render() override;
    virtual QList<QtProperty*> getPropertyList(QtVariantPropertyManager *manager) override;
private:
    unsigned int VBO, VAO;
    unsigned int texture1, texture2;
    QOpenGLShaderProgram *mProgram;
    QMatrix4x4 mModel, mView, mProjection;
};

#endif // COURSE_1_6_2_COORDINATE_SYSTEMS_DEPTH_H
