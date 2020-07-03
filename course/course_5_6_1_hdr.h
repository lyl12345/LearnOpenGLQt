#ifndef COURSE_5_6_1_HDR_H
#define COURSE_5_6_1_HDR_H

#include "course.h"
#include <QOpenGLExtraFunctions>
#include <QOpenGLShaderProgram>
#include <QMatrix4x4>
#include "core/camera.h"
#include "coursewithcamera.h"

class Course_5_6_1_hdr : public CourseWithCamera
{
public:
    Course_5_6_1_hdr();
    virtual ~Course_5_6_1_hdr();

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
    unsigned int woodTexture;
    QVector3D lightPos;
    unsigned int hdrFBO;
    unsigned int colorBuffer;
    unsigned int rboDepth;
    unsigned int cubeVAO;
    unsigned int cubeVBO;
    unsigned int quadVAO;
    unsigned int quadVBO;
    bool hdr, hdrKeyPressed;
    float exposure;
    QOpenGLShaderProgram shader, hdrShader;

    QVector<QVector3D> lightPositions;
    QVector<QVector3D> lightColors;
};

#endif // COURSE_5_6_1_HDR_H
