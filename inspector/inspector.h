#ifndef INSPECTOR_H
#define INSPECTOR_H

#include <QWidget>
#include "property/qtvariantproperty.h"
#include "property/qtbuttonpropertybrowser.h"
#include "inspectorproxy.h"

class QtProperty;

class Inspector : public QWidget
{
    Q_OBJECT
public:
    Inspector(QWidget *parent = nullptr);

    void setProxy(InspectorProxy* proxy);
    void updateProperty(const QString &propertyId, const QVariant &val);
private slots:
    void writeProperty(QtProperty *property, const QVariant &value);
private:
    QtVariantPropertyManager *mVariantManager;
    QtVariantEditorFactory *mVariantFactory;
    QtButtonPropertyBrowser *mVariantBrowser;

    InspectorProxy *mProxy;
    bool canWrite;
};

#endif // INSPECTOR_H
