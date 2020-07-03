#ifndef COURSE_5_8_2_DEFERRED_SHADING_VOLUMES_H
#define COURSE_5_8_2_DEFERRED_SHADING_VOLUMES_H

#include "course.h"
#include <QOpenGLExtraFunctions>
#include <QOpenGLShaderProgram>
#include <QMatrix4x4>
#include "core/camera.h"
#include "coursewithcamera.h"
#include "core/model.h"

class Course_5_8_2_deferred_shading_volumes : public CourseWithCamera
{
public:
    Course_5_8_2_deferred_shading_volumes();
    virtual ~Course_5_8_2_deferred_shading_volumes();

    void init(GlWindow *glWindow = nullptr) override;
    void render() override;
    virtual QList<QtProperty*> getPropertyList(QtVariantPropertyManager *manager) override;
protected:
    void Resize(QResizeEvent *event) override;
private:
    void renderCube();
    void renderQuad();
private:
    int SCR_WIDTH, SCR_HEIGHT;
    Model *backpack;
    QVector<QVector3D> objectPositions;
    unsigned int gBuffer;
    unsigned int gPosition, gNormal, gAlbedoSpec;
    unsigned int rboDepth;
    const unsigned int NR_LIGHTS = 32;
    QVector<QVector3D> lightPositions;
    QVector<QVector3D> lightColors;
    unsigned int cubeVAO;
    unsigned int cubeVBO;
    unsigned int quadVAO;
    unsigned int quadVBO;
    QOpenGLShaderProgram shaderGeometryPass, shaderLightingPass, shaderLightBox;
};

#endif // COURSE_5_8_2_DEFERRED_SHADING_VOLUMES_H
