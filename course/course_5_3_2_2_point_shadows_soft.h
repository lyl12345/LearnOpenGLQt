#ifndef COURSE_5_3_2_2_POINT_SHADOWS_SOFT_H
#define COURSE_5_3_2_2_POINT_SHADOWS_SOFT_H

#include "course.h"
#include <QOpenGLExtraFunctions>
#include <QOpenGLShaderProgram>
#include <QMatrix4x4>
#include "core/camera.h"
#include "coursewithcamera.h"

class Course_5_3_2_2_point_shadows_soft : public CourseWithCamera
{
public:
    Course_5_3_2_2_point_shadows_soft();
    virtual ~Course_5_3_2_2_point_shadows_soft();

    void render() override;
    virtual QList<QtProperty*> getPropertyList(QtVariantPropertyManager *manager) override;
protected:
    void processInput() override;

private:
    void renderScene(QOpenGLShaderProgram &shader);
    void renderCube();
private:
    unsigned int woodTexture;
    unsigned int depthMapFBO;
    unsigned int depthCubemap;
    unsigned int cubeVAO;
    unsigned int cubeVBO;

    bool shadows, shadowsKeyPressed;
    QVector3D lightPos;
    QOpenGLShaderProgram shader, simpleDepthShader;
};

#endif // COURSE_5_3_2_2_POINT_SHADOWS_SOFT_H
