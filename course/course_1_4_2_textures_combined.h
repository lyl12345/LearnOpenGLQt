#ifndef COURSE_1_4_2_TEXTURES_COMBINED_H
#define COURSE_1_4_2_TEXTURES_COMBINED_H

#include "course.h"
#include <QOpenGLExtraFunctions>
#include <QOpenGLShaderProgram>

class Course_1_4_2_textures_combined : public Course, protected QOpenGLExtraFunctions
{
public:
    Course_1_4_2_textures_combined();
    virtual ~Course_1_4_2_textures_combined();

    void render() override;
    virtual QList<QtProperty*> getPropertyList(QtVariantPropertyManager *manager) override;
private:
    unsigned int VBO, VAO, EBO;
    unsigned int texture1, texture2;
    QOpenGLShaderProgram *mProgram;
};

#endif // COURSE_1_4_2_TEXTURES_COMBINED_H
