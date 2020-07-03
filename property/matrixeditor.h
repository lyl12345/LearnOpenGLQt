#ifndef MATRIXEDITOR_H
#define MATRIXEDITOR_H

#include <QWidget>
#include <QMatrix4x4>

class QDoubleSpinBox;

class MatrixEditor : public QWidget
{
    Q_OBJECT
public:
    MatrixEditor(QWidget *parent = nullptr);
    virtual ~MatrixEditor();

    QMatrix4x4 value();
    void setValue(const QMatrix4x4& value);
    void setDecimals(int dec);
signals:
    void valueChanged(const QMatrix4x4&);

private slots:
    void slotSetValue(double value);

private:
    float m11, m12, m13, m14, m21, m22, m23, m24, m31, m32, m33, m34, m41, m42, m43, m44;

    QDoubleSpinBox *spinBoxm11;
    QDoubleSpinBox *spinBoxm12;
    QDoubleSpinBox *spinBoxm13;
    QDoubleSpinBox *spinBoxm14;

    QDoubleSpinBox *spinBoxm21;
    QDoubleSpinBox *spinBoxm22;
    QDoubleSpinBox *spinBoxm23;
    QDoubleSpinBox *spinBoxm24;

    QDoubleSpinBox *spinBoxm31;
    QDoubleSpinBox *spinBoxm32;
    QDoubleSpinBox *spinBoxm33;
    QDoubleSpinBox *spinBoxm34;

    QDoubleSpinBox *spinBoxm41;
    QDoubleSpinBox *spinBoxm42;
    QDoubleSpinBox *spinBoxm43;
    QDoubleSpinBox *spinBoxm44;
};

#endif // MATRIXEDITOR_H
