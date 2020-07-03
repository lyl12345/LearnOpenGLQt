#include "course_1_2_5_hello_triangle_exercise3.h"

Course_1_2_5_hello_triangle_exercise3::Course_1_2_5_hello_triangle_exercise3()
{
    initializeOpenGLFunctions();

    const char *vertexShaderSource = "#version 330 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "void main()\n"
        "{\n"
        "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
        "}\0";
    const char *fragmentShader1Source = "#version 330 core\n"
        "out vec4 FragColor;\n"
        "void main()\n"
        "{\n"
        "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
        "}\n\0";
    const char *fragmentShader2Source = "#version 330 core\n"
        "out vec4 FragColor;\n"
        "void main()\n"
        "{\n"
        "   FragColor = vec4(1.0f, 1.0f, 0.0f, 1.0f);\n"
        "}\n\0";

    mProgramOrange = new QOpenGLShaderProgram();
    mProgramOrange->addShaderFromSourceCode(QOpenGLShader::Vertex, vertexShaderSource);
    mProgramOrange->addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentShader1Source);
    mProgramOrange->link();

    mProgramYellow = new QOpenGLShaderProgram();
    mProgramYellow->addShaderFromSourceCode(QOpenGLShader::Vertex, vertexShaderSource);
    mProgramYellow->addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentShader2Source);
    mProgramYellow->link();

    float firstTriangle[] = {
        -0.9f, -0.5f, 0.0f,  // left
        -0.0f, -0.5f, 0.0f,  // right
        -0.45f, 0.5f, 0.0f,  // top
    };
    float secondTriangle[] = {
        0.0f, -0.5f, 0.0f,  // left
        0.9f, -0.5f, 0.0f,  // right
        0.45f, 0.5f, 0.0f   // top
    };

    glGenVertexArrays(2, VAOs); // we can also generate multiple VAOs or buffers at the same time
    glGenBuffers(2, VBOs);
    // first triangle setup
    // --------------------
    glBindVertexArray(VAOs[0]);
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(firstTriangle), firstTriangle, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);	// Vertex attributes stay the same
    glEnableVertexAttribArray(0);
    // glBindVertexArray(0); // no need to unbind at all as we directly bind a different VAO the next few lines
    // second triangle setup
    // ---------------------
    glBindVertexArray(VAOs[1]);	// note that we bind to a different VAO now
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);	// and a different VBO
    glBufferData(GL_ARRAY_BUFFER, sizeof(secondTriangle), secondTriangle, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0); // because the vertex data is tightly packed we can also specify 0 as the vertex attribute's stride to let OpenGL figure it out
    glEnableVertexAttribArray(0);
    // glBindVertexArray(0); // not really necessary as well, but beware of calls that could affect VAOs while this one is bound (like binding element buffer objects, or enabling/disabling vertex attributes)
}

Course_1_2_5_hello_triangle_exercise3::~Course_1_2_5_hello_triangle_exercise3()
{
    glDeleteVertexArrays(2, VAOs);
    glDeleteBuffers(2, VBOs);
    mProgramOrange->release();
    delete mProgramOrange;
    mProgramYellow->release();
    delete mProgramYellow;
}

void Course_1_2_5_hello_triangle_exercise3::render()
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // now when we draw the triangle we first use the vertex and orange fragment shader from the first program
    mProgramOrange->bind();
    // draw the first triangle using the data from our first VAO
    glBindVertexArray(VAOs[0]);
    glDrawArrays(GL_TRIANGLES, 0, 3);	// this call should output an orange triangle
    // then we draw the second triangle using the data from the second VAO
    // when we draw the second triangle we want to use a different shader program so we switch to the shader program with our yellow fragment shader.
    mProgramYellow->bind();
    glBindVertexArray(VAOs[1]);
    glDrawArrays(GL_TRIANGLES, 0, 3);	// this call should output a yellow triangle
    glBindVertexArray(0);
    mProgramOrange->release();
    mProgramYellow->release();
}

QList<QtProperty *> Course_1_2_5_hello_triangle_exercise3::getPropertyList(QtVariantPropertyManager *manager)
{
    GETPROPERTYLIST(Course_1_2_5_hello_triangle_exercise3)
}
