#include "matrixeditor.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QDoubleSpinBox>

#define CREATEMATRIXELEMENT(r, c)                                                           \
QLabel *labelm##r##c = new QLabel("m"#r#c, this);                                           \
labelm##r##c->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));           \
hlayout##r->addWidget(labelm##r##c);                                                        \
spinBoxm##r##c = new QDoubleSpinBox(this);                                                  \
spinBoxm##r##c->setMinimum(-LONG_MAX);                                                      \
spinBoxm##r##c->setMaximum(LONG_MAX);                                                       \
connect(spinBoxm##r##c, SIGNAL(valueChanged(double)), this, SLOT(slotSetValue(double)));    \
hlayout##r->addWidget(spinBoxm##r##c);

#define GETMATRIXELEMENT(r,c) m##r##c = spinBoxm##r##c->value();

MatrixEditor::MatrixEditor(QWidget *parent)
    :QWidget(parent)
{
    QVBoxLayout *vlayout1 = new QVBoxLayout();
    this->setLayout(vlayout1);
    vlayout1->setMargin(0);
    vlayout1->setSpacing(0);

    QVBoxLayout *vlayout = new QVBoxLayout();

    QFrame *frame = new QFrame(this);
    frame->setFrameShape(QFrame::StyledPanel);
    frame->setFrameShadow(QFrame::Plain);
    frame->setLineWidth(1);
    frame->setLayout(vlayout);
    vlayout1->addWidget(frame);

    QHBoxLayout *hlayout1 = new QHBoxLayout();
    vlayout->addLayout(hlayout1);
    QHBoxLayout *hlayout2 = new QHBoxLayout();
    vlayout->addLayout(hlayout2);
    QHBoxLayout *hlayout3 = new QHBoxLayout();
    vlayout->addLayout(hlayout3);
    QHBoxLayout *hlayout4 = new QHBoxLayout();
    vlayout->addLayout(hlayout4);

    CREATEMATRIXELEMENT(1,1)
    CREATEMATRIXELEMENT(1,2)
    CREATEMATRIXELEMENT(1,3)
    CREATEMATRIXELEMENT(1,4)

    CREATEMATRIXELEMENT(2,1)
    CREATEMATRIXELEMENT(2,2)
    CREATEMATRIXELEMENT(2,3)
    CREATEMATRIXELEMENT(2,4)

    CREATEMATRIXELEMENT(3,1)
    CREATEMATRIXELEMENT(3,2)
    CREATEMATRIXELEMENT(3,3)
    CREATEMATRIXELEMENT(3,4)

    CREATEMATRIXELEMENT(4,1)
    CREATEMATRIXELEMENT(4,2)
    CREATEMATRIXELEMENT(4,3)
    CREATEMATRIXELEMENT(4,4)
}

MatrixEditor::~MatrixEditor()
{
}

QMatrix4x4 MatrixEditor::value()
{
    return QMatrix4x4(m11, m12, m13, m14, m21, m22, m23, m24, m31, m32, m33, m34, m41, m42, m43, m44);
}

void MatrixEditor::setValue(const QMatrix4x4 &value)
{
    QVector4D row1 = value.row(0);
    m11 = row1.x();
    m12 = row1.y();
    m13 = row1.z();
    m14 = row1.w();

    QVector4D row2 = value.row(1);
    m21 = row2.x();
    m22 = row2.y();
    m23 = row2.z();
    m24 = row2.w();

    QVector4D row3 = value.row(2);
    m31 = row3.x();
    m32 = row3.y();
    m33 = row3.z();
    m34 = row3.w();

    QVector4D row4 = value.row(3);
    m41 = row4.x();
    m42 = row4.y();
    m43 = row4.z();
    m44 = row4.w();

    spinBoxm11->setValue(m11);
    spinBoxm12->setValue(m12);
    spinBoxm13->setValue(m13);
    spinBoxm14->setValue(m14);
    spinBoxm21->setValue(m21);
    spinBoxm22->setValue(m22);
    spinBoxm23->setValue(m23);
    spinBoxm24->setValue(m24);
    spinBoxm31->setValue(m31);
    spinBoxm32->setValue(m32);
    spinBoxm33->setValue(m33);
    spinBoxm34->setValue(m34);
    spinBoxm41->setValue(m41);
    spinBoxm42->setValue(m42);
    spinBoxm43->setValue(m43);
    spinBoxm44->setValue(m44);
}

void MatrixEditor::setDecimals(int dec)
{
    spinBoxm11->setDecimals(dec);
    spinBoxm12->setDecimals(dec);
    spinBoxm13->setDecimals(dec);
    spinBoxm14->setDecimals(dec);
    spinBoxm21->setDecimals(dec);
    spinBoxm22->setDecimals(dec);
    spinBoxm23->setDecimals(dec);
    spinBoxm24->setDecimals(dec);
    spinBoxm31->setDecimals(dec);
    spinBoxm32->setDecimals(dec);
    spinBoxm33->setDecimals(dec);
    spinBoxm34->setDecimals(dec);
    spinBoxm41->setDecimals(dec);
    spinBoxm42->setDecimals(dec);
    spinBoxm43->setDecimals(dec);
    spinBoxm44->setDecimals(dec);
}

void MatrixEditor::slotSetValue(double value)
{
    Q_UNUSED(value)

    QObject *sender = this->sender();
    if(sender == spinBoxm11){
        m11 = spinBoxm11->value();
    }else if(sender == spinBoxm12){
        m12 = spinBoxm12->value();
    }else if(sender == spinBoxm13){
        m13 = spinBoxm13->value();
    }else if(sender == spinBoxm14){
        m14 = spinBoxm14->value();
    }else if(sender == spinBoxm21){
        m21 = spinBoxm21->value();
    }else if(sender == spinBoxm22){
        m22 = spinBoxm22->value();
    }else if(sender == spinBoxm23){
        m23 = spinBoxm23->value();
    }else if(sender == spinBoxm24){
        m24 = spinBoxm24->value();
    }else if(sender == spinBoxm31){
        m31 = spinBoxm31->value();
    }else if(sender == spinBoxm32){
        m32 = spinBoxm32->value();
    }else if(sender == spinBoxm33){
        m33 = spinBoxm33->value();
    }else if(sender == spinBoxm34){
        m34 = spinBoxm34->value();
    }else if(sender == spinBoxm41){
        m41 = spinBoxm41->value();
    }else if(sender == spinBoxm42){
        m42 = spinBoxm42->value();
    }else if(sender == spinBoxm43){
        m43 = spinBoxm43->value();
    }else if(sender == spinBoxm44){
        m44 = spinBoxm44->value();
    }

    QMatrix4x4 val(m11, m12, m13, m14, m21, m22, m23, m24, m31, m32, m33, m34, m41, m42, m43, m44);
    emit valueChanged(val);
}
