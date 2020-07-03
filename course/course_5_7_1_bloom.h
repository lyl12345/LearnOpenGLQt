#ifndef COURSE_5_7_1_BLOOM_H
#define COURSE_5_7_1_BLOOM_H

#include "course.h"
#include <QOpenGLExtraFunctions>
#include <QOpenGLShaderProgram>
#include <QMatrix4x4>
#include "core/camera.h"
#include "coursewithcamera.h"

class Course_5_7_1_bloom : public CourseWithCamera
{
public:
    Course_5_7_1_bloom();
    virtual ~Course_5_7_1_bloom();

    void init(GlWindow *glWindow = nullptr) override;
    void render() override;
    virtual QList<QtProperty*> getPropertyList(QtVariantPropertyManager *manager) override;
protected:
    void processInput() override;
    void Resize(QResizeEvent *event) override;
private:
    void renderCube();
    void renderQuad();
private:
    bool bloom;
    bool bloomKeyPressed;
    float exposure;
    unsigned int woodTexture, containerTexture;
    unsigned int hdrFBO;
    unsigned int colorBuffers[2];
    unsigned int rboDepth;
    unsigned int attachments[2];
    unsigned int pingpongFBO[2];
    unsigned int pingpongColorbuffers[2];
    QVector<QVector3D> lightPositions, lightColors;
    unsigned int cubeVAO;
    unsigned int cubeVBO;
    unsigned int quadVAO;
    unsigned int quadVBO;
    QOpenGLShaderProgram shader, shaderLight, shaderBlur, shaderBloomFinal;
};

#endif // COURSE_5_7_1_BLOOM_H
