#ifndef COURSE_6_2_1_2_IBL_IRRADIANCE_H
#define COURSE_6_2_1_2_IBL_IRRADIANCE_H

#include "course.h"
#include <QOpenGLExtraFunctions>
#include <QOpenGLShaderProgram>
#include <QMatrix4x4>
#include "core/camera.h"
#include "coursewithcamera.h"

class Course_6_2_1_2_ibl_irradiance : public CourseWithCamera
{
public:
    Course_6_2_1_2_ibl_irradiance();
    virtual ~Course_6_2_1_2_ibl_irradiance();

    void init(GlWindow *glWindow = nullptr) override;
    void render() override;
    virtual QList<QtProperty*> getPropertyList(QtVariantPropertyManager *manager) override;
private:
    void renderSphere();
    void renderCube();
    float clamp(float x, float minVal, float maxVal);
private:
    int SCR_WIDTH, SCR_HEIGHT;
    QVector<QVector3D> lightPositions;
    QVector<QVector3D> lightColors;
    int nrRows, nrColumns;
    float spacing;
    unsigned int captureFBO;
    unsigned int captureRBO;
    unsigned int hdrTexture;
    unsigned int envCubemap;
    unsigned int irradianceMap;
    unsigned int sphereVAO;
    unsigned int vbo, ebo;
    unsigned int cubeVAO;
    unsigned int cubeVBO;
    unsigned int indexCount;
    QOpenGLShaderProgram pbrShader, equirectangularToCubemapShader, irradianceShader, backgroundShader;
};

#endif // COURSE_6_2_1_2_IBL_IRRADIANCE_H
