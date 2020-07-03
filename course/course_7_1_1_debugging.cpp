#include "course_7_1_1_debugging.h"
#include <QDir>
#include <QDebug>
#include "stb_image.h"
#include <QOpenGLDebugLogger>

void _stdcall glDebugOutput(GLenum source, GLenum type, unsigned int id, GLenum severity, GLsizei length, const char *message, const void *userParam)
{
    if(id == 131169 || id == 131185 || id == 131218 || id == 131204) return; // ignore these non-significant error codes

    qDebug() << "---------------\n";
    qDebug() << "Debug message (" << id << "): " <<  message;

    switch (source)
    {
    case GL_DEBUG_SOURCE_API:             qDebug() << "Source: API"; break;
    case GL_DEBUG_SOURCE_WINDOW_SYSTEM:   qDebug() << "Source: Window System"; break;
    case GL_DEBUG_SOURCE_SHADER_COMPILER: qDebug() << "Source: Shader Compiler"; break;
    case GL_DEBUG_SOURCE_THIRD_PARTY:     qDebug() << "Source: Third Party"; break;
    case GL_DEBUG_SOURCE_APPLICATION:     qDebug() << "Source: Application"; break;
    case GL_DEBUG_SOURCE_OTHER:           qDebug() << "Source: Other"; break;
    } qDebug() << "\n";

    switch (type)
    {
    case GL_DEBUG_TYPE_ERROR:               qDebug() << "Type: Error"; break;
    case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: qDebug() << "Type: Deprecated Behaviour"; break;
    case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:  qDebug() << "Type: Undefined Behaviour"; break;
    case GL_DEBUG_TYPE_PORTABILITY:         qDebug() << "Type: Portability"; break;
    case GL_DEBUG_TYPE_PERFORMANCE:         qDebug() << "Type: Performance"; break;
    case GL_DEBUG_TYPE_MARKER:              qDebug() << "Type: Marker"; break;
    case GL_DEBUG_TYPE_PUSH_GROUP:          qDebug() << "Type: Push Group"; break;
    case GL_DEBUG_TYPE_POP_GROUP:           qDebug() << "Type: Pop Group"; break;
    case GL_DEBUG_TYPE_OTHER:               qDebug() << "Type: Other"; break;
    } qDebug() << "\n";

    switch (severity)
    {
    case GL_DEBUG_SEVERITY_HIGH:         qDebug() << "Severity: high"; break;
    case GL_DEBUG_SEVERITY_MEDIUM:       qDebug() << "Severity: medium"; break;
    case GL_DEBUG_SEVERITY_LOW:          qDebug() << "Severity: low"; break;
    case GL_DEBUG_SEVERITY_NOTIFICATION: qDebug() << "Severity: notification"; break;
    } qDebug() << "\n";
    qDebug() << "\n";
}

Course_7_1_1_debugging::Course_7_1_1_debugging()
    :CourseWithCamera()
{
    initializeOpenGLFunctions();
}

Course_7_1_1_debugging::~Course_7_1_1_debugging()
{
    glDisable(GL_CULL_FACE);
    glDisable(GL_DEBUG_OUTPUT);
    glDisable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
}

void Course_7_1_1_debugging::init(GlWindow *glWindow)
{
    setGlWindow(glWindow);

//    QOpenGLContext *ctx = QOpenGLContext::currentContext();
//    QOpenGLDebugLogger *logger = new QOpenGLDebugLogger(this);
//    logger->initialize();
//    connect(logger, &QOpenGLDebugLogger::messageLogged, this, &Course_7_1_1_debugging::handleLoggedMessage);
//    logger->startLogging();

    // enable OpenGL debug context if context allows for debug context
    int flags;
    glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
    if (flags & GL_CONTEXT_FLAG_DEBUG_BIT)
    {
        glEnable(GL_DEBUG_OUTPUT);
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS); // makes sure errors are displayed synchronously
        glDebugMessageCallback(glDebugOutput, nullptr);
        glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
    }

    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    QString shaderPath = QDir::currentPath() + "/shaders/6.pbr/1.debugging/";
    shader.addShaderFromSourceFile(QOpenGLShader::Vertex,shaderPath+"debugging.vs");
    shader.addShaderFromSourceFile(QOpenGLShader::Fragment,shaderPath+"debugging.fs");
    shader.link();

    float vertices[] = {
        // back face
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, // bottom-left
        0.5f,  0.5f, -0.5f,  1.0f,  1.0f, // top-right
        0.5f, -0.5f, -0.5f,  1.0f,  0.0f, // bottom-right
        0.5f,  0.5f, -0.5f,  1.0f,  1.0f, // top-right
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, // bottom-left
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f, // top-left
        // front face
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, // bottom-left
        0.5f, -0.5f,  0.5f,  1.0f,  0.0f, // bottom-right
        0.5f,  0.5f,  0.5f,  1.0f,  1.0f, // top-right
        0.5f,  0.5f,  0.5f,  1.0f,  1.0f, // top-right
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f, // top-left
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, // bottom-left
        // left face
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f, // top-right
        -0.5f,  0.5f, -0.5f, -1.0f,  1.0f, // top-left
        -0.5f, -0.5f, -0.5f, -0.0f,  1.0f, // bottom-left
        -0.5f, -0.5f, -0.5f, -0.0f,  1.0f, // bottom-left
        -0.5f, -0.5f,  0.5f, -0.0f,  0.0f, // bottom-right
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f, // top-right
        // right face
        0.5f,  0.5f,  0.5f,  1.0f,  0.0f, // top-left
        0.5f, -0.5f, -0.5f,  0.0f,  1.0f, // bottom-right
        0.5f,  0.5f, -0.5f,  1.0f,  1.0f, // top-right
        0.5f, -0.5f, -0.5f,  0.0f,  1.0f, // bottom-right
        0.5f,  0.5f,  0.5f,  1.0f,  0.0f, // top-left
        0.5f, -0.5f,  0.5f,  0.0f,  0.0f, // bottom-left
        // bottom face
        -0.5f, -0.5f, -0.5f,  0.0f,  1.0f, // top-right
        0.5f, -0.5f, -0.5f,  1.0f,  1.0f, // top-left
        0.5f, -0.5f,  0.5f,  1.0f,  0.0f, // bottom-left
        0.5f, -0.5f,  0.5f,  1.0f,  0.0f, // bottom-left
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, // bottom-right
        -0.5f, -0.5f, -0.5f,  0.0f,  1.0f, // top-right
        // top face
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f, // top-left
        0.5f,  0.5f,  0.5f,  1.0f,  0.0f, // bottom-right
        0.5f,  0.5f, -0.5f,  1.0f,  1.0f, // top-right
        0.5f,  0.5f,  0.5f,  1.0f,  0.0f, // bottom-right
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f, // top-left
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f  // bottom-left
    };

    glGenVertexArrays(1, &cubeVAO);
    glGenBuffers(1, &cubeVBO);
    // fill buffer
    glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // link vertex attributes
    glBindVertexArray(cubeVAO);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    int width, height, nrComponents;
    QString path = QDir::currentPath() + "/resources/textures/wood.png";
    unsigned char *data = stbi_load(path.toStdString().c_str(), &width, &height, &nrComponents, 0);
    if (data)
    {
        glTexImage2D(GL_FRAMEBUFFER, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }
    else
    {
        qDebug() << "Failed to load texture";
    }
    stbi_image_free(data);

    // set up projection matrix
    QMatrix4x4 projection;
    projection.perspective(45.0f, 800/600,  0.1f, 10.0f);
    glUniformMatrix4fv(glGetUniformLocation(shader.programId(), "projection"), 1, GL_FALSE, projection.data());
    glUniform1i(glGetUniformLocation(shader.programId(), "tex"), 0);
}

void Course_7_1_1_debugging::render()
{
    Course::render();

    processInput();

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    shader.bind();
    float rotationSpeed = 10.0f;
    float angle = (float)mDuration* rotationSpeed;
    QMatrix4x4 model;
    model.translate(QVector3D(0.0, 0.0f, -2.5));
    model.rotate(angle, QVector3D(1.0f, 1.0f, 1.0f));
    glUniformMatrix4fv(glGetUniformLocation(shader.programId(), "model"), 1, GL_FALSE, model.data());

    glBindTexture(GL_TEXTURE_2D, texture);
    glBindVertexArray(cubeVAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
}

QList<QtProperty *> Course_7_1_1_debugging::getPropertyList(QtVariantPropertyManager *manager)
{
    GETPROPERTYLIST(Course_7_1_1_debugging)
}

void Course_7_1_1_debugging::handleLoggedMessage(const QOpenGLDebugMessage &debugMessage)
{
    qDebug() << debugMessage;
}
