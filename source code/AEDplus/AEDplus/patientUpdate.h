#ifndef PATIENT_H
#define PATIENT_H

#include <QObject>
#include <QDebug>
#include <QTimer>
#include <QImage>
#include <QPixmap>
#include <QLabel>
#include <QGraphicsScene>

namespace Ui {
class MainWindow;
}

class patient:public QObject
{
    Q_OBJECT
private:
    bool vf;//venticular fibrillation
    int heart_rate;
    //bool vt;//venticular tacgycardia, heart_rate>120 == true
    bool shocked;//the status of patient, false==before shock
    QTimer* ecgTimer;
    QGraphicsScene *scene;
    Ui::MainWindow* ui;


//probably we need 3 types of ECGs, 1 for vf only, 1 for vt+vf and 1 for normal(after shocked), *extra* with good/bad cpr , it is 4 ecgs

public:
    patient();
    ~patient();

    void set_status();

signals:
    void signal_shocked();
public slots:
    void updateECG();


};


#endif
