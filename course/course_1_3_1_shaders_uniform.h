#ifndef COURSE_1_3_1_SHADERS_UNIFORM_H
#define COURSE_1_3_1_SHADERS_UNIFORM_H

#include "course.h"
#include <QOpenGLExtraFunctions>
#include <QOpenGLShaderProgram>

class Course_1_3_1_shaders_uniform : public Course, protected QOpenGLExtraFunctions
{
public:
    Course_1_3_1_shaders_uniform();
    virtual ~Course_1_3_1_shaders_uniform();

    void render() override;
    virtual QList<QtProperty*> getPropertyList(QtVariantPropertyManager *manager) override;
private  slots:
    void changeGreenValue();
private:
    unsigned int VBO, VAO;
    QOpenGLShaderProgram *mProgram;
};

#endif // COURSE_1_3_1_SHADERS_UNIFORM_H
