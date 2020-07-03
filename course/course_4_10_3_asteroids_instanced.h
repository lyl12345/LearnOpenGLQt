#ifndef COURSE_4_10_3_ASTEROIDS_INSTANCED_H
#define COURSE_4_10_3_ASTEROIDS_INSTANCED_H

#include "course.h"
#include <QOpenGLExtraFunctions>
#include <QOpenGLShaderProgram>
#include <QMatrix4x4>
#include "core/camera.h"
#include "coursewithcamera.h"
#include "core/model.h"

class Course_4_10_3_asteroids_instanced : public CourseWithCamera
{
public:
    Course_4_10_3_asteroids_instanced();
    virtual ~Course_4_10_3_asteroids_instanced();

    void render() override;
    virtual QList<QtProperty*> getPropertyList(QtVariantPropertyManager *manager) override;
private:
    unsigned int buffer;
    QOpenGLShaderProgram mAsteroidProgram, mPlanetProgram;

    Model *mRock, *mPlanet;
    QMatrix4x4 *modelMatrices;
    unsigned int amount;
};

#endif // COURSE_4_10_3_ASTEROIDS_INSTANCED_H
