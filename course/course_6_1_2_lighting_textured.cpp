#include "course_6_1_2_lighting_textured.h"
#include <QDir>
#include <QDebug>
#include "stb_image.h"

Course_6_1_2_lighting_textured::Course_6_1_2_lighting_textured()
    :CourseWithCamera()
    ,nrRows(7)
    ,nrColumns(7)
    ,spacing(2.5)
    ,sphereVAO(0)
{
    initializeOpenGLFunctions();
}

Course_6_1_2_lighting_textured::~Course_6_1_2_lighting_textured()
{
    glDeleteTextures(1, &albedo);
    glDeleteTextures(1, &normal);
    glDeleteTextures(1, &metallic);
    glDeleteTextures(1, &roughness);
    glDeleteTextures(1, &ao);
    glDeleteVertexArrays(1, &sphereVAO);
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &ebo);
}

void Course_6_1_2_lighting_textured::init(GlWindow *glWindow)
{
    setGlWindow(glWindow);
    glEnable(GL_DEPTH_TEST);

    QString shaderPath = QDir::currentPath() + "/shaders/6.pbr/1.2.lighting_textured/";
    shader.addShaderFromSourceFile(QOpenGLShader::Vertex,shaderPath+"1.2.pbr.vs");
    shader.addShaderFromSourceFile(QOpenGLShader::Fragment,shaderPath+"1.2.pbr.fs");
    shader.link();

    shader.bind();
    shader.setUniformValue("albedoMap", 0);
    shader.setUniformValue("normalMap", 1);
    shader.setUniformValue("metallicMap", 2);
    shader.setUniformValue("roughnessMap", 3);
    shader.setUniformValue("aoMap", 4);

    QString path = QDir::currentPath() + "/resources/textures/pbr/rusted_iron/albedo.png";
    albedo = loadTexture(path.toStdString().c_str());
    path = QDir::currentPath() + "/resources/textures/pbr/rusted_iron/normal.png";
    normal = loadTexture(path.toStdString().c_str());
    path = QDir::currentPath() + "/resources/textures/pbr/rusted_iron/metallic.png";
    metallic = loadTexture(path.toStdString().c_str());
    path = QDir::currentPath() + "/resources/textures/pbr/rusted_iron/roughness.png";
    roughness = loadTexture(path.toStdString().c_str());
    path = QDir::currentPath() + "/resources/textures/pbr/rusted_iron/ao.png";
    ao = loadTexture(path.toStdString().c_str());

    lightPositions.push_back(QVector3D(0.0f, 0.0f, 10.0f));
    lightColors.push_back(QVector3D(150.0f, 150.0f, 150.0f));

    QMatrix4x4 projection;
    projection.perspective(mCamera.Zoom, 800/600, 0.1f, 100.0f);
    shader.bind();
    shader.setUniformValue("projection", projection);
}

void Course_6_1_2_lighting_textured::render()
{
    Course::render();

    processInput();

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    shader.bind();
    QMatrix4x4 view = mCamera.GetViewMatrix();
    shader.setUniformValue("view", view);
    shader.setUniformValue("camPos", mCamera.Position);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, albedo);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, normal);
    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, metallic);
    glActiveTexture(GL_TEXTURE3);
    glBindTexture(GL_TEXTURE_2D, roughness);
    glActiveTexture(GL_TEXTURE4);
    glBindTexture(GL_TEXTURE_2D, ao);

    // render rows*column number of spheres with material properties defined by textures (they all have the same material properties)
    QMatrix4x4 model;
    for (int row = 0; row < nrRows; ++row)
    {
        for (int col = 0; col < nrColumns; ++col)
        {
            model.setToIdentity();
            model.translate(QVector3D(
                                (float)(col - (nrColumns / 2)) * spacing,
                                (float)(row - (nrRows / 2)) * spacing,
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
        QString path = "lightPositions[" + QString::number(i) + "]";
        shader.setUniformValue(path.toStdString().c_str(), newPos);
        path = "lightColors[" + QString::number(i) + "]";
        shader.setUniformValue(path.toStdString().c_str(), lightColors[i]);

        model.setToIdentity();
        model.translate(newPos);
        model.scale(QVector3D(0.5f, 0.5f, 0.5f));
        shader.setUniformValue("model", model);
        renderSphere();
    }
}

QList<QtProperty *> Course_6_1_2_lighting_textured::getPropertyList(QtVariantPropertyManager *manager)
{
    GETPROPERTYLIST(Course_6_1_2_lighting_textured)
}

void Course_6_1_2_lighting_textured::renderSphere()
{
    if (sphereVAO == 0)
    {
        glGenVertexArrays(1, &sphereVAO);

        glGenBuffers(1, &vbo);
        glGenBuffers(1, &ebo);

        QVector<QVector3D> positions;
        QVector<QVector2D> uv;
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
        for (std::size_t i = 0; i < positions.size(); ++i)
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
