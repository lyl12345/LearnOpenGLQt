#ifndef COURSE_1_2_2_HELLO_TRIANGLE_INDEXED_H
#define COURSE_1_2_2_HELLO_TRIANGLE_INDEXED_H

#include "course.h"
#include <QOpenGLExtraFunctions>
#include <QOpenGLShaderProgram>

class Course_1_2_2_hello_triangle_indexed : public Course, protected QOpenGLExtraFunctions
{
public:
    Course_1_2_2_hello_triangle_indexed();
    virtual ~Course_1_2_2_hello_triangle_indexed();

    void render() override;
    virtual QList<QtProperty*> getPropertyList(QtVariantPropertyManager *manager) override;
private:
    unsigned int VBO, VAO, EBO;
    QOpenGLShaderProgram *mProgram;
};

#endif // COURSE_1_2_2_HELLO_TRIANGLE_INDEXED_H
