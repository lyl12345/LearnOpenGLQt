#ifndef COURSE_4_5_1_FRAMEBUFFERS_H
#define COURSE_4_5_1_FRAMEBUFFERS_H

#include "course.h"
#include <QOpenGLExtraFunctions>
#include <QOpenGLShaderProgram>
#include <QMatrix4x4>
#include "core/camera.h"
#include "coursewithcamera.h"

class Course_4_5_1_framebuffers : public CourseWithCamera
{
public:
    Course_4_5_1_framebuffers();
    virtual ~Course_4_5_1_framebuffers();

    void init(GlWindow *glWindow) override;
    void render() override;
    virtual QList<QtProperty*> getPropertyList(QtVariantPropertyManager *manager) override;
protected:
    void Resize(QResizeEvent *event) override;
private:
    unsigned int cubeVAO, cubeVBO;
    unsigned int planeVAO, planeVBO;
    unsigned int quadVAO, quadVBO;
    unsigned int cubeTexture, floorTexture;
    unsigned int framebuffer, textureColorbuffer;
    unsigned int rbo;

    QOpenGLShaderProgram mProgram, mScreenProgram;
};

#endif // COURSE_4_5_1_FRAMEBUFFERS_H
