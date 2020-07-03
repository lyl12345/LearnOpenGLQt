#include "course_1_3_1_shaders_uniform.h"
#include <qmath.h>

Course_1_3_1_shaders_uniform::Course_1_3_1_shaders_uniform()
    :Course()
{
    initializeOpenGLFunctions();

    const char *vertexShaderSource ="#version 330 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "void main()\n"
        "{\n"
        "   gl_Position = vec4(aPos, 1.0);\n"
        "}\0";

    const char *fragmentShaderSource = "#version 330 core\n"
        "out vec4 FragColor;\n"
        "uniform vec4 ourColor;\n"
        "void main()\n"
        "{\n"
        "   FragColor = ourColor;\n"
        "}\n\0";

    mProgram = new QOpenGLShaderProgram();
    mProgram->addShaderFromSourceCode(QOpenGLShader::Vertex, vertexShaderSource);
    mProgram->addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentShaderSource);
    mProgram->link();

    float vertices[] = {
         0.5f, -0.5f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f,  // bottom left
         0.0f,  0.5f, 0.0f   // top
    };

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
}

Course_1_3_1_shaders_uniform::~Course_1_3_1_shaders_uniform()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    mProgram->release();
    delete mProgram;
}

void Course_1_3_1_shaders_uniform::render()
{
    Course::render();

    float greenValue = sin(mDuration) / 2.0f + 0.5f;

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    mProgram->bind();
    glBindVertexArray(VAO);
    int vertexColorLocation = glGetUniformLocation(mProgram->programId(), "ourColor");
    glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

QList<QtProperty *> Course_1_3_1_shaders_uniform::getPropertyList(QtVariantPropertyManager *manager)
{
    GETPROPERTYLIST(Course_1_3_1_shaders_uniform)
}
