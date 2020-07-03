#ifndef COURSE_1_4_3_TEXTURES_EXERCISE2_H
#define COURSE_1_4_3_TEXTURES_EXERCISE2_H

#include "course.h"
#include <QOpenGLExtraFunctions>
#include <QOpenGLShaderProgram>

class Course_1_4_3_textures_exercise2 : public Course, protected QOpenGLExtraFunctions
{
public:
    Course_1_4_3_textures_exercise2();
    virtual ~Course_1_4_3_textures_exercise2();

    void render() override;
    virtual QList<QtProperty*> getPropertyList(QtVariantPropertyManager *manager) override;
private:
    unsigned int VBO, VAO, EBO;
    unsigned int texture1, texture2;
    QOpenGLShaderProgram *mProgram;
};

#endif // COURSE_1_4_3_TEXTURES_EXERCISE2_H
