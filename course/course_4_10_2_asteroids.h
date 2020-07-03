#ifndef COURSE_4_10_2_ASTEROIDS_H
#define COURSE_4_10_2_ASTEROIDS_H

#include "course.h"
#include <QOpenGLExtraFunctions>
#include <QOpenGLShaderProgram>
#include <QMatrix4x4>
#include "core/camera.h"
#include "coursewithcamera.h"
#include "core/model.h"

class Course_4_10_2_asteroids : public CourseWithCamera
{
public:
    Course_4_10_2_asteroids();
    virtual ~Course_4_10_2_asteroids();

    void render() override;
    virtual QList<QtProperty*> getPropertyList(QtVariantPropertyManager *manager) override;
private:
    QOpenGLShaderProgram mProgram;

    Model *mRock, *mPlanet;
    QMatrix4x4 *modelMatrices;
    unsigned int amount;
};

#endif // COURSE_4_10_2_ASTEROIDS_H
