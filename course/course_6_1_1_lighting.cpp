#include "course_6_1_1_lighting.h"
#include <QDir>
#include <QDebug>
#include "stb_image.h"
#include <QResizeEvent>
#include <math.h>

float clamp(float x, float minVal, float maxVal)
{
    return fmin(fmax(x, minVal), maxVal);
}

Course_6_1_1_lighting::Course_6_1_1_lighting()
    :CourseWithCamera()
    ,nrRows(7)
    ,nrColumns(7)
    ,spacing(2.5)
    ,sphereVAO(0)
{
    initializeOpenGLFunctions();
}

Course_6_1_1_lighting::~Course_6_1_1_lighting()
{
    glDeleteVertexArrays(1, &sphereVAO);
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &ebo);
}

void Course_6_1_1_lighting::init(GlWindow *glWindow)
{
    setGlWindow(glWindow);
    glEnable(GL_DEPTH_TEST);

    QString shaderPath = QDir::currentPath() + "/shaders/6.pbr/1.1.lighting/";
    shader.addShaderFromSourceFile(QOpenGLShader::Vertex,shaderPath+"1.1.pbr.vs");
    shader.addShaderFromSourceFile(QOpenGLShader::Fragment,shaderPath+"1.1.pbr.fs");
    shader.link();

    shader.bind();
    shader.setUniformValue("albedo", QVector3D(0.5f, 0.0f, 0.0f));
    shader.setUniformValue("ao", 1.0f);

    lightPositions.push_back(QVector3D(-10.0f,  10.0f, 10.0f));
    lightPositions.push_back(QVector3D( 10.0f,  10.0f, 10.0f));
    lightPositions.push_back(QVector3D(-10.0f, -10.0f, 10.0f));
    lightPositions.push_back(QVector3D( 10.0f, -10.0f, 10.0f));

    lightColors.push_back(QVector3D(300.0f, 300.0f, 300.0f));
    lightColors.push_back(QVector3D(300.0f, 300.0f, 300.0f));
    lightColors.push_back(QVector3D(300.0f, 300.0f, 300.0f));
    lightColors.push_back(QVector3D(300.0f, 300.0f, 300.0f));

    QMatrix4x4 projection;
    projection.perspective(mCamera.Zoom, 1280/720, 0.1f, 100.0f);
    shader.bind();
    shader.setUniformValue("projection", projection);
}

void Course_6_1_1_lighting::render()
{
    Course::render();

    processInput();

    // render
    // ------
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    shader.bind();
    QMatrix4x4 view = mCamera.GetViewMatrix();
    shader.setUniformValue("view", view);
    shader.setUniformValue("camPos", mCamera.Position);

    // render rows*column number of spheres with varying metallic/roughness values scaled by rows and columns respectively
    QMatrix4x4 model;
    for (int row = 0; row < nrRows; ++row)
    {
        shader.setUniformValue("metallic", (float)row / (float)nrRows);
        for (int col = 0; col < nrColumns; ++col)
        {
            // we clamp the roughness to 0.025 - 1.0 as perfectly smooth surfaces (roughness of 0.0) tend to look a bit off
            // on direct lighting.
            shader.setUniformValue("roughness", clamp((float)col / (float)nrColumns, 0.05f, 1.0f));

            model.setToIdentity();
            model.translate(QVector3D(
                                (col - (nrColumns / 2)) * spacing,
                                (row - (nrRows / 2)) * spacing,
                                0.0f
                                ));
            shader.setUniformValue("model", model);
            renderSphere();
        }
    }

    // render light source (simply re-render sphere at light positions)
    // this looks a bit off as we use the same shader, but it'll make their positions obvious and
    // keeps the codeprint small.
    for (unsigned int i = 0; i < lightPositions.size(); ++i)
    {
        QVector3D newPos = lightPositions[i] + QVector3D(sin(mDuration * 5.0) * 5.0, 0.0, 0.0);
        newPos = lightPositions[i];
        QString name = "lightPositions[" + QString::number(i) + "]";
        shader.setUniformValue(name.toStdString().c_str(), newPos);
        name = "lightColors[" + QString::number(i) + "]";
        shader.setUniformValue(name.toStdString().c_str(), lightColors[i]);

        model.setToIdentity();
        model.translate(newPos);
        model.scale(QVector3D(0.5f, 0.5f, 0.5f));
        shader.setUniformValue("model", model);
        renderSphere();
    }
}

QList<QtProperty *> Course_6_1_1_lighting::getPropertyList(QtVariantPropertyManager *manager)
{
    GETPROPERTYLIST(Course_6_1_1_lighting)
}

void Course_6_1_1_lighting::renderSphere()
{
    if (sphereVAO == 0)
    {
        glGenVertexArrays(1, &sphereVAO);

        glGenBuffers(1, &vbo);
        glGenBuffers(1, &ebo);

        QVector<QVector3D> positions;
        QVector<QVector3D> uv;
        QVector<QVector3D> normals;
        std::vector<unsigned int> indices;

        const unsigned int X_SEGMENTS = 64;
        const unsigned int Y_SEGMENTS = 64;
        const float PI = 3.14159265359;
        for (unsigned int y = 0; y <= Y_SEGMENTS; ++y)
        {
            for (unsigned int x = 0; x <= X_SEGMENTS; ++x)
            {
                float xSegment = (float)x / (float)X_SEGMENTS;
                float ySegment = (float)y / (float)Y_SEGMENTS;
                float xPos = std::cos(xSegment * 2.0f * PI) * std::sin(ySegment * PI);
                float yPos = std::cos(ySegment * PI);
                float zPos = std::sin(xSegment * 2.0f * PI) * std::sin(ySegment * PI);

                positions.push_back(QVector3D(xPos, yPos, zPos));
                uv.push_back(QVector2D(xSegment, ySegment));
                normals.push_back(QVector3D(xPos, yPos, zPos));
            }
        }

        bool oddRow = false;
        for (unsigned int y = 0; y < Y_SEGMENTS; ++y)
        {
            if (!oddRow) // even rows: y == 0, y == 2; and so on
            {
                for (unsigned int x = 0; x <= X_SEGMENTS; ++x)
                {
                    indices.push_back(y       * (X_SEGMENTS + 1) + x);
                    indices.push_back((y + 1) * (X_SEGMENTS + 1) + x);
                }
            }
            else
            {
                for (int x = X_SEGMENTS; x >= 0; --x)
                {
                    indices.push_back((y + 1) * (X_SEGMENTS + 1) + x);
                    indices.push_back(y       * (X_SEGMENTS + 1) + x);
                }
            }
            oddRow = !oddRow;
        }
        indexCount = indices.size();

        std::vector<float> data;
        for (unsigned int i = 0; i < positions.size(); ++i)
        {
            data.push_back(positions[i].x());
            data.push_back(positions[i].y());
            data.push_back(positions[i].z());
            if (uv.size() > 0)
            {
                data.push_back(uv[i].x());
                data.push_back(uv[i].y());
            }
            if (normals.size() > 0)
            {
                data.push_back(normals[i].x());
                data.push_back(normals[i].y());
                data.push_back(normals[i].z());
            }
        }
        glBindVertexArray(sphereVAO);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), &data[0], GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
        float stride = (3 + 2 + 3) * sizeof(float);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void*)0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, stride, (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, stride, (void*)(5 * sizeof(float)));
    }

    glBindVertexArray(sphereVAO);
    glDrawElements(GL_TRIANGLE_STRIP, indexCount, GL_UNSIGNED_INT, 0);
}
