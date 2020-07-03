#ifndef COURSE_1_1_1_TEXTURES_H
#define COURSE_1_1_1_TEXTURES_H

#include <QOpenGLExtraFunctions>
#include "course.h"

class Course_1_1_1_hello_window : public Course, protected QOpenGLExtraFunctions
{
public:
    Course_1_1_1_hello_window();

    void render() override;
    virtual QList<QtProperty*> getPropertyList(QtVariantPropertyManager *manager) override;
};

#endif // COURSE_1_1_1_TEXTURES_H
