#ifndef COURSE_7_1_1_DEBUGGING_H
#define COURSE_7_1_1_DEBUGGING_H

#include "course.h"
#include <QOpenGLExtraFunctions>
#include <QOpenGLShaderProgram>
#include <QMatrix4x4>
#include "core/camera.h"
#include "coursewithcamera.h"
#include <QOpenGLDebugMessage>

class Course_7_1_1_debugging : public CourseWithCamera
{
public:
    Course_7_1_1_debugging();
    virtual ~Course_7_1_1_debugging();

    void init(GlWindow *glWindow = nullptr) override;
    void render() override;
    virtual QList<QtProperty*> getPropertyList(QtVariantPropertyManager *manager) override;
private slots:
    void handleLoggedMessage(const QOpenGLDebugMessage &debugMessage);
private:
    unsigned int cubeVAO, cubeVBO;
    unsigned int texture;
    QOpenGLShaderProgram shader;
};

#endif // COURSE_7_1_1_DEBUGGING_H
