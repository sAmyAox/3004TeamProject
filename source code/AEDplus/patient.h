#ifndef PATIENT_H
#define PATIENT_H

#include <QObject>

class patient:public QObject
{
    Q_OBJECT
private:
    bool vf;//venticular fibrillation
    int heart_rate;
    //bool vt;//venticular tacgycardia, heart_rate>120 == true
    bool shocked;//the status of patient, false==before shock




public:
    patient(/* args */);
    ~patient();

signals:
    void signal_shocked();
public slots:


};


#endif
