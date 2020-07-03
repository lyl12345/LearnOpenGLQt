#ifndef COURSE_4_11_2_ANTI_ALIASING_OFFSCREEN_H
#define COURSE_4_11_2_ANTI_ALIASING_OFFSCREEN_H

#include "course.h"
#include <QOpenGLExtraFunctions>
#include <QOpenGLShaderProgram>
#include <QMatrix4x4>
#include "core/camera.h"
#include "coursewithcamera.h"

class Course_4_11_2_anti_aliasing_offscreen : public CourseWithCamera
{
public:
    Course_4_11_2_anti_aliasing_offscreen();
    virtual ~Course_4_11_2_anti_aliasing_offscreen();

    void render() override;
    virtual QList<QtProperty*> getPropertyList(QtVariantPropertyManager *manager) override;
private:
    unsigned int cubeVAO, cubeVBO;
    unsigned int quadVAO, quadVBO;
    unsigned int framebuffer;
    unsigned int textureColorBufferMultiSampled;
    unsigned int intermediateFBO;
    unsigned int screenTexture;
    QOpenGLShaderProgram mProgram, mScreenProgram;

    typedef void (*GlTexImage2DMultisample) (GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations);
    GlTexImage2DMultisample glTexImage2DMultisample;
};

#endif // COURSE_4_11_2_ANTI_ALIASING_OFFSCREEN_H
