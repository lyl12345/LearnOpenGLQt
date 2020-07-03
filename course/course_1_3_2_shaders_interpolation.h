#ifndef COURSE_1_3_2_SHADERS_INTERPOLATION_H
#define COURSE_1_3_2_SHADERS_INTERPOLATION_H

#include "course.h"
#include <QOpenGLExtraFunctions>
#include <QOpenGLShaderProgram>

class Course_1_3_2_shaders_interpolation : public Course, protected QOpenGLExtraFunctions
{
public:
    Course_1_3_2_shaders_interpolation();
    virtual ~Course_1_3_2_shaders_interpolation();

    void render() override;
    virtual QList<QtProperty*> getPropertyList(QtVariantPropertyManager *manager) override;
private:
    unsigned int VBO, VAO;
    QOpenGLShaderProgram *mProgram;
};

#endif // COURSE_1_3_2_SHADERS_INTERPOLATION_H
