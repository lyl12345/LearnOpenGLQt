#ifndef COURSE_5_1_1_ADVANCED_LIGHTING_H
#define COURSE_5_1_1_ADVANCED_LIGHTING_H

#include "course.h"
#include <QOpenGLExtraFunctions>
#include <QOpenGLShaderProgram>
#include <QMatrix4x4>
#include "core/camera.h"
#include "coursewithcamera.h"

class Course_5_1_1_advanced_lighting : public CourseWithCamera
{
public:
    Course_5_1_1_advanced_lighting();
    virtual ~Course_5_1_1_advanced_lighting();

    void render() override;
    virtual QList<QtProperty*> getPropertyList(QtVariantPropertyManager *manager) override;
protected:
    void processInput() override;
private:
    unsigned int planeVAO, planeVBO;
    unsigned int floorTexture;
    QVector3D lightPos;
    bool blinn, blinnKeyPressed;
    QOpenGLShaderProgram mProgram;
};

#endif // COURSE_5_1_1_ADVANCED_LIGHTING_H
