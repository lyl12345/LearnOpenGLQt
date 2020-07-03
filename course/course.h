#ifndef COURSE_H
#define COURSE_H

#include "inspector/inspectorproxy.h"

class GlWindow;
class QFocusEvent;

class Course : public InspectorProxy
{
    Q_OBJECT
public:
    Course(QObject *parent = nullptr);
    virtual ~Course();

    virtual void init(GlWindow *glWindow = nullptr);
    virtual void render();
protected:
    void setGlWindow(GlWindow *glWindow);
    QSize contextSize();
    float contextRatio();
protected:
    virtual void enter(QEvent *event);
    virtual void leave(QEvent *event);
    virtual void Resize(QResizeEvent *event);
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void wheelEvent(QWheelEvent*event);
    virtual void keyPressEvent(QKeyEvent *event);
    virtual void keyReleaseEvent(QKeyEvent *event);

    bool eventFilter(QObject *object, QEvent *event) override;

signals:
    void update();

protected:
    qint64 mFirstFrame, mLastFrame;
    float mDelta;                   //time since last frame
    double mDuration;               //time since first frame
    GlWindow *mGlWindow;
};

#endif // COURSE_H
