#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "hsi.h"
#include "airspeed.h"
#include "fma.h"
#include "conversion.h"

Hsi         *pfdhsi;
Airspeed    *pfdairspeed;
Fma         *pfdfma;
Conversion  *convertunits;

ATengagedmodes atengmode = MCPSPD;
Rollengagedmodes rollengmode = HDGSEL;
Pitchengagedmodes pitchendmode = VNAVPTH;

qreal animidx = 0;
double         requested_kias = 200;
double         actual_kias = 0;

int         kias_incdec_counter = 0;
bool        kias_busy = false;
QTimer*     tmr_kiasupdate;
double      stepdegree = 1;

void MainWindow::updtmr(void)
{
    static bool direction = false;

    if (direction == false)
    {
        if (animidx >= 10){
            direction = true;
            //requested_kias = 150;
        }
        else
        {
            animidx++;

        }
    }
    else
    {
        if (animidx > -10)
            animidx--;
        else{
            direction = false;
            //requested_kias = 30;
        }
    }
    pfdhsi->setRollAngle(0);
    pfdhsi->setPitchAngle(0);

   /* pfdairspeed->setActualKIAS(abs(animidx)*10);
    pfdairspeed->setRotateAngle(animidx);*/

    if (requested_kias > actual_kias){

        actual_kias+=0.5;
    }
    else if (requested_kias < actual_kias){
        actual_kias-=0.5;
    }

    pfdairspeed->setTargetKIAS(175);
    pfdairspeed->setGroundSpeed(180);
    pfdairspeed->setActualKIAS(actual_kias);
    pfdairspeed->setRotateAngle(convertunits->kias2angle(actual_kias));

    pfdfma->setATEngagedMode(atengmode);
    pfdfma->setRollEngagedMode(rollengmode);
    pfdfma->setPitchEngagedMode(pitchendmode);

    pfdhsi->repaint();
    pfdairspeed->repaint();
    pfdfma->repaint();
}



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setStyleSheet("background-color:black;");

    ui->wdg_HSI->setGeometry(125, 120, 300, 300);
    ui->wdg_HSI->show();

    ui->wdg_AIRSPEED->setGeometry(5, 0, 100, 560);
    ui->wdg_AIRSPEED->show();

    ui->wdg_FMANAV->setGeometry(90, 5, 360, 110);
    ui->wdg_FMANAV->show();

    convertunits = new Conversion;

    pfdhsi = new Hsi(ui->wdg_HSI);
    pfdhsi->setGeometry(0, 0, 300, 300);

    pfdairspeed = new Airspeed(ui->wdg_AIRSPEED);
    pfdairspeed->setGeometry(0, 0, 70, 560);
    pfdairspeed->show();

    pfdfma = new Fma(ui->wdg_FMANAV);
    pfdfma->setGeometry(0, 0, 360, 125);
    pfdfma->show();

    //pfdairspeed->setRotateAngle(155);   //Calibration for 0 knot
    pfdairspeed->setActualKIAS(0);
    pfdairspeed->setRotateAngle(convertunits->kias2angle(0));

    QTimer* timer = new QTimer(this);
    timer->setSingleShot(false);
    timer->start(10);
    connect(timer, SIGNAL(timeout()), this, SLOT(updtmr()));

    //pfdairspeed->setActualKIAS(130);
}

MainWindow::~MainWindow()
{
    delete ui;
}

