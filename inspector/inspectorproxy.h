#ifndef PROXY_H
#define PROXY_H

#include <QObject>
#include "property/qtpropertybrowser.h"
#include "property/qtvariantproperty.h"

#define GETPROPERTYLIST(classname)                                                       \
QList<QtProperty *> properties;                                                          \
QtVariantProperty *root = manager->addProperty(manager->groupTypeId(), tr(#classname));  \
properties.push_back(root);                                                              \
QList<QtProperty *> inheritedProperties = Course::getPropertyList(manager);              \
for (int i=0; i<inheritedProperties.count(); i++){                                       \
    properties.push_back(inheritedProperties.at(i));                                     \
}                                                                                        \
return properties;


class InspectorProxy : public QObject
{
    Q_OBJECT
public:
    InspectorProxy(QObject *parent = nullptr);
    virtual ~InspectorProxy();
    virtual QList<QtProperty*> getPropertyList(QtVariantPropertyManager *manager);
    virtual bool setProperty(const QString &propertyId, const QVariant &value);

signals:
    void propertyChanged(const QString &propertyId, const QVariant &value);
};

#endif // PROXY_H
