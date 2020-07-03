#ifndef COURSE_1_6_1_COORDINATE_SYSTEMS_H
#define COURSE_1_6_1_COORDINATE_SYSTEMS_H

#include "course.h"
#include <QOpenGLExtraFunctions>
#include <QOpenGLShaderProgram>
#include <QMatrix4x4>

class Course_1_6_1_coordinate_systems : public Course, protected QOpenGLExtraFunctions
{
public:
    Course_1_6_1_coordinate_systems();
    virtual ~Course_1_6_1_coordinate_systems();

    void render() override;
    virtual QList<QtProperty*> getPropertyList(QtVariantPropertyManager *manager) override;
    virtual bool setProperty(const QString &propertyId, const QVariant &value) override;
private:
    unsigned int VBO, VAO, EBO;
    unsigned int texture1, texture2;
    QOpenGLShaderProgram *mProgram;

    QMatrix4x4 mModel, mView, mProjection;
};

#endif // COURSE_1_6_1_COORDINATE_SYSTEMS_H
