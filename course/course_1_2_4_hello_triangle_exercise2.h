#ifndef COURSE_1_2_4_HELLO_TRIANGLE_EXERCISE2_H
#define COURSE_1_2_4_HELLO_TRIANGLE_EXERCISE2_H

#include "course.h"
#include <QOpenGLExtraFunctions>
#include <QOpenGLShaderProgram>

class Course_1_2_4_hello_triangle_exercise2 : public Course, protected QOpenGLExtraFunctions
{
public:
    Course_1_2_4_hello_triangle_exercise2();
    virtual ~Course_1_2_4_hello_triangle_exercise2();

    void render() override;
    virtual QList<QtProperty*> getPropertyList(QtVariantPropertyManager *manager) override;
private:
    unsigned int VBOs[2], VAOs[2];
    QOpenGLShaderProgram *mProgram;
};

#endif // COURSE_1_2_4_HELLO_TRIANGLE_EXERCISE2_H
