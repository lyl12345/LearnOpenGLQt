#include "course_1_5_1_transformations.h"
#include <QDir>
#include <QDebug>
#include "stb_image.h"
#include <qmath.h>

Course_1_5_1_transformations::Course_1_5_1_transformations()
    :Course()
{
   initializeOpenGLFunctions();

   QString shaderPath = QDir::currentPath() + "/shaders/1.getting_started/5.1.transformations/";
   mProgram = new QOpenGLShaderProgram();
   mProgram->addShaderFromSourceFile(QOpenGLShader::Vertex,shaderPath+"5.1.transform.vs");
   mProgram->addShaderFromSourceFile(QOpenGLShader::Fragment,shaderPath+"5.1.transform.fs");
   mProgram->link();

   float vertices[] = {
       // positions          // texture coords
        0.5f,  0.5f, 0.0f,   1.0f, 1.0f, // top right
        0.5f, -0.5f, 0.0f,   1.0f, 0.0f, // bottom right
       -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, // bottom left
       -0.5f,  0.5f, 0.0f,   0.0f, 1.0f  // top left
   };
   unsigned int indices[] = {
       0, 1, 3, // first triangle
       1, 2, 3  // second triangle
   };

   glGenVertexArrays(1, &VAO);
   glGenBuffers(1, &VBO);
   glGenBuffers(1, &EBO);

   glBindVertexArray(VAO);

   glBindBuffer(GL_ARRAY_BUFFER, VBO);
   glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
   glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

   // position attribute
   glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
   glEnableVertexAttribArray(0);
   // texture coord attribute
   glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
   glEnableVertexAttribArray(1);

   // texture 1
   // ---------
   glGenTextures(1, &texture1);
   glBindTexture(GL_TEXTURE_2D, texture1);
   // set the texture wrapping parameters
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
   // set texture filtering parameters
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
   // load image, create texture and generate mipmaps
   int width, height, nrChannels;
   stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
   QString texturePath = QDir::currentPath() + "/resources/textures/container.jpg";
   unsigned char *data = stbi_load(texturePath.toStdString().c_str(), &width, &height, &nrChannels, 0);
   if (data)
   {
       glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
       glGenerateMipmap(GL_TEXTURE_2D);
   }
   else
   {
       qDebug() << "Failed to load texture:" << texturePath;
   }
   stbi_image_free(data);
   // texture 2
   // ---------
   glGenTextures(1, &texture2);
   glBindTexture(GL_TEXTURE_2D, texture2);
   // set the texture wrapping parameters
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
   // set texture filtering parameters
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
   // load image, create texture and generate mipmaps
   texturePath = QDir::currentPath() + "/resources/textures/awesomeface.png";
   data = stbi_load(texturePath.toStdString().c_str(), &width, &height, &nrChannels, 0);
   if (data)
   {
       // note that the awesomeface.png has transparency and thus an alpha channel, so make sure to tell OpenGL the data type is of GL_RGBA
       glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
       glGenerateMipmap(GL_TEXTURE_2D);
   }
   else
   {
       qDebug() << "Failed to load texture:" << texturePath;
   }
   stbi_image_free(data);

   mProgram->bind();
   glUniform1i(glGetUniformLocation(mProgram->programId(), "texture1"), 0);
   glUniform1i(glGetUniformLocation(mProgram->programId(), "texture2"), 1);
   mProgram->release();

   stbi_set_flip_vertically_on_load(false);
}

Course_1_5_1_transformations::~Course_1_5_1_transformations()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteTextures(1, &texture1);
    glDeleteTextures(1, &texture2);
    mProgram->release();
    delete mProgram;
}

void Course_1_5_1_transformations::render()
{
    Course::render();

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // bind textures on corresponding texture units
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture1);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texture2);

    // get matrix's uniform location and set matrix
    mProgram->bind();

    float angle = qRadiansToDegrees(mDuration);
    mTransform.setToIdentity();
    mTransform.translate(QVector3D(0.5f, -0.5f, 0.0f));
    mTransform.rotate(angle, QVector3D(0.0f, 0.0f, 1.0f));

    unsigned int transformLoc = glGetUniformLocation(mProgram->programId(), "transform");
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, mTransform.data());

    // render container
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
    mProgram->release();
}

QList<QtProperty *> Course_1_5_1_transformations::getPropertyList(QtVariantPropertyManager *manager)
{
    GETPROPERTYLIST(Course_1_5_1_transformations)
}
