#ifndef COURSE_1_5_1_TRANSFORMATIONS_H
#define COURSE_1_5_1_TRANSFORMATIONS_H

#include "course.h"
#include <QOpenGLExtraFunctions>
#include <QOpenGLShaderProgram>
#include <QMatrix4x4>

class Course_1_5_1_transformations : public Course, protected QOpenGLExtraFunctions
{
    Q_OBJECT
public:
    Course_1_5_1_transformations();
    virtual ~Course_1_5_1_transformations();

    void render() override;

    virtual QList<QtProperty*> getPropertyList(QtVariantPropertyManager *manager) override;
private:
    unsigned int VBO, VAO, EBO;
    unsigned int texture1, texture2;
    QOpenGLShaderProgram *mProgram;

    QMatrix4x4 mTransform;
};

#endif // COURSE_1_5_1_TRANSFORMATIONS_H
