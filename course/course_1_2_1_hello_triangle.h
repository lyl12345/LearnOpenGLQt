#ifndef COURSE_1_2_1_HELLO_TRIANGLE_H
#define COURSE_1_2_1_HELLO_TRIANGLE_H

#include "course.h"
#include <QOpenGLExtraFunctions>
#include <QOpenGLShaderProgram>

class Course_1_2_1_hello_triangle : public Course, protected QOpenGLExtraFunctions
{
public:
    Course_1_2_1_hello_triangle();
    virtual ~Course_1_2_1_hello_triangle();

    void render() override;
    virtual QList<QtProperty*> getPropertyList(QtVariantPropertyManager *manager) override;
private:
    unsigned int VBO, VAO;
    QOpenGLShaderProgram *mProgram;
};

#endif // COURSE_1_2_1_HELLO_TRIANGLE_H
