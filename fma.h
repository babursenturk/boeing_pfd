#ifndef FMA_H
#define FMA_H

#include <QWidget>
#include <QPainter>
#include <QColor>
#include <QPainterPath>

const QString atengagedtext[7] = {
     {"N1"},
     {"GA"},
     {"RETARD"},
     {"FMC SPD"},
     {"MCP SPD"},
     {"THR HOLD"},
     {"ARM"},
};

const QString rollengagedtext[4] = {
     {"HDG SEL"},
     {"VOR/LOC"},
     {"LNAV"},
     {"B/CRS"},
};

const QString pitchengagedtext[10] = {
     {"TO/GA"},
     {"V/S"},
     {"ALT HOLD"},
     {"ALT/ACQ"},
     {"VNAV SPD"},
     {"VNAV PTH"},
     {"VNAV ALT"},
     {"MCP SPD"},
     {"G/S"},
     {"FLARE"},
};

enum ATengagedmodes { N1 = 0, GA, RETARD, FMCSPD, MCPSPD, THRHOLD, ARM};
enum Rollengagedmodes { HDGSEL = 0, VORLOC, LNAV, BCRS};
enum Pitchengagedmodes {TOGA = 0, VS, ALTHOLD, ALTACQ, VNAVSPD, VNAVPTH, VNAVALT, MCP2SPD, GS, FLARE};

class Fma : public QWidget
{
    Q_OBJECT
public:
    explicit Fma(QWidget *parent = nullptr);
    void setATEngagedMode(ATengagedmodes mode);
    void setRollEngagedMode(Rollengagedmodes mode);
    void setPitchEngagedMode(Pitchengagedmodes mode);
protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
    ATengagedmodes atmode;
    Rollengagedmodes    rollmode;
    Pitchengagedmodes    pitchmode;
signals:

};

#endif // FMA_H
