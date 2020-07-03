#ifndef COURSE_1_6_3_COORDINATE_SYSTEMS_MULTIPLE_H
#define COURSE_1_6_3_COORDINATE_SYSTEMS_MULTIPLE_H

#include "course.h"
#include <QOpenGLExtraFunctions>
#include <QOpenGLShaderProgram>
#include <QMatrix4x4>

class Course_1_6_3_coordinate_systems_multiple : public Course, protected QOpenGLExtraFunctions
{
public:
    Course_1_6_3_coordinate_systems_multiple();
    virtual ~Course_1_6_3_coordinate_systems_multiple();

    void render() override;
    virtual QList<QtProperty*> getPropertyList(QtVariantPropertyManager *manager) override;
private:
    unsigned int VBO, VAO;
    unsigned int texture1, texture2;
    QMatrix4x4 mModel, mView, mProjection;
    QOpenGLShaderProgram *mProgram;
};

#endif // COURSE_1_6_3_COORDINATE_SYSTEMS_MULTIPLE_H
