#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "glwindow.h"
#include <QAction>
#include <QDockWidget>
#include "inspector/inspector.h"
#include "inspector/inspectordockwidget.h"
#include "inspector/inspectorproxyexample.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:  
    void courseTriggered(const QString &name);

public:
    void setInspectorProxy(InspectorProxy *proxy);
    void setInspectorProperty(const QString &propertyId, const QVariant &value);

private slots:
    void actionTriggered_inspect_example2();
    void actionTriggered_uninspect_example2();
    void actionTriggered_showMatrix();

private:
    Ui::MainWindow *ui;
    GlWindow *glWindow;

    QDockWidget *treeWidget;
    InspectorDockWidget *inspectorWidget;

    ProxyExample1 *example1;
    ProxyExample2 *example2;
};
#endif // MAINWINDOW_H
