#include "course_1_1_2_hello_window_clear.h"

Course_1_1_2_hello_window_clear::Course_1_1_2_hello_window_clear()
{
   initializeOpenGLFunctions();
}

void Course_1_1_2_hello_window_clear::render()
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

QList<QtProperty *> Course_1_1_2_hello_window_clear::getPropertyList(QtVariantPropertyManager *manager)
{
    GETPROPERTYLIST(Course_1_1_2_hello_window_clear)
}
