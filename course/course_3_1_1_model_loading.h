#ifndef COURSE_3_1_1_MODEL_LOADING_H
#define COURSE_3_1_1_MODEL_LOADING_H

#include "course.h"
#include <QOpenGLExtraFunctions>
#include <QOpenGLShaderProgram>
#include <QMatrix4x4>
#include "core/camera.h"
#include "coursewithcamera.h"
#include "core/model.h"

class Course_3_1_1_model_loading : public CourseWithCamera
{
public:
    Course_3_1_1_model_loading();
    virtual ~Course_3_1_1_model_loading();

    void render() override;
    virtual QList<QtProperty*> getPropertyList(QtVariantPropertyManager *manager) override;
private:
    Model *mModel;
    QOpenGLShaderProgram mProgram;
};

#endif // COURSE_3_1_1_MODEL_LOADING_H
