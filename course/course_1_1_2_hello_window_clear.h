#ifndef COURSE_1_1_1_HELLO_WINDOW_CLEAR_H
#define COURSE_1_1_1_HELLO_WINDOW_CLEAR_H

#include <QOpenGLExtraFunctions>
#include "course.h"

class Course_1_1_2_hello_window_clear : public Course, protected QOpenGLExtraFunctions
{
public:
    Course_1_1_2_hello_window_clear();

    void render() override;
    virtual QList<QtProperty*> getPropertyList(QtVariantPropertyManager *manager) override;
};

#endif // COURSE_1_1_1_HELLO_WINDOW_CLEAR_H
