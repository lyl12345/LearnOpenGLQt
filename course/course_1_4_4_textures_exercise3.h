#ifndef COURSE_1_4_4_TEXTURES_EXERCISE3_H
#define COURSE_1_4_4_TEXTURES_EXERCISE3_H

#include "course.h"
#include <QOpenGLExtraFunctions>
#include <QOpenGLShaderProgram>

class Course_1_4_4_textures_exercise3 : public Course, protected QOpenGLExtraFunctions
{
public:
    Course_1_4_4_textures_exercise3();
    virtual ~Course_1_4_4_textures_exercise3();

    void render() override;
    virtual QList<QtProperty*> getPropertyList(QtVariantPropertyManager *manager) override;
private:
    unsigned int VBO, VAO, EBO;
    unsigned int texture1, texture2;
    QOpenGLShaderProgram *mProgram;
};

#endif // COURSE_1_4_4_TEXTURES_EXERCISE3_H
