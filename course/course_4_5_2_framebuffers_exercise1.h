#ifndef COURSE_4_5_2_FRAMEBUFFERS_EXERCISE1_H
#define COURSE_4_5_2_FRAMEBUFFERS_EXERCISE1_H

#include "course.h"
#include <QOpenGLExtraFunctions>
#include <QOpenGLShaderProgram>
#include <QMatrix4x4>
#include "core/camera.h"
#include "coursewithcamera.h"

class Course_4_5_2_framebuffers_exercise1 : public CourseWithCamera
{
public:
    Course_4_5_2_framebuffers_exercise1();
    virtual ~Course_4_5_2_framebuffers_exercise1();

    void render() override;
    virtual QList<QtProperty*> getPropertyList(QtVariantPropertyManager *manager) override;
protected:
    unsigned int loadTexture(const char *path,bool gammaCorrection = false) override;
private:
    unsigned int cubeVAO, cubeVBO;
    unsigned int planeVAO, planeVBO;
    unsigned int quadVAO, quadVBO;
    unsigned int cubeTexture, floorTexture;
    unsigned int framebuffer, textureColorbuffer;
    unsigned int rbo;

    QOpenGLShaderProgram mProgram, mScreenProgram;
};

#endif // COURSE_4_5_2_FRAMEBUFFERS_EXERCISE1_H
