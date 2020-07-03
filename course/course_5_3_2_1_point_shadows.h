#ifndef COURSE_5_3_2_1_POINT_SHADOWS_H
#define COURSE_5_3_2_1_POINT_SHADOWS_H

#include "course.h"
#include <QOpenGLExtraFunctions>
#include <QOpenGLShaderProgram>
#include <QMatrix4x4>
#include "core/camera.h"
#include "coursewithcamera.h"

class Course_5_3_2_1_point_shadows : public CourseWithCamera
{
public:
    Course_5_3_2_1_point_shadows();
    virtual ~Course_5_3_2_1_point_shadows();

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

#endif // COURSE_5_3_2_1_POINT_SHADOWS_H
