#ifndef COURSE_4_3_1_BLENDING_DISCARD_H
#define COURSE_4_3_1_BLENDING_DISCARD_H

#include "course.h"
#include <QOpenGLExtraFunctions>
#include <QOpenGLShaderProgram>
#include <QMatrix4x4>
#include "core/camera.h"
#include "coursewithcamera.h"

class Course_4_3_1_blending_discard : public CourseWithCamera
{
public:
    Course_4_3_1_blending_discard();
    virtual ~Course_4_3_1_blending_discard();

    void render() override;
    virtual QList<QtProperty*> getPropertyList(QtVariantPropertyManager *manager) override;

protected:
    unsigned int loadTexture(const char *path, bool gammaCorrection = false) override;
private:
    unsigned int cubeVAO, cubeVBO;
    unsigned int planeVAO, planeVBO;
    unsigned int transparentVAO, transparentVBO;
    unsigned int cubeTexture, floorTexture, transparentTexture;

    QOpenGLShaderProgram mProgram;
};

#endif // COURSE_4_3_1_BLENDING_DISCARD_H
