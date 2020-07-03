#include "course_1_1_1_hello_window.h"

Course_1_1_1_hello_window::Course_1_1_1_hello_window()
{
    initializeOpenGLFunctions();
}

void Course_1_1_1_hello_window::render()
{
    glClear(GL_COLOR_BUFFER_BIT);
}

QList<QtProperty *> Course_1_1_1_hello_window::getPropertyList(QtVariantPropertyManager *manager)
{
    GETPROPERTYLIST(Course_1_1_1_hello_window)
}


