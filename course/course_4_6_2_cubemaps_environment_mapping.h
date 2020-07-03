#ifndef COURSE_4_6_2_CUBEMAPS_ENVIRONMENT_MAPPING_H
#define COURSE_4_6_2_CUBEMAPS_ENVIRONMENT_MAPPING_H

#include "course.h"
#include <QOpenGLExtraFunctions>
#include <QOpenGLShaderProgram>
#include <QMatrix4x4>
#include "core/camera.h"
#include "coursewithcamera.h"

class Course_4_6_2_cubemaps_environment_mapping : public CourseWithCamera
{
public:
    Course_4_6_2_cubemaps_environment_mapping();
    virtual ~Course_4_6_2_cubemaps_environment_mapping();

    void render() override;
    virtual QList<QtProperty*> getPropertyList(QtVariantPropertyManager *manager) override;
private:
    unsigned int cubeVAO, cubeVBO;
    unsigned int skyboxVAO, skyboxVBO;
    unsigned int cubemapTexture;

    QOpenGLShaderProgram mProgram, mSkyboxProgram;
};

#endif // COURSE_4_6_2_CUBEMAPS_ENVIRONMENT_MAPPING_H
