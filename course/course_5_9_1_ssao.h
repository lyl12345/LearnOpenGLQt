#ifndef COURSE_5_9_1_SSAO_H
#define COURSE_5_9_1_SSAO_H

#include "course.h"
#include <QOpenGLExtraFunctions>
#include <QOpenGLShaderProgram>
#include <QMatrix4x4>
#include "core/camera.h"
#include "coursewithcamera.h"
#include "core/model.h"

class Course_5_9_1_ssao : public CourseWithCamera
{
public:
    Course_5_9_1_ssao();
    virtual ~Course_5_9_1_ssao();

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
    unsigned int gBuffer;
    unsigned int gPosition, gNormal, gAlbedo;
    unsigned int rboDepth;
    unsigned int ssaoFBO, ssaoBlurFBO;
    unsigned int ssaoColorBuffer, ssaoColorBufferBlur;
    QVector<QVector3D> ssaoKernel;
    QVector<QVector3D> ssaoNoise;
    unsigned int noiseTexture;
    QVector3D lightPos;
    QVector3D lightColor;
    unsigned int cubeVAO;
    unsigned int cubeVBO;
    unsigned int quadVAO;
    unsigned int quadVBO;
    QOpenGLShaderProgram shaderGeometryPass, shaderLightingPass, shaderSSAO, shaderSSAOBlur;
};

#endif // COURSE_5_9_1_SSAO_H
