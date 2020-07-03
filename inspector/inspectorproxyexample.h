#ifndef INSPECTORPROXYEXAMPLE_H
#define INSPECTORPROXYEXAMPLE_H

#include "inspectorproxy.h"
#include <QDate>
#include <QTime>
#include <QDateTime>
#include <QChar>
#include <QKeySequence>
#include <QLocale>
#include <QVector2D>
#include <QVector3D>
#include <QVector4D>
#include <QMatrix4x4>

class ProxyExample1 : public InspectorProxy
{
    Q_OBJECT
public:
    ProxyExample1(QObject *parent = nullptr);
    virtual ~ProxyExample1();
    virtual QList<QtProperty*> getPropertyList(QtVariantPropertyManager *manager);
    virtual bool setProperty(const QString &propertyId, const QVariant &value);
private:
    bool visible;
    double height;
};

class ProxyExample2 : public ProxyExample1
{
    Q_OBJECT
    enum Direction{
        UP,
        RIGHT,
        DOWN,
        LEFT
    };

public:
    ProxyExample2(QObject *parent = nullptr);
    virtual ~ProxyExample2();
    virtual QList<QtProperty*> getPropertyList(QtVariantPropertyManager *manager);
    virtual bool setProperty(const QString &propertyId, const QVariant &value);
private:
    int ivalue;
    double dvalue;
    bool bvalue;
    QString string;
    QDate date;
    QTime time;
    QDateTime datetime;
    QKeySequence keySequence;
    QChar c;
    QLocale local;
    QPoint point;
    QPointF pointf;
    QSize size;
    QSizeF sizef;
    QRect rect;
    QRectF rectf;
    QColor color;
    Direction direction;    //enum
    QSizePolicy sizePolicy;
    QFont font;
    QCursor cursor;
    QVector2D vector2d;
    QVector3D vector3d;
    QVector4D vector4d;
    QMatrix4x4 matrix44;
};
#endif // INSPECTORPROXYEXAMPLE_H
