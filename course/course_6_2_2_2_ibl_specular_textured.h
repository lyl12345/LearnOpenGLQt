#ifndef COURSE_6_2_2_2_IBL_SPECULAR_TEXTURED_H
#define COURSE_6_2_2_2_IBL_SPECULAR_TEXTURED_H

#include "course.h"
#include <QOpenGLExtraFunctions>
#include <QOpenGLShaderProgram>
#include <QMatrix4x4>
#include "core/camera.h"
#include "coursewithcamera.h"

class Course_6_2_2_2_ibl_specular_textured : public CourseWithCamera
{
public:
    Course_6_2_2_2_ibl_specular_textured();
    virtual ~Course_6_2_2_2_ibl_specular_textured();

    void init(GlWindow *glWindow = nullptr) override;
    void render() override;
    virtual QList<QtProperty*> getPropertyList(QtVariantPropertyManager *manager) override;

private:
    void renderSphere();
    void renderCube();
    void renderQuad();
private:
    int SCR_WIDTH,SCR_HEIGHT;
    unsigned int ironAlbedoMap;
    unsigned int ironNormalMap;
    unsigned int ironMetallicMap;
    unsigned int ironRoughnessMap;
    unsigned int ironAOMap;

    unsigned int goldAlbedoMap;
    unsigned int goldNormalMap;
    unsigned int goldMetallicMap;
    unsigned int goldRoughnessMap;
    unsigned int goldAOMap;

    unsigned int grassAlbedoMap;
    unsigned int grassNormalMap;
    unsigned int grassMetallicMap;
    unsigned int grassRoughnessMap;
    unsigned int grassAOMap;

    unsigned int plasticAlbedoMap;
    unsigned int plasticNormalMap;
    unsigned int plasticMetallicMap;
    unsigned int plasticRoughnessMap;
    unsigned int plasticAOMap;

    unsigned int wallAlbedoMap;
    unsigned int wallNormalMap;
    unsigned int wallMetallicMap;
    unsigned int wallRoughnessMap;
    unsigned int wallAOMap;

    QVector<QVector3D> lightPositions;
    QVector<QVector3D> lightColors;

    unsigned int captureFBO;
    unsigned int captureRBO;
    unsigned int hdrTexture;
    unsigned int envCubemap;
    unsigned int irradianceMap;
    unsigned int prefilterMap;
    unsigned int brdfLUTTexture;

    unsigned int sphereVAO;
    unsigned int vbo,ebo;
    unsigned int indexCount;
    unsigned int cubeVAO;
    unsigned int cubeVBO;
    unsigned int quadVAO;
    unsigned int quadVBO;

    QOpenGLShaderProgram pbrShader, equirectangularToCubemapShader, irradianceShader;
    QOpenGLShaderProgram prefilterShader, brdfShader, backgroundShader;
};

#endif // COURSE_6_2_2_2_IBL_SPECULAR_TEXTURED_H
