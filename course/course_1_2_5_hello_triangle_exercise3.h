#ifndef COURSE_1_2_5_HELLO_TRIANGLE_EXERCISE3_H
#define COURSE_1_2_5_HELLO_TRIANGLE_EXERCISE3_H

#include "course.h"
#include <QOpenGLExtraFunctions>
#include <QOpenGLShaderProgram>

class Course_1_2_5_hello_triangle_exercise3 : public Course, protected QOpenGLExtraFunctions
{
public:
    Course_1_2_5_hello_triangle_exercise3();
    virtual ~Course_1_2_5_hello_triangle_exercise3();

    void render() override;
    virtual QList<QtProperty*> getPropertyList(QtVariantPropertyManager *manager) override;
private:
    unsigned int VBOs[2], VAOs[2];
    QOpenGLShaderProgram *mProgramOrange;
    QOpenGLShaderProgram *mProgramYellow;
};

#endif // COURSE_1_2_5_HELLO_TRIANGLE_EXERCISE3_H
