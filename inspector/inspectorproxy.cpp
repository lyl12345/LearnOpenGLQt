#include "inspectorproxy.h"
#include <QVariant>

InspectorProxy::InspectorProxy(QObject *parent)
    :QObject(parent)
{
}

InspectorProxy::~InspectorProxy()
{
}

QList<QtProperty *> InspectorProxy::getPropertyList(QtVariantPropertyManager *manager)
{
    Q_UNUSED(manager);
    QList<QtProperty *> properties;
    return properties;
}

bool InspectorProxy::setProperty(const QString &propertyId, const QVariant &value)
{
    Q_UNUSED(propertyId);
    Q_UNUSED(value);
    return false;
}
