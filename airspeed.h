#ifndef AIRSPEED_H
#define AIRSPEED_H

#include <QWidget>
#include <QPainter>
#include <QColor>
#include <QPainterPath>
#include <QStaticText>
#include <QMatrix4x4>
#include <QVector3D>
#include <QList>
#include <QDebug>


struct CarouselItem;

class Airspeed : public QWidget
{
    Q_OBJECT
public:
    explicit Airspeed(QWidget *parent = nullptr);
    ~Airspeed();

public slots:
    void setTargetKIAS(int targetkias);     /**< Target indicated airpseed in knots. */
    void setActualKIAS(double actualkias);  /**< Actual indicated airpseed in knots. */
    void setOverSpeed(int overspeed);       /**< Indicated airpseed Speed that should not be exceeded. */
    void setBelowSpeed(int belowspeed);      /**< Indicated airpseed Speed that should not be undershot. */
    void setVREF(int vref);                 /**< Speed for landing. Pilot must add wind factor. */
    void setFLAP(int flap);                 /**< Flap degree for landing. */
    void setGroundSpeed(int groundspeed);   /**< Ground speed. */
    void setRotateAngle(double rotateAngle);/**< Do scroll by angle in .1 degree */
    int getActualKIAS(void);
signals:
protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

    int targetkias;
    double actualkias;
    int requestedkias;
    int overspeed;
    int belowspeed;
    int vref;
    int flap;
    int groundspeed;
private:
    QList<CarouselItem*> items;

};

#endif // AIRSPEED_H
