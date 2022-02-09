#include "airspeed.h"

QPen    whtLinePen_a(Qt::white,2);
QPen    purpLinePen_a(QColor(249, 147, 249, 255),2);
QFont   font_14_a("DejaVu Sans Condensed", 12);
QFont   font_16_a("DejaVu Sans Condensed", 16);
QFont   font_18_a("DejaVu Sans Condensed", 18);
QPen    whttextpen16(QColor(255, 255, 255, 255));

static const QPointF actual_kias_window[7] = {
    QPointF(-30.0, 25.0),
    QPointF(25.0, 25.0),
    QPointF(25.0, 10.0),
    QPointF(35.0, 0.0),
    QPointF(25.0, -10.0),
    QPointF(25.0, -25.0),
    QPointF(-30.0, -25.0),
};

struct CarouselItem {
    double      angle;
    QPixmap     pixmap;
    QString     pixmaptxt;
    int         pindex;
    QRect       rect;
    QVector3D   center;
};

int         radius = 200;                 //dönme yaricapi
QVector3D   rotateAxis(-1, 0, 0);          //bu eksen etrafinda döndür
QVector3D   maxItemCenter(0, 0 ,radius);  //en büyük ögenin merkez koordinati
int         maxItemWidth  = 40;           //en büyük öğenin genisligi 370
int         maxItemHeight = 40;           //en büyük öğenin yuksekligi    268
double      minItemZoom   = 1;            //en küçük öğenin en öndeki öğeye orani

CarouselItem *item[36];


//! Airspeed function
/*!
 * \brief Airspeed constructor makes horizontal carousel.
 * @param -.
 * @pre -
 */
Airspeed::Airspeed(QWidget *parent)
    : QWidget{parent}
{
    for (int i = 0; i < 36; ++i)
         items << new CarouselItem;

    for (int i = 0; i < items.size(); ++i)
    {
        item[i] = items[i];
        item[i]->pindex = i*10;
        item[i]->pixmaptxt = QString::number((i)*10);

        double rotateAngle = 360.0/items.size()*i;
        QMatrix4x4 matrix;

        matrix.rotate(360 / items.size() * i, rotateAxis);
        item[i]->center = matrix.map(maxItemCenter);

        double rate = minItemZoom +  (1-minItemZoom) * (1-(maxItemCenter.z()-item[i]->center.z())/2/radius);
        item[i]->rect.setRect(0, 0, maxItemWidth*rate, maxItemHeight*rate);
        item[i]->rect.moveCenter(item[i]->center.toPoint());

        item[i]->angle = rotateAngle;

        //item[i]->pixmaptxt = QString::number((rotateAngle)/**10*/);

        //qDebug() << rotateAngle;
    }

    this->actualkias = 0;
    this->requestedkias = 0;
    this->groundspeed = 0;

    std::sort(items.begin(), items.end(), [](CarouselItem* a, CarouselItem* b) -> bool {
            return a->center.z() < b->center.z();
        });
}

Airspeed::~Airspeed() {
    qDeleteAll(items);
}

void Airspeed::setTargetKIAS(int targetkias)
{
    this->targetkias = targetkias;
}

void Airspeed::setActualKIAS(double actualkias)
{
    this->actualkias = actualkias;
}

int Airspeed::getActualKIAS(void)
{
    return this->actualkias;
}

void Airspeed::setOverSpeed(int overspeed)
{
    this->overspeed = overspeed;
}

void Airspeed::setBelowSpeed(int belowspeed)
{
    this->belowspeed = belowspeed;
}

void Airspeed::setVREF(int vref)
{
    this->vref = vref;
}

void Airspeed::setFLAP(int flap)
{
    this->flap = flap;
}

void Airspeed::setGroundSpeed(int groundspeed)
{
    this->groundspeed = groundspeed;
}

//! setRotateAngle function
/*!
 * \brief setRotateAngle scroll airspeed indicator by .1 deg angle.
 * @param double rotateAngle.
 * @pre -
 */
void Airspeed::setRotateAngle(double rotateAngle) {

    //qDebug() << rotateAngle;
    for (int i = 0; i < items.size(); ++i)
    {
        QMatrix4x4 matrix;
        matrix.rotate(item[i]->angle + rotateAngle, rotateAxis);

        QVector3D maxItemCenter(0, 0, radius);
        item[i]->center = matrix.map(maxItemCenter);

        double rate = minItemZoom + (1-minItemZoom) * (1 - (maxItemCenter.z() - item[i]->center.z()) / 2 / radius);

        item[i]->rect.setRect(0, 0, maxItemWidth * rate, maxItemHeight * rate);
        item[i]->rect.moveCenter(item[i]->center.toPoint());
    }
}

//! paintEvent function
/*!
 * \brief paintEvent draws AIRSPEED values on the Left band.
 * @param event override.
 * @pre -
 */
void Airspeed::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    //----------------------- Purple Set speed
    painter.setFont(font_18_a);
    painter.setPen(purpLinePen_a);
    painter.drawText(20, 30, 45, 30, Qt::AlignRight, QString::number(this->targetkias));

    //----------------------- White Ground speed
    painter.setFont(font_16_a);
    painter.setPen(whtLinePen_a);
    painter.drawText(0, 480, 70, 30, Qt::AlignRight, QString("GS%1").arg(this->groundspeed));
    //------------------------

    painter.fillRect(0,80,70,390, QColor(64,64,64));
    painter.translate(width()/2, height()/2);

    painter.setFont(font_16_a);
    painter.setPen(whtLinePen_a);


    //painter.drawText(0,0,50,50, Qt::AlignRight, "sdff");

    foreach (const CarouselItem *item, items)
    {
        if (item->center.z() < -70)
        {
            painter.drawLine(item->rect.x()+44, item->rect.y() + 12, item->rect.x() + 55,  item->rect.y() + 12);

            if ((item->pindex / 10) & 0x01)
            {

            }
            else
            {
                painter.drawText(item->rect, Qt::AlignLeft, /*QString::number(item->pindex)*/item->pixmaptxt);
            }
        }
        //qDebug() << item->pindex << "-" << item->center.z();
       //painter.drawPixmap(item->rect, item->pixmap);
    }

    //Soldaki kias penceresi
    painter.setBrush(Qt::SolidPattern);
    painter.drawPolygon(actual_kias_window, 7);
    painter.setFont(font_18_a);
    painter.drawText(-25, -12, 45, 30, Qt::AlignRight, QString::number((int)this->actualkias));



}
