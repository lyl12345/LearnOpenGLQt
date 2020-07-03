#ifndef COURSE_1_4_5_TEXTURES_EXERCISE4_H
#define COURSE_1_4_5_TEXTURES_EXERCISE4_H

#include "course.h"
#include <QOpenGLExtraFunctions>
#include <QOpenGLShaderProgram>

class Course_1_4_5_textures_exercise4 : public Course, protected QOpenGLExtraFunctions
{
public:
    Course_1_4_5_textures_exercise4();
    virtual ~Course_1_4_5_textures_exercise4();

    void render() override;

    virtual QList<QtProperty*> getPropertyList(QtVariantPropertyManager *manager) override;
    virtual bool setProperty(const QString &propertyId, const QVariant &value) override;
private:
    unsigned int VBO, VAO, EBO;
    unsigned int texture1, texture2;
    float mMixValue;
    QOpenGLShaderProgram *mProgram;
};

#endif // COURSE_1_4_5_TEXTURES_EXERCISE4_H
