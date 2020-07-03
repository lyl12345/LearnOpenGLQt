#ifndef COURSE_4_6_1_CUBEMAPS_SKYBOX_H
#define COURSE_4_6_1_CUBEMAPS_SKYBOX_H

#include "course.h"
#include <QOpenGLExtraFunctions>
#include <QOpenGLShaderProgram>
#include <QMatrix4x4>
#include "core/camera.h"
#include "coursewithcamera.h"

class Course_4_6_1_cubemaps_skybox : public CourseWithCamera
{
public:
    Course_4_6_1_cubemaps_skybox();
    virtual ~Course_4_6_1_cubemaps_skybox();

    void render() override;
    virtual QList<QtProperty*> getPropertyList(QtVariantPropertyManager *manager) override;
protected:
    unsigned int loadTexture(const char *path, bool gammaCorrection = false) override;
private:
    unsigned int cubeVAO, cubeVBO;
    unsigned int skyboxVAO, skyboxVBO;
    unsigned int cubeTexture, cubemapTexture;

    QOpenGLShaderProgram mProgram, mSkyboxProgram;
};

#endif // COURSE_4_6_1_CUBEMAPS_SKYBOX_H
