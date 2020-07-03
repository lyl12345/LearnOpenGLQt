#ifndef COURSE_1_5_2_TRANSFORMATIONS_EXERCISE2_H
#define COURSE_1_5_2_TRANSFORMATIONS_EXERCISE2_H

#include "course.h"
#include <QOpenGLExtraFunctions>
#include <QOpenGLShaderProgram>

class Course_1_5_2_transformations_exercise2 : public Course, protected QOpenGLExtraFunctions
{
    Q_OBJECT
public:
    Course_1_5_2_transformations_exercise2();
    ~Course_1_5_2_transformations_exercise2();

    void render() override;
    virtual QList<QtProperty*> getPropertyList(QtVariantPropertyManager *manager) override;
    virtual bool setProperty(const QString &propertyId, const QVariant &value) override;
private:
    unsigned int VBO, VAO, EBO;
    unsigned int texture1, texture2;
    QOpenGLShaderProgram *mProgram;
    QMatrix4x4 mMatrix1, mMatrix2;

    float mAngle, mScale;
    QVector3D mTranslate1, mTranslate2, mRotateAsix;
};

#endif // COURSE_1_5_2_TRANSFORMATIONS_EXERCISE2_H
