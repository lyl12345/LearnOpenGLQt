#ifndef MYDOCKWIDGET_H
#define MYDOCKWIDGET_H

#include <QDockWidget>

class MyDockWidget : public QDockWidget
{
    Q_OBJECT
public:
    MyDockWidget(QWidget *parent = nullptr);
    QSize sizeHint() const;
};

#endif // MYDOCKWIDGET_H
