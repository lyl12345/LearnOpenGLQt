#include "mydockwidget.h"

MyDockWidget::MyDockWidget(QWidget *parent)
    :QDockWidget(parent)
{
}

QSize MyDockWidget::sizeHint() const
{
    return QSize(32,200);
}

