#include "course_5_5_1_parallax_mapping.h"
#include <QDir>
#include <QDebug>
#include "stb_image.h"

Course_5_5_1_parallax_mapping::Course_5_5_1_parallax_mapping()
    :CourseWithCamera()
    ,quadVAO(0)
    ,quadVBO(0)
    ,heightScale(0.1)
{
    initializeOpenGLFunctions();
    glEnable(GL_DEPTH_TEST);

    QString shaderPath = QDir::currentPath() + "/shaders/5.advanced_lighting/5.1.parallax_mapping/";
    shader.addShaderFromSourceFile(QOpenGLShader::Vertex,shaderPath+"5.1.parallax_mapping.vs");
    shader.addShaderFromSourceFile(QOpenGLShader::Fragment,shaderPath+"5.1.parallax_mapping.fs");
    shader.link();

    QString path = QDir::currentPath() + "/resources/textures/bricks2.jpg";
    diffuseMap = loadTexture(path.toStdString().c_str());
    path = QDir::currentPath() + "/resources/textures/bricks2_normal.jpg";
    normalMap = loadTexture(path.toStdString().c_str());
    path = QDir::currentPath() + "/resources/textures/bricks2_disp.jpg";
    heightMap = loadTexture(path.toStdString().c_str());

    shader.bind();
    shader.setUniformValue("diffuseMap", 0);
    shader.setUniformValue("normalMap", 1);
    shader.setUniformValue("depthMap", 2);

    lightPos = QVector3D(0.5f, 1.0f, 0.3f);
}

Course_5_5_1_parallax_mapping::~Course_5_5_1_parallax_mapping()
{
    glDeleteVertexArrays(1, &quadVAO);
    glDeleteBuffers(1, &quadVBO);
    glDeleteTextures(1, &diffuseMap);
    glDeleteTextures(1, &normalMap);
    glDeleteTextures(1, &heightMap);
}

void Course_5_5_1_parallax_mapping::render()
{
    Course::render();

    processInput();

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // configure view/projection matrices
    QMatrix4x4 projection;
    projection.perspective(mCamera.Zoom, 800/600, 0.1f, 100.0f);
    QMatrix4x4 view = mCamera.GetViewMatrix();
    shader.bind();
    shader.setUniformValue("projection", projection);
    shader.setUniformValue("view", view);
    // render parallax-mapped quad
    QMatrix4x4 model;
    model.rotate(mDuration * -10.0f, QVector3D(1.0, 0.0, 1.0).normalized());
    shader.setUniformValue("model", model);
    shader.setUniformValue("viewPos", mCamera.Position);
    shader.setUniformValue("lightPos", lightPos);
    shader.setUniformValue("heightScale", heightScale); // adjust with Q and E keys
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, diffuseMap);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, normalMap);
    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, heightMap);
    renderQuad();

    // render light source (simply re-renders a smaller plane at the light's position for debugging/visualization)
    model.setToIdentity();
    model.translate(lightPos);
    model.scale(QVector3D(0.1f, 0.1f, 0.1f));
    shader.setUniformValue("model", model);
    renderQuad();
}

QList<QtProperty *> Course_5_5_1_parallax_mapping::getPropertyList(QtVariantPropertyManager *manager)
{
    GETPROPERTYLIST(Course_5_5_1_parallax_mapping)
}

void Course_5_5_1_parallax_mapping::processInput()
{
    CourseWithCamera::processInput();

    if (mPressedKey.contains(Qt::Key_Q)){
        if (heightScale > 0.0f)
            heightScale -= 0.0005f;
        else
            heightScale = 0.0f;
    }else if (mPressedKey.contains(Qt::Key_E)){
        if (heightScale < 1.0f)
            heightScale += 0.0005f;
        else
            heightScale = 1.0f;
    }
}

void Course_5_5_1_parallax_mapping::renderQuad()
{
    if (quadVAO == 0)
    {
        // positions
        QVector3D pos1(-1.0f,  1.0f, 0.0f);
        QVector3D pos2(-1.0f, -1.0f, 0.0f);
        QVector3D pos3( 1.0f, -1.0f, 0.0f);
        QVector3D pos4( 1.0f,  1.0f, 0.0f);
        // texture coordinates
        QVector2D uv1(0.0f, 1.0f);
        QVector2D uv2(0.0f, 0.0f);
        QVector2D uv3(1.0f, 0.0f);
        QVector2D uv4(1.0f, 1.0f);
        // normal vector
        QVector3D nm(0.0f, 0.0f, 1.0f);

        // calculate tangent/bitangent vectors of both triangles
        QVector3D tangent1, bitangent1;
        QVector3D tangent2, bitangent2;
        // triangle 1
        // ----------
        QVector3D edge1 = pos2 - pos1;
        QVector3D edge2 = pos3 - pos1;
        QVector2D deltaUV1 = uv2 - uv1;
        QVector2D deltaUV2 = uv3 - uv1;

        float f = 1.0f / (deltaUV1.x() * deltaUV2.y() - deltaUV2.x() * deltaUV1.y());

        tangent1.setX(f * (deltaUV2.y() * edge1.x() - deltaUV1.y() * edge2.x()));
        tangent1.setY(f * (deltaUV2.y() * edge1.y() - deltaUV1.y() * edge2.y()));
        tangent1.setZ(f * (deltaUV2.y() * edge1.z() - deltaUV1.y() * edge2.z()));

        bitangent1.setX(f * (-deltaUV2.x() * edge1.x() + deltaUV1.x() * edge2.x()));
        bitangent1.setY(f * (-deltaUV2.x() * edge1.y() + deltaUV1.x() * edge2.y()));
        bitangent1.setZ(f * (-deltaUV2.x() * edge1.z() + deltaUV1.x() * edge2.z()));

        // triangle 2
        // ----------
        edge1 = pos3 - pos1;
        edge2 = pos4 - pos1;
        deltaUV1 = uv3 - uv1;
        deltaUV2 = uv4 - uv1;

        f = 1.0f / (deltaUV1.x() * deltaUV2.y() - deltaUV2.x() * deltaUV1.y());

        tangent2.setX(f * (deltaUV2.y() * edge1.x() - deltaUV1.y() * edge2.x()));
        tangent2.setY(f * (deltaUV2.y() * edge1.y() - deltaUV1.y() * edge2.y()));
        tangent2.setZ(f * (deltaUV2.y() * edge1.z() - deltaUV1.y() * edge2.z()));


        bitangent2.setX(f * (-deltaUV2.x() * edge1.x() + deltaUV1.x() * edge2.x()));
        bitangent2.setY(f * (-deltaUV2.x() * edge1.y() + deltaUV1.x() * edge2.y()));
        bitangent2.setZ(f * (-deltaUV2.x() * edge1.z() + deltaUV1.x() * edge2.z()));


        float quadVertices[] = {
            // positions            // normal         // texcoords  // tangent                          // bitangent
            pos1.x(), pos1.y(), pos1.z(), nm.x(), nm.y(), nm.z(), uv1.x(), uv1.y(), tangent1.x(), tangent1.y(), tangent1.z(), bitangent1.x(), bitangent1.y(), bitangent1.z(),
            pos2.x(), pos2.y(), pos2.z(), nm.x(), nm.y(), nm.z(), uv2.x(), uv2.y(), tangent1.x(), tangent1.y(), tangent1.z(), bitangent1.x(), bitangent1.y(), bitangent1.z(),
            pos3.x(), pos3.y(), pos3.z(), nm.x(), nm.y(), nm.z(), uv3.x(), uv3.y(), tangent1.x(), tangent1.y(), tangent1.z(), bitangent1.x(), bitangent1.y(), bitangent1.z(),

            pos1.x(), pos1.y(), pos1.z(), nm.x(), nm.y(), nm.z(), uv1.x(), uv1.y(), tangent2.x(), tangent2.y(), tangent2.z(), bitangent2.x(), bitangent2.y(), bitangent2.z(),
            pos3.x(), pos3.y(), pos3.z(), nm.x(), nm.y(), nm.z(), uv3.x(), uv3.y(), tangent2.x(), tangent2.y(), tangent2.z(), bitangent2.x(), bitangent2.y(), bitangent2.z(),
            pos4.x(), pos4.y(), pos4.z(), nm.x(), nm.y(), nm.z(), uv4.x(), uv4.y(), tangent2.x(), tangent2.y(), tangent2.z(), bitangent2.x(), bitangent2.y(), bitangent2.z()
        };
        // configure plane VAO
        glGenVertexArrays(1, &quadVAO);
        glGenBuffers(1, &quadVBO);
        glBindVertexArray(quadVAO);
        glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 14 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 14 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 14 * sizeof(float), (void*)(6 * sizeof(float)));
        glEnableVertexAttribArray(3);
        glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 14 * sizeof(float), (void*)(8 * sizeof(float)));
        glEnableVertexAttribArray(4);
        glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, 14 * sizeof(float), (void*)(11 * sizeof(float)));
    }
    glBindVertexArray(quadVAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}
