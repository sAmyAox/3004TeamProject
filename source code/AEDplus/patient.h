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
    int get_heart_rate();
    bool get_vf();
    bool get_shock_status();

    void set_heart_rate(int);
    void set_vf(bool);

signals:
    void signal_shocked();
    void signal_heart_rate(int heart_rate);
    void signal_vf(bool vf);
public slots:


};


#endif
