#include "fma.h"

QPen    whtLinePen_f(Qt::white,2);
QPen    greenLinePen_f(QColor(9, 248, 61, 255),2);
QFont   font_16_f("Bahnschrift Condensed", 16);

Fma::Fma(QWidget *parent)
    : QWidget{parent}
{

}


//! setATEngagedMode function
/*!
 * \brief setATEngagedMode update ATengaged mode.
 * @param enum ATengagedmodes mode.
 * @pre -
 */
void Fma::setATEngagedMode(ATengagedmodes mode)
{
    this->atmode = mode;
}

//! setRollEngagedMode function
/*!
 * \brief setRollEngagedMode update Rollengaged mode.
 * @param enum Rollengagedmodes mode.
 * @pre -
 */
void Fma::setRollEngagedMode(Rollengagedmodes mode)
{
    this->rollmode = mode;
}

//! setRollEngagedMode function
/*!
 * \brief setRollEngagedMode update Rollengaged mode.
 * @param enum Rollengagedmodes mode.
 * @pre -
 */
void Fma::setPitchEngagedMode(Pitchengagedmodes mode)
{
    this->pitchmode = mode;
}

//! paintEvent function
/*!
 * \brief paintEvent draws FMA and NAV section to top.
 * @param event override.
 * @pre -
 */
void Fma::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    painter.fillRect(0,0,360,40, QColor(64,64,64));
    painter.setPen(whtLinePen_f);

    painter.drawLine(120, 0, 120, 40);
    painter.drawLine(240, 0, 240, 40);


    //------------- A/T Engaged Mode ----------------
    painter.setFont(font_16_f);
    painter.setPen(greenLinePen_f);
    painter.drawText(10, 0, 100, 20, Qt::AlignCenter, QString(atengagedtext[this->atmode]));

    //------------- Roll Engaged Mode ----------------
    painter.setFont(font_16_f);
    painter.setPen(greenLinePen_f);
    painter.drawText(130, 0, 100, 20, Qt::AlignCenter, QString(rollengagedtext[this->rollmode]));

    //------------- Pitch Engaged Mode ----------------
    painter.setFont(font_16_f);
    painter.setPen(greenLinePen_f);
    painter.drawText(250, 0, 100, 20, Qt::AlignCenter, QString(pitchengagedtext[this->pitchmode]));

}
