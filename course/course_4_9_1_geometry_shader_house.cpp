#include "course_4_9_1_geometry_shader_house.h"
#include <QDir>
#include <QDebug>
#include "stb_image.h"

Course_4_9_1_geometry_shader_house::Course_4_9_1_geometry_shader_house()
    :CourseWithCamera()
{
    initializeOpenGLFunctions();

    glEnable(GL_DEPTH_TEST);

    QString shaderPath = QDir::currentPath() + "/shaders/4.advanced_opengl/9.1.geometry_shader_houses/";
    mProgram.addShaderFromSourceFile(QOpenGLShader::Vertex,shaderPath+"9.1.geometry_shader.vs");
    mProgram.addShaderFromSourceFile(QOpenGLShader::Fragment,shaderPath+"9.1.geometry_shader.fs");
    mProgram.addShaderFromSourceFile(QOpenGLShader::Geometry,shaderPath+"9.1.geometry_shader.gs");
    mProgram.link();

    float points[] = {
        -0.5f,  0.5f, 1.0f, 0.0f, 0.0f, // top-left
         0.5f,  0.5f, 0.0f, 1.0f, 0.0f, // top-right
         0.5f, -0.5f, 0.0f, 0.0f, 1.0f, // bottom-right
        -0.5f, -0.5f, 1.0f, 1.0f, 0.0f  // bottom-left
    };

    glGenBuffers(1, &VBO);
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(points), &points, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), 0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(2 * sizeof(float)));
    glBindVertexArray(0);
}

Course_4_9_1_geometry_shader_house::~Course_4_9_1_geometry_shader_house()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}

void Course_4_9_1_geometry_shader_house::render()
{
    Course::render();

    processInput();

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // draw points
    mProgram.bind();
    glBindVertexArray(VAO);
    glDrawArrays(GL_POINTS, 0, 4);
}

QList<QtProperty *> Course_4_9_1_geometry_shader_house::getPropertyList(QtVariantPropertyManager *manager)
{
    GETPROPERTYLIST(Course_4_9_1_geometry_shader_house)
}
