#ifndef COURSE_1_4_1_TEXTURES_H
#define COURSE_1_4_1_TEXTURES_H

#include "course.h"
#include <QOpenGLExtraFunctions>
#include <QOpenGLShaderProgram>

class Course_1_4_1_textures : public Course, protected QOpenGLExtraFunctions
{
public:
    Course_1_4_1_textures();
    ~Course_1_4_1_textures();

    virtual void render() override;
    virtual QList<QtProperty*> getPropertyList(QtVariantPropertyManager *manager) override;
private:
    unsigned int VAO,VBO,EBO;
    unsigned int texture;

    QOpenGLShaderProgram *mProgram;
};

#endif // COURSE_1_4_1_TEXTURES_H
