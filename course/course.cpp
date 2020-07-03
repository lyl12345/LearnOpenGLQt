#include "course.h"
#include <QDateTime>
#include <QFocusEvent>
#include "glwindow.h"

Course::Course(QObject *parent)
    :InspectorProxy(parent)
    ,mLastFrame(0)
    ,mDelta(0)
    ,mDuration(0)
    ,mGlWindow(nullptr)
{
    mFirstFrame = QDateTime::currentDateTime().toMSecsSinceEpoch();
}

Course::~Course()
{
    setGlWindow(nullptr);
}

void Course::init(GlWindow *glWindow)
{
    setGlWindow(glWindow);
}

void Course::render()
{
    qint64 currentFrame = QDateTime::currentDateTime().toMSecsSinceEpoch();
    mDelta = (currentFrame - mLastFrame) * 0.001; //msec to sec
    mDuration = (currentFrame - mFirstFrame) * 0.001; //msec to sec
    mLastFrame = currentFrame;
}

void Course::setGlWindow(GlWindow *glWindow)
{
    if (glWindow == mGlWindow){
        return;
    }
    if (mGlWindow){
        mGlWindow->removeEventFilter(this);
    }
    mGlWindow = glWindow;
    if (!glWindow){
        return;
    }

    mGlWindow->installEventFilter(this);
}

QSize Course::contextSize()
{
    if (mGlWindow){
        return mGlWindow->size();
    }else
    {
        return QSize();
    }
}

float Course::contextRatio()
{
    if (mGlWindow){
        QSize size = mGlWindow->size();
        if (size.height()<=0){
            return 0;
        }
        return size.width()/size.height();
    }{
        return 0;
    }
}

void Course::enter(QEvent *event)
{
    Q_UNUSED(event)
}

void Course::leave(QEvent *event)
{
    Q_UNUSED(event)
}

void Course::Resize(QResizeEvent *event)
{
    Q_UNUSED(event)
}

void Course::mousePressEvent(QMouseEvent *event)
{
    Q_UNUSED(event)
}

void Course::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event)
}

void Course::mouseMoveEvent(QMouseEvent *event)
{
    Q_UNUSED(event)
}

void Course::wheelEvent(QWheelEvent *event)
{
    Q_UNUSED(event)
}

void Course::keyPressEvent(QKeyEvent *event)
{
    Q_UNUSED(event)
}

void Course::keyReleaseEvent(QKeyEvent *event)
{
    Q_UNUSED(event)
}

bool Course::eventFilter(QObject *object, QEvent *event)
{
    if (object == mGlWindow) {
        if (event->type() == QEvent::Enter){
            enter(event);
        }else if(event->type() == QEvent::Leave){
            leave(event);
        }else if(event->type() == QEvent::Resize){
            Resize(dynamic_cast<QResizeEvent*>(event));
        }else if(event->type() == QEvent::MouseButtonPress){
            mousePressEvent(dynamic_cast<QMouseEvent*>(event));
        }else if(event->type() == QEvent::MouseButtonRelease){
            mouseReleaseEvent(dynamic_cast<QMouseEvent*>(event));
        }else if(event->type() == QEvent::MouseMove){
            mouseMoveEvent(dynamic_cast<QMouseEvent*>(event));
        }else if(event->type() == QEvent::Wheel){
            wheelEvent(dynamic_cast<QWheelEvent*>(event));
        }else if(event->type() == QEvent::KeyPress){
            keyPressEvent(dynamic_cast<QKeyEvent*>(event));
        }else if(event->type() == QEvent::KeyRelease){
            keyReleaseEvent(dynamic_cast<QKeyEvent*>(event));
        }
    }

    return false;
}


