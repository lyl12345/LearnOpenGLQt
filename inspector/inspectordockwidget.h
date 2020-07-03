#ifndef INSPECTORDOCKWIDGET_H
#define INSPECTORDOCKWIDGET_H

#include <QDockWidget>
#include "inspector.h"

class InspectorDockWidget : public QDockWidget
{
    Q_OBJECT
public:
    InspectorDockWidget(QWidget *parent = nullptr);
    virtual ~InspectorDockWidget();

    QSize sizeHint() const;

    Inspector* getInspector();
private:
    Inspector *mInspector;
};

#endif // INSPECTORDOCKWIDGET_H
