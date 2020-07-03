#include "coursewithcamera.h"
#include <QMouseEvent>
#include "stb_image.h"

CourseWithCamera::CourseWithCamera(QObject *parent)
    :Course(parent)
    ,mCamera(QVector3D(0.0f, 0.0f, 3.0f))
{ 
    initializeOpenGLFunctions();
}

CourseWithCamera::~CourseWithCamera()
{
}

void CourseWithCamera::enter(QEvent *event)
{
    Q_UNUSED(event);
}

void CourseWithCamera::leave(QEvent *event)
{
    Q_UNUSED(event);
    mPressedKey.clear();
}

void CourseWithCamera::mousePressEvent(QMouseEvent *event)
{
    mMousePressed = true;
    QPoint pos = event->pos();
    mLastX = pos.x();
    mLastY = pos.y();
}

void CourseWithCamera::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    mMousePressed = false;
}

void CourseWithCamera::mouseMoveEvent(QMouseEvent *event)
{
    if (mMousePressed){
        QPoint pos = event->pos();
        int xpos = pos.x();
        int ypos = pos.y();
        float xoffset = xpos - mLastX;
        float yoffset = mLastY - ypos; // reversed since y-coordinates go from bottom to top
        mLastX = xpos;
        mLastY = ypos;
        mCamera.ProcessMouseMovement(xoffset, yoffset);
    }
}

void CourseWithCamera::wheelEvent(QWheelEvent *event)
{
    QPoint numPixels = event->angleDelta() / 120;
    mCamera.ProcessMouseScroll(numPixels.y());
}

void CourseWithCamera::keyPressEvent(QKeyEvent *event)
{
    mPressedKey.insert(event->key());
    Course::keyPressEvent(event);
}

void CourseWithCamera::keyReleaseEvent(QKeyEvent *event)
{
    mPressedKey.remove(event->key());
    Course::keyReleaseEvent(event);
}

void CourseWithCamera::processInput()
{
    if (mPressedKey.contains(Qt::Key_W)){
        mCamera.ProcessKeyboard(FORWARD, mDelta);
    }
    if (mPressedKey.contains(Qt::Key_S)){
        mCamera.ProcessKeyboard(BACKWARD, mDelta);
    }
    if (mPressedKey.contains(Qt::Key_A)){
        mCamera.ProcessKeyboard(LEFT, mDelta);
    }
    if (mPressedKey.contains(Qt::Key_D)){
        mCamera.ProcessKeyboard(RIGHT, mDelta);
    }
}

unsigned int CourseWithCamera::loadTexture(const char *path, bool gammaCorrection)
{
    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    unsigned char *data = stbi_load(path, &width, &height, &nrComponents, 0);
    if (data)
    {
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
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

unsigned int CourseWithCamera::loadTexture2(const char *path, bool gammaCorrection)
{
    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    unsigned char *data = stbi_load(path, &width, &height, &nrComponents, 0);
    if (data)
    {
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, format == GL_RGBA ? GL_CLAMP_TO_EDGE : GL_REPEAT); // for this tutorial: use GL_CLAMP_TO_EDGE to prevent semi-transparent borders. Due to interpolation it takes texels from next repeat
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, format == GL_RGBA ? GL_CLAMP_TO_EDGE : GL_REPEAT);
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

unsigned int CourseWithCamera::loadTexture3(const char *path, bool gammaCorrection)
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

unsigned int CourseWithCamera::loadCubemap(QVector<QString> faces)
{
    unsigned int textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

    int width, height, nrChannels;
    for (unsigned int i = 0; i < faces.size(); i++)
    {
        unsigned char *data = stbi_load(faces[i].toStdString().c_str(), &width, &height, &nrChannels, 0);
        if (data)
        {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            stbi_image_free(data);
        }
        else
        {
            qDebug() << "Cubemap texture failed to load at path: " << faces[i];
            stbi_image_free(data);
        }
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    return textureID;
}
