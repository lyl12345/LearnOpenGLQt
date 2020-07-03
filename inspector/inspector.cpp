#include "inspector.h"
#include <QHBoxLayout>

Inspector::Inspector(QWidget *parent)
    :QWidget(parent)
{
    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->setMargin(0);
    layout->setSpacing(0);

    mVariantManager = new QtVariantPropertyManager(this);
    mVariantFactory = new QtVariantEditorFactory(this);
    mVariantBrowser = new QtButtonPropertyBrowser(this);
    layout->addWidget(mVariantBrowser);

    connect(mVariantManager, SIGNAL(valueChanged(QtProperty *, const QVariant &)), this, SLOT(writeProperty(QtProperty *, const QVariant &)));
    mVariantBrowser->setFactoryForManager(mVariantManager, mVariantFactory);
}

void Inspector::setProxy(InspectorProxy *proxy)
{
    if (proxy == mProxy){
        return;
    }

    mProxy = proxy;
    mVariantBrowser->clear();
    mVariantManager->clear();

    if (mProxy == nullptr){
        return;
    }

    canWrite = false;
    QList<QtProperty*> properties = mProxy->getPropertyList(mVariantManager);
    for (int i=0; i<properties.count(); i++){
        QtProperty *property = properties.at(i);
        QtBrowserItem *item = mVariantBrowser->addProperty(property);
        mVariantBrowser->setExpanded(item,true);
    }
    canWrite = true;
}

void Inspector::updateProperty(const QString &propertyId, const QVariant &val)
{
    QSet<QtProperty *> properties = mVariantManager->properties();

    QSetIterator<QtProperty *> i(properties);
    while (i.hasNext()){
        QtProperty *property = i.next();
        if (property->propertyId() == propertyId){
            mVariantManager->setValue(property, val);
            return;
        }
    }
}

void Inspector::writeProperty(QtProperty *property, const QVariant &value)
{
    if (!canWrite || mProxy == nullptr){
        return;
    }
    mProxy->setProperty(property->propertyId(), value);
}
