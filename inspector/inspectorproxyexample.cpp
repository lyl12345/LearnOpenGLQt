#include "inspectorproxyexample.h"

ProxyExample1::ProxyExample1(QObject *parent)
    :InspectorProxy(parent)
    ,visible(true)
    ,height(199)
{
}

ProxyExample1::~ProxyExample1()
{
}

QList<QtProperty *> ProxyExample1::getPropertyList(QtVariantPropertyManager *manager)
{
    QList<QtProperty *> properties;
    QtVariantProperty *root = manager->addProperty(manager->groupTypeId(), tr("ProxyExample1"));
    properties.push_back(root);

    QtVariantProperty *property;
    property = manager->addProperty(QVariant::Bool, tr("visible"));
    property->setPropertyId("visible");
    property->setValue(visible);
    root->addSubProperty(property);

    property = manager->addProperty(QVariant::Double, tr("height"));
    property->setPropertyId("height");
    property->setAttribute(QLatin1String("minimum"), 0);
    property->setAttribute(QLatin1String("maximum"), 100);
    property->setValue(height);
    root->addSubProperty(property);

    QList<QtProperty *> inheritedProperties = InspectorProxy::getPropertyList(manager);
    for (int i=0; i<inheritedProperties.count(); i++){
        properties.push_back(inheritedProperties.at(i));
    }

    return properties;
}

bool ProxyExample1::setProperty(const QString &propertyId, const QVariant &value)
{
    if(InspectorProxy::setProperty(propertyId, value)){
        return true;
    }

    bool ret = true;
    if (propertyId=="visible"){
        visible = value.toBool();
    }else if(propertyId=="height"){
        height = value.toDouble();
    }else{
        ret = false;
    }

    return ret;
}

ProxyExample2::ProxyExample2(QObject *parent)
    :ProxyExample1(parent)
{
}

ProxyExample2::~ProxyExample2()
{
}

QList<QtProperty *> ProxyExample2::getPropertyList(QtVariantPropertyManager *manager)
{
    QList<QtProperty *> properties;
    QtVariantProperty *root = manager->addProperty(manager->groupTypeId(), tr("ProxyExample2"));
    properties.push_back(root);

    QtVariantProperty *property;
    property = manager->addProperty(QVariant::Int, tr("ivalue"));
    property->setPropertyId("ivalue");
    property->setAttribute("maximum",100);
    property->setAttribute("minimum",-100);
    property->setValue(ivalue);
    root->addSubProperty(property);

    property = manager->addProperty(QVariant::Double, tr("dvalue"));
    property->setPropertyId("dvalue");
    property->setValue(dvalue);
    root->addSubProperty(property);

    property = manager->addProperty(QVariant::Bool, tr("bvalue"));
    property->setPropertyId("bvalue");
    property->setValue(bvalue);
    root->addSubProperty(property);

    property = manager->addProperty(QVariant::String, tr("string"));
    property->setPropertyId("string");
    property->setValue(string);
    root->addSubProperty(property);

    property = manager->addProperty(QVariant::Date, tr("date"));
    property->setPropertyId("date");
    property->setValue(date);
    root->addSubProperty(property);

    property = manager->addProperty(QVariant::Time, tr("time"));
    property->setPropertyId("time");
    property->setValue(time);
    root->addSubProperty(property);

    property = manager->addProperty(QVariant::DateTime, tr("datetime"));
    property->setPropertyId("datetime");
    property->setValue(datetime);
    root->addSubProperty(property);

    property = manager->addProperty(QVariant::KeySequence, tr("keySequence"));
    property->setPropertyId("keySequence");
    property->setValue(keySequence);
    root->addSubProperty(property);

    property = manager->addProperty(QVariant::Char, tr("c"));
    property->setPropertyId("c");
    property->setValue(c);
    root->addSubProperty(property);

    property = manager->addProperty(QVariant::Locale, tr("local"));
    property->setPropertyId("local");
    property->setValue(local);
    root->addSubProperty(property);

    property = manager->addProperty(QVariant::Point, tr("point"));
    property->setPropertyId("point");
    property->setValue(point);
    root->addSubProperty(property);

    property = manager->addProperty(QVariant::PointF, tr("pointf"));
    property->setPropertyId("pointf");
    property->setValue(pointf);
    root->addSubProperty(property);

    property = manager->addProperty(QVariant::Size, tr("size"));
    property->setPropertyId("size");
    property->setValue(size);
    root->addSubProperty(property);

    property = manager->addProperty(QVariant::SizeF, tr("sizef"));
    property->setPropertyId("sizef");
    property->setValue(sizef);
    root->addSubProperty(property);

    property = manager->addProperty(QVariant::Rect, tr("rect"));
    property->setPropertyId("rect");
    property->setValue(rect);
    root->addSubProperty(property);

    property = manager->addProperty(QVariant::RectF, tr("rectf"));
    property->setPropertyId("rectf");
    property->setValue(rectf);
    root->addSubProperty(property);

    property = manager->addProperty(QVariant::Color, tr("color"));
    property->setPropertyId("color");
    property->setValue(color);
    root->addSubProperty(property);

    property = manager->addProperty(manager->enumTypeId(), tr("direction"));
    property->setPropertyId("direction");
    QStringList enumNames;
    enumNames << "Up" << "Right" << "Down" << "Left";
    property->setAttribute("enumNames",enumNames);
    QMap<int, QIcon> enumIcons;
    enumIcons[0] = QIcon(":/images/up.png");
    enumIcons[1] = QIcon(":/images/right.png");
    enumIcons[2] = QIcon(":/images/down.png");
    enumIcons[3] = QIcon(":/images/left.png");
    property->setAttribute("enumIcons",QVariant::fromValue(enumIcons));
    property->setValue((int)direction);
    root->addSubProperty(property);

    property = manager->addProperty(QVariant::SizePolicy, tr("sizePolicy"));
    property->setPropertyId("sizePolicy");
    property->setValue(sizePolicy);
    root->addSubProperty(property);

    property = manager->addProperty(QVariant::Font, tr("font"));
    property->setPropertyId("font");
    property->setValue(font);
    root->addSubProperty(property);

    property = manager->addProperty(QVariant::Cursor, tr("cursor"));
    property->setPropertyId("cursor");
    property->setValue(cursor);
    root->addSubProperty(property);

    property = manager->addProperty(QVariant::Vector2D, tr("vector2d"));
    property->setPropertyId("vector2d");
    property->setAttribute("decimals", 2);
    property->setValue(vector2d);
    root->addSubProperty(property);

    property = manager->addProperty(QVariant::Vector3D, tr("vector3d"));
    property->setPropertyId("vector3d");
    property->setAttribute("decimals", 3);
    property->setValue(vector3d);
    root->addSubProperty(property);

    property = manager->addProperty(QVariant::Vector4D, tr("vector4d"));
    property->setPropertyId("vector4d");
    property->setAttribute("decimals", 4);
    property->setValue(vector4d);
    root->addSubProperty(property);

    QtVariantProperty *matrixRoot;
    matrixRoot = manager->addProperty(manager->groupTypeId(), tr("matrix44"));
    root->addSubProperty(matrixRoot);

    property = manager->addProperty(QVariant::Matrix4x4, tr(""));
    property->setPropertyId("matrix44");
    property->setAttribute("decimals", 5);
    property->setValue(matrix44);
    matrixRoot->addSubProperty(property);

    QList<QtProperty *> inheritedProperties = ProxyExample1::getPropertyList(manager);
    for (int i=0; i<inheritedProperties.count(); i++){
        properties.push_back(inheritedProperties.at(i));
    }

    return properties;
}

bool ProxyExample2::setProperty(const QString &propertyId, const QVariant &value)
{
    if(ProxyExample1::setProperty(propertyId, value)){
        return true;
    }

    bool ret = true;

    if (propertyId == "ivalue"){
        ivalue = value.toInt();
    }else if (propertyId == "dvalue"){
        dvalue = value.toDouble();
    }else if (propertyId == "bvalue"){
        bvalue = value.toBool();
    }else if (propertyId == "string"){
        string = value.toString();
    }else if (propertyId == "date"){
        date = value.toDate();
    }else if (propertyId == "time"){
        time = value.toTime();
    }else if (propertyId == "datetime"){
        datetime = value.toDateTime();
    }else if (propertyId == "keySequence"){
        keySequence = value.value<QKeySequence>();
    }else if (propertyId == "c"){
        c = value.toChar();
    }else if (propertyId == "local"){
        local = value.toLocale();
    }else if (propertyId == "point"){
        point = value.toPoint();
    }else if (propertyId == "pointf"){
        pointf = value.toPointF();
    }else if (propertyId == "size"){
        size = value.toSize();
    }else if (propertyId == "sizef"){
        sizef = value.toSizeF();
    }else if (propertyId == "rect"){
        rect = value.toRect();
    }else if (propertyId == "rectf"){
        rectf = value.toRectF();
    }else if (propertyId == "color"){
        color = value.value<QColor>();
    }else if (propertyId == "direction"){
        direction = Direction(value.toInt());
    }else if (propertyId == "sizePolicy"){
        sizePolicy = value.value<QSizePolicy>();
    }else if (propertyId == "font"){
        font = value.value<QFont>();
    }else if (propertyId == "cursor"){
        cursor = value.value<QCursor>();
    }else if (propertyId == "vector2d"){
        vector2d = value.value<QVector2D>();
    }else if (propertyId == "vector3d"){
        vector3d = value.value<QVector3D>();
    }else if (propertyId == "vector4d"){
        vector4d = value.value<QVector4D>();
    }else if (propertyId == "matrix44"){
        matrix44 = value.value<QMatrix4x4>();
    }else
    {
        ret = false;
    }

    return ret;
}
