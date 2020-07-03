#include "course_1_4_5_textures_exercise4.h"
#include <QDir>
#include <QDebug>
#include "stb_image.h"

Course_1_4_5_textures_exercise4::Course_1_4_5_textures_exercise4()
    :mMixValue(0.2f)
{
    initializeOpenGLFunctions();

    QString shaderPath = QDir::currentPath() + "/shaders/1.getting_started/4.5.textures_exercise4/";
    mProgram = new QOpenGLShaderProgram();
    mProgram->addShaderFromSourceFile(QOpenGLShader::Vertex,shaderPath+"4.5.texture.vs");
    mProgram->addShaderFromSourceFile(QOpenGLShader::Fragment,shaderPath+"4.5.texture.fs");
    mProgram->link();

    float vertices[] = {
        // positions          // colors           // texture coords
         0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
         0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left
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
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // texture coord attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    // texture 1
    // ---------
    glGenTextures(1, &texture1);
    glBindTexture(GL_TEXTURE_2D, texture1);
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
    // The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
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
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
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

Course_1_4_5_textures_exercise4::~Course_1_4_5_textures_exercise4()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteTextures(1, &texture1);
    glDeleteTextures(1, &texture2);
    mProgram->release();
    delete mProgram;
}

void Course_1_4_5_textures_exercise4::render()
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // bind textures on corresponding texture units
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture1);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texture2);

    // render container
    mProgram->bind();
    // set the texture mix value in the shader
    glUniform1f(glGetUniformLocation(mProgram->programId(), "mixValue"), mMixValue);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
    mProgram->release();
}

QList<QtProperty *> Course_1_4_5_textures_exercise4::getPropertyList(QtVariantPropertyManager *manager)
{
    QList<QtProperty *> properties;
    QtVariantProperty *root = manager->addProperty(manager->groupTypeId(), tr("Course_1_4_5_textures_exercise4"));
    properties.push_back(root);

    QtVariantProperty *property;
    property = manager->addProperty(QVariant::Double, tr("MixValue"));
    property->setAttribute(QLatin1String("minimum"), 0);
    property->setAttribute(QLatin1String("maximum"), 1);
    property->setAttribute(QLatin1String("singleStep"),0.01);
    property->setPropertyId("MixValue");
    property->setValue(mMixValue);
    root->addSubProperty(property);

    QList<QtProperty *> inheritedProperties = Course::getPropertyList(manager);
    for (int i=0; i<inheritedProperties.count(); i++){
        properties.push_back(inheritedProperties.at(i));
    }

    return properties;
}

bool Course_1_4_5_textures_exercise4::setProperty(const QString &propertyId, const QVariant &value)
{
    if(Course::setProperty(propertyId, value)){
        return true;
    }

    bool ret = true;
    if (propertyId == "MixValue"){
        mMixValue = value.toDouble();
    }else{
        ret = false;
    }

    if (ret){
        emit update();
    }

    return ret;
}
