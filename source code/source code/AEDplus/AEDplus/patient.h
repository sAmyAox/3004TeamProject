#ifndef PATIENT_H
#define PATIENT_H

#include <QObject>
#include <QDebug>

class patient:public QObject
{
    Q_OBJECT
private:
    bool vf;//venticular fibrillation
    int heart_rate;
    //bool vt;//venticular tacgycardia, heart_rate>120 == true
    bool shocked;//the status of patient, false==before shock


//probably we need 3 types of ECGs, 1 for vf only, 1 for vt+vf and 1 for normal(after shocked), *extra* with good/bad cpr , it is 4 ecgs

public:
    patient(/* args */);
    ~patient();

    void set_status();

signals:
    void signal_shocked();
public slots:


};


#endif
