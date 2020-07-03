#include "course_5_2_1_gamma_correction.h"
#include <QDir>
#include <QDebug>
#include "stb_image.h"

Course_5_2_1_gamma_correction::Course_5_2_1_gamma_correction()
    :CourseWithCamera()
    ,gammaEnabled(false)
    ,gammaKeyPressed(false)
{
    initializeOpenGLFunctions();
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    QString shaderPath = QDir::currentPath() + "/shaders/5.advanced_lighting/2.gamma_correction/";
    mProgram.addShaderFromSourceFile(QOpenGLShader::Vertex,shaderPath+"2.gamma_correction.vs");
    mProgram.addShaderFromSourceFile(QOpenGLShader::Fragment,shaderPath+"2.gamma_correction.fs");
    mProgram.link();

    float planeVertices[] = {
        // positions            // normals         // texcoords
         10.0f, -0.5f,  10.0f,  0.0f, 1.0f, 0.0f,  10.0f,  0.0f,
        -10.0f, -0.5f,  10.0f,  0.0f, 1.0f, 0.0f,   0.0f,  0.0f,
        -10.0f, -0.5f, -10.0f,  0.0f, 1.0f, 0.0f,   0.0f, 10.0f,

         10.0f, -0.5f,  10.0f,  0.0f, 1.0f, 0.0f,  10.0f,  0.0f,
        -10.0f, -0.5f, -10.0f,  0.0f, 1.0f, 0.0f,   0.0f, 10.0f,
         10.0f, -0.5f, -10.0f,  0.0f, 1.0f, 0.0f,  10.0f, 10.0f
    };

    glGenVertexArrays(1, &planeVAO);
    glGenBuffers(1, &planeVBO);
    glBindVertexArray(planeVAO);
    glBindBuffer(GL_ARRAY_BUFFER, planeVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(planeVertices), planeVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glBindVertexArray(0);

    QString path = QDir::currentPath() + "/resources/textures/wood.png";
    floorTexture = loadTexture(path.toStdString().c_str(), false);
    path = QDir::currentPath() + "/resources/textures/wood.png";
    floorTextureGammaCorrected = loadTexture(path.toStdString().c_str(), true);

    mProgram.bind();
    mProgram.setUniformValue("floorTexture", 0);
    mProgram.release();
}

Course_5_2_1_gamma_correction::~Course_5_2_1_gamma_correction()
{
    glDisable(GL_BLEND);
    glDeleteVertexArrays(1, &planeVAO);
    glDeleteBuffers(1, &planeVBO);
    glDeleteTextures(1, &floorTexture);
    glDeleteTextures(1, &floorTextureGammaCorrected);
}

void Course_5_2_1_gamma_correction::render()
{
    Course::render();

    processInput();

    QVector3D lightPositions[] = {
        QVector3D(-3.0f, 0.0f, 0.0f),
        QVector3D(-1.0f, 0.0f, 0.0f),
        QVector3D (1.0f, 0.0f, 0.0f),
        QVector3D (3.0f, 0.0f, 0.0f)
    };
    QVector3D lightColors[] = {
        QVector3D(0.25,0.25,0.25),
        QVector3D(0.50,0.50,0.50),
        QVector3D(0.75,0.75,0.75),
        QVector3D(1.00,1.00,1.00)
    };

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // draw objects
    mProgram.bind();
    QMatrix4x4 projection;
    projection.perspective(mCamera.Zoom, 800 / 600, 1.0f, 100.0f);
    QMatrix4x4 view = mCamera.GetViewMatrix();
    mProgram.bind();
    mProgram.setUniformValue("projection", projection);
    mProgram.setUniformValue("view", view);
    // set light uniforms
    glUniform3fv(glGetUniformLocation(mProgram.programId(), "lightPositions"), 4, &lightPositions[0][0]);
    glUniform3fv(glGetUniformLocation(mProgram.programId(), "lightColors"), 4, &lightColors[0][0]);
    mProgram.setUniformValue("viewPos", mCamera.Position);
    mProgram.setUniformValue("gamma", gammaEnabled);
    // floor
    glBindVertexArray(planeVAO);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, gammaEnabled ? floorTextureGammaCorrected : floorTexture);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

QList<QtProperty *> Course_5_2_1_gamma_correction::getPropertyList(QtVariantPropertyManager *manager)
{
    GETPROPERTYLIST(Course_5_2_1_gamma_correction)
}

unsigned int Course_5_2_1_gamma_correction::loadTexture(const char *path, bool gammaCorrection)
{
    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    unsigned char *data = stbi_load(path, &width, &height, &nrComponents, 0);
    if (data)
    {
        GLenum internalFormat;
        GLenum dataFormat;
        if (nrComponents == 1)
        {
            internalFormat = dataFormat = GL_RED;
        }
        else if (nrComponents == 3)
        {
            internalFormat = gammaCorrection ? GL_SRGB : GL_RGB;
            dataFormat = GL_RGB;
        }
        else if (nrComponents == 4)
        {
            internalFormat = gammaCorrection ? GL_SRGB_ALPHA : GL_RGBA;
            dataFormat = GL_RGBA;
        }

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, dataFormat, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    }
    else
    {
        qDebug() << "Texture failed to load at path: " << path;
        stbi_image_free(data);
    }

    return textureID;
}

void Course_5_2_1_gamma_correction::processInput()
{
    CourseWithCamera::processInput();

    if (mPressedKey.contains(Qt::Key_Space) && !gammaKeyPressed){
        gammaEnabled = !gammaEnabled;
        gammaKeyPressed = true;
    }
    if (!mPressedKey.contains(Qt::Key_Space)){
        gammaKeyPressed = false;
    }
}
