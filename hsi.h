#ifndef HSI_H
#define HSI_H
#include <QWidget>
#include <QPainter>
#include <QColor>
#include <QPainterPath>
#include <QStaticText>

class Hsi : public QWidget
{
    Q_OBJECT
public:
    explicit Hsi(QWidget *parent = nullptr);

public slots:
    void setRollAngle(qreal rollangle);     /**< Bank angle of airplane */
    void setPitchAngle(qreal pitchangle);   /**< Pitch angle of airplane */
signals:

protected:
    void paintEvent(QPaintEvent *event);
    qreal rollangle;
    qreal pitchangle;
    qreal topcoord;
};

#endif // HSI_H
