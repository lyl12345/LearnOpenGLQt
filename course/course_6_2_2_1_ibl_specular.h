#ifndef COURSE_6_2_2_1_IBL_SPECULAR_H
#define COURSE_6_2_2_1_IBL_SPECULAR_H

#include "course.h"
#include <QOpenGLExtraFunctions>
#include <QOpenGLShaderProgram>
#include <QMatrix4x4>
#include "core/camera.h"
#include "coursewithcamera.h"

class Course_6_2_2_1_ibl_specular : public CourseWithCamera
{
public:
    Course_6_2_2_1_ibl_specular();
    virtual ~Course_6_2_2_1_ibl_specular();

    void init(GlWindow *glWindow = nullptr) override;
    void render() override;
    virtual QList<QtProperty*> getPropertyList(QtVariantPropertyManager *manager) override;
private:
    void renderSphere();
    void renderCube();
    void renderQuad();
    float clamp(float x, float minVal, float maxVal);
private:
    int SCR_WIDTH,SCR_HEIGHT;
    QVector<QVector3D> lightPositions;
    QVector<QVector3D> lightColors;
    int nrRows, nrColumns;
    float spacing;
    unsigned int captureFBO;
    unsigned int captureRBO;
    unsigned int envCubemap;
    unsigned int irradianceMap;
    unsigned int prefilterMap;
    unsigned int brdfLUTTexture;
    unsigned int sphereVAO;
    unsigned int vbo, ebo;
    unsigned int indexCount;
    unsigned int quadVAO;
    unsigned int quadVBO;
    unsigned int cubeVAO;
    unsigned int cubeVBO;
    QOpenGLShaderProgram pbrShader, equirectangularToCubemapShader, irradianceShader;
    QOpenGLShaderProgram prefilterShader, brdfShader, backgroundShader;
};

#endif // COURSE_6_2_2_1_IBL_SPECULAR_H
