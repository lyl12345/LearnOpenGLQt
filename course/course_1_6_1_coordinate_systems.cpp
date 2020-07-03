#include "course_1_6_1_coordinate_systems.h"
#include <QDir>
#include <QDebug>
#include "stb_image.h"

Course_1_6_1_coordinate_systems::Course_1_6_1_coordinate_systems()
{
    initializeOpenGLFunctions();

    QString shaderPath = QDir::currentPath() + "/shaders/1.getting_started/6.1.coordinate_systems/";
    mProgram = new QOpenGLShaderProgram();
    mProgram->addShaderFromSourceFile(QOpenGLShader::Vertex,shaderPath+"6.1.coordinate_systems.vs");
    mProgram->addShaderFromSourceFile(QOpenGLShader::Fragment,shaderPath+"6.1.coordinate_systems.fs");
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

Course_1_6_1_coordinate_systems::~Course_1_6_1_coordinate_systems()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    mProgram->release();
    delete mProgram;
}

void Course_1_6_1_coordinate_systems::render()
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // bind textures on corresponding texture units
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture1);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texture2);

    // activate shader
    mProgram->bind();

    // create transformations
    unsigned int modelLoc = glGetUniformLocation(mProgram->programId(), "model");
    unsigned int viewLoc  = glGetUniformLocation(mProgram->programId(), "view");
    unsigned int projectionLoc  = glGetUniformLocation(mProgram->programId(), "projection");
    // pass them to the shaders (3 different ways)
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, mModel.data());
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, mView.data());
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, mProjection.data());

    // render container
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
    mProgram->release();
}

QList<QtProperty *> Course_1_6_1_coordinate_systems::getPropertyList(QtVariantPropertyManager *manager)
{
    QList<QtProperty *> properties;
    QtVariantProperty *root = manager->addProperty(manager->groupTypeId(), tr("Course_1_6_1_coordinate_systems"));
    properties.push_back(root);

    QtVariantProperty *property;

    property = manager->addProperty(QVariant::Matrix4x4, tr("model"));
    property->setPropertyId("model");
    property->setAttribute("decimals", 5);
    property->setValue(mModel);
    root->addSubProperty(property);

    property = manager->addProperty(QVariant::Matrix4x4, tr("view"));
    property->setPropertyId("view");
    property->setAttribute("decimals", 5);
    property->setValue(mView);
    root->addSubProperty(property);

    property = manager->addProperty(QVariant::Matrix4x4, tr("projection"));
    property->setPropertyId("projection");
    property->setAttribute("decimals", 5);
    property->setValue(mProjection);
    root->addSubProperty(property);

    QList<QtProperty *> inheritedProperties = Course::getPropertyList(manager);
    for (int i=0; i<inheritedProperties.count(); i++){
        properties.push_back(inheritedProperties.at(i));
    }

    return properties;
}

bool Course_1_6_1_coordinate_systems::setProperty(const QString &propertyId, const QVariant &value)
{
    if(Course::setProperty(propertyId, value)){
        return true;
    }

    bool ret = true;

    if (propertyId == "model"){
        mModel = value.value<QMatrix4x4>();
    }else if (propertyId == "view"){
        mView = value.value<QMatrix4x4>();
    }else if (propertyId == "projection"){
        mProjection = value.value<QMatrix4x4>();
    }else{
        ret = false;
    }

    emit update();

    return ret;
}


