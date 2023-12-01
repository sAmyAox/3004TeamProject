#ifndef DEVICE_H
#define DEVICE_H

#include <QObject>
#include <QDebug>
#include "mainwindow.h"
#include "QString"
#include "QTimer"
#include "patient.h"

class device:public QObject
{
    Q_OBJECT

private:
    int battery;
    bool operational;//if =false(didn;t press on), no respose, check before each function?
    bool shockable;//if shockable==true, then wait for the button_shock,else display prompt, ask for CPR


public:
    device(/* args */);
    ~device();

    void get_patient_status();//get patient's heart rate and vf.
    void shock();//deliver shock to patient
    void display_device_status();//show status when the device turned on
    void detect_rhythm();//getter for patient's heart rhythm
    void workflow();//init for patients and blabla.
    void display_bad_CPR_feedback();//when pressed button, tell user if it is bad or good.
    void display_good_CPR_feedback();//when pressed button, tell user if it is bad or good.
    //void error_mode();//if the device wait for too long, enter error mode.(asking to give CPR)
    void display_prompt();//maybe qstring?
    void display_bad_electrode();
    void display_good_electrode();
    void init_sequence();//member function for init the divece, and wait for 3s to start the device



signals:
    void text_prompt_update(const QString &str);
    void text_CPR_update(const QString &str);
    void text_status_update(const QString &str);
    void signal_shock();

public slots:
    void debug();





};

#endif
