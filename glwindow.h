#ifndef GLWINDOW_H
#define GLWINDOW_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLExtraFunctions>
#include <QTimer>
#include <QEvent>

class Course;
class MainWindow;

class GlWindow : public QOpenGLWidget,
        protected QOpenGLExtraFunctions
{
    Q_OBJECT
public:
    GlWindow(MainWindow *mainWindow, QWidget *parent = nullptr);
    ~GlWindow();

    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;
protected:
    bool event(QEvent *event) override;

private slots:
    void renderCourse(const QString &name);
    void updateInspectorProperty(const QString &propertyId, const QVariant &value);
    void renderFrame();
private:
    Course *mCourse;
    MainWindow *mMainWindow;
    QTimer mTimer;
};

#endif // GLWINDOW_H
