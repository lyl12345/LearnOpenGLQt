#ifndef COURSE_1_2_3_HELLO_TRIANGLE_EXERCISE1_H
#define COURSE_1_2_3_HELLO_TRIANGLE_EXERCISE1_H

#include "course.h"
#include <QOpenGLExtraFunctions>
#include <QOpenGLShaderProgram>

class Course_1_2_3_hello_triangle_exercise1 : public Course, protected QOpenGLExtraFunctions
{
public:
    Course_1_2_3_hello_triangle_exercise1();
    virtual ~Course_1_2_3_hello_triangle_exercise1();

    void render() override;
    virtual QList<QtProperty*> getPropertyList(QtVariantPropertyManager *manager) override;
private:
    unsigned int VBO, VAO;
    QOpenGLShaderProgram *mProgram;
};

#endif // COURSE_1_2_3_HELLO_TRIANGLE_EXERCISE1_H
