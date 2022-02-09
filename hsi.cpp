#include "hsi.h"

QColor  hsi_blue = QColor(28, 157, 237);
QColor  hsi_orange = QColor(168, 73, 0);
QPen    arcPen(Qt::black);
QPen    whtLinePen(Qt::white,2);
QFont   font_14("DejaVu Sans Condensed", 12);
QList<QLine> bank_lines;

static const QPointF left_handle[6] = {
    QPointF(-55.0, 10.0),
    QPointF(-65.0, 10.0),
    QPointF(-65.0, 5.0),
    QPointF(-120.0, 5.0),
    QPointF(-120.0, -5.0),
    QPointF(-55.0, -5.0),
};

static const QPointF right_handle[6] = {
    QPointF(55.0, 10.0),
    QPointF(65.0, 10.0),
    QPointF(65.0, 5.0),
    QPointF(120.0, 5.0),
    QPointF(120.0, -5.0),
    QPointF(55.0, -5.0),
};

static const QPointF center_scope[4] = {
    QPointF(-3.0, -3.0),
    QPointF(3.0, -3.0),
    QPointF(3.0, 3.0),
    QPointF(-3.0, 3.0),
};

Hsi::Hsi(QWidget *parent)
    : QWidget{parent}
{

    bank_lines << QLine(-128, -99, -118, -94);
    bank_lines << QLine(-104, -122, -98, -116);
    bank_lines << QLine(-84, -138, -79, -131);
    bank_lines << QLine(-60, -146, -58, -141);

    bank_lines << QLine(-30, -148, -29, -145);
    bank_lines << QLine(0, -148, 0, -146);
    bank_lines << QLine(30, -148, 29 , -145);

    bank_lines << QLine(128, -99, 118, -94);
    bank_lines << QLine(104, -122, 98, -116);
    bank_lines << QLine(84, -138, 79, -131);
    bank_lines << QLine(60, -146, 58, -141);

    arcPen.setWidth(16);
    this->rollangle = 0;

    this->repaint();
}

//! setRollAngle function
/*!
 * \brief setRollAngle sets HSI to actual bank angle.
 * @param rollangle is bank angle of airplane.
 * @pre -
 */
void Hsi::setRollAngle(qreal rollangle)
{
    this->rollangle = rollangle;
    repaint();
}

//! setPitchAngle function
/*!
 * \brief setPitchAngle sets HSI to actual pitch angle.
 * @param pitchangle is pitch angle of airplane.
 * @pre -
 */
void Hsi::setPitchAngle(qreal pitchangle)
{
    this->pitchangle = pitchangle;

    topcoord = this->pitchangle;   //angle to pixel
    //TODO: angle to pixel
    repaint();
}

//! paintEvent function
/*!
 * \brief paintEvent draw HSI elements and paints.
 * @param event override.
 * @pre -
 */
void Hsi::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    painter.setFont(font_14);

    painter.setRenderHint(QPainter::Antialiasing);
    painter.translate(width() / 2, height() / 2);

    painter.rotate(this->rollangle);



    QPainterPath sky;
    sky.addRect(QRectF(-300, topcoord-300, 600, 300));
    QPen pen_blue(hsi_blue, 1);
    painter.setPen(pen_blue);
    painter.fillPath(sky, hsi_blue);
    painter.drawPath(sky);


    QPainterPath land;
    land.addRect(QRectF(-300, topcoord, 600, 300));
    QPen pen_orange(hsi_orange, 1);
    painter.setPen(pen_orange);
    painter.fillPath(land, hsi_orange);
    painter.drawPath(land);

    painter.setPen(whtLinePen); //pitch cizgi

    painter.drawLine(-300, topcoord, 300,  topcoord);   //ufuk cizgisi
    int lnwidth[4] = {15,30,15,60};
    int lntext[3] = {10,20,30};
    for (int i=0; i<12; i++)    //pitch cizgileri
    {
        if ((topcoord - (15*(i+1))) >= -130)    //ustten bir miktar asagidan baslatmak icin
        {
            painter.drawLine(-lnwidth[i%4], topcoord - (15*(i+1)), lnwidth[i%4],  topcoord - (15*(i+1)));//mavi alan
            painter.drawLine(-lnwidth[i%4], topcoord + (15*(i+1)), lnwidth[i%4],  topcoord + (15*(i+1)));//kahve alan

            if ((i+1)%4 == 0)       //10,20,30 pitch sayilari
            {
                painter.drawText(-(lnwidth[i%4] + 25), topcoord - (15*(i+1) + 8), 32, 20, Qt::AlignLeft, QString::number(lntext[i/4]));
                painter.drawText(-(lnwidth[i%4] + 25), topcoord + (15*(i+1) - 8), 32, 20, Qt::AlignLeft, QString::number(lntext[i/4]));
                painter.drawText((lnwidth[i%4] + 5), topcoord - (15*(i+1) + 8), 32, 20, Qt::AlignLeft, QString::number(lntext[i/4]));
                painter.drawText((lnwidth[i%4] + 5), topcoord + (15*(i+1) - 8), 32, 20, Qt::AlignLeft, QString::number(lntext[i/4]));
            }
        }
    }


    painter.drawRect(-15, -130, 30, 5);     //tepedeki ucgenin tabani
    painter.drawLine(-15, -130, 0, -140);
    painter.drawLine(15, -130, 0, -140);

    painter.rotate(-this->rollangle);

    painter.setBrush(Qt::SolidPattern);
    painter.drawLines(bank_lines);
    painter.drawPolygon(left_handle, 6);
    painter.drawPolygon(right_handle, 6);
    painter.drawPolygon(center_scope, 4);


    /* Rounded corners */
    painter.setPen(arcPen);
    painter.drawArc(88, -158, 70, 70, 90*16, -90*16);   //upper right
    painter.drawArc(-158, -158, 70, 70, 90*16, 90*16);  //upper left
    painter.drawArc(88, 88, 70, 70, 0*16, -90*16);   //lower right
    painter.drawArc(-158, 88, 70, 70, 180*16, 90*16);  //lower left
}
