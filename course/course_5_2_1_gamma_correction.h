#ifndef COURSE_5_2_1_GAMMA_CORRECTION_H
#define COURSE_5_2_1_GAMMA_CORRECTION_H

#include "course.h"
#include <QOpenGLExtraFunctions>
#include <QOpenGLShaderProgram>
#include <QMatrix4x4>
#include "core/camera.h"
#include "coursewithcamera.h"

class Course_5_2_1_gamma_correction : public CourseWithCamera
{
public:
    Course_5_2_1_gamma_correction();
    virtual ~Course_5_2_1_gamma_correction();

    void render() override;
    virtual QList<QtProperty*> getPropertyList(QtVariantPropertyManager *manager) override;
protected:
    unsigned int loadTexture(const char *path, bool gammaCorrection = false) override;
    void processInput() override;
private:
    unsigned int planeVAO, planeVBO;
    unsigned int floorTexture, floorTextureGammaCorrected;
    bool gammaEnabled, gammaKeyPressed;
    QOpenGLShaderProgram mProgram;
};

#endif // COURSE_5_2_1_GAMMA_CORRECTION_H
