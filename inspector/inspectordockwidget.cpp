#include "inspectordockwidget.h"
#include <QScrollArea>
#include <QLabel>

InspectorDockWidget::InspectorDockWidget(QWidget *parent)
    :QDockWidget(parent)
{
    setWindowTitle(tr("Inspector"));
    setFeatures(QDockWidget::NoDockWidgetFeatures);
    setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);

    mInspector = new Inspector(this);

    QScrollArea *scroll = new QScrollArea(this);
    setWidget(scroll);
    scroll->setWidgetResizable(true);
    scroll->setWidget(mInspector);
}

InspectorDockWidget::~InspectorDockWidget()
{
}

QSize InspectorDockWidget::sizeHint() const
{
    return QSize(32,200);
}

Inspector *InspectorDockWidget::getInspector()
{
    return mInspector;
}

