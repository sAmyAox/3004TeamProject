#ifndef DEVICE_H
#define DEVICE_H

#include <QObject>
#include <QDebug>
//#include "mainwindow.h"
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
    int state; //0 = no power, 1="on" pressed, 2=electrode button pressed,3=aftershock,4=after CPR
    QTimer *battery_timer;
    QTimer *init_timer;
    QTimer *rhythm_analysis_timer;
    patient *myPatient;
    int counter_chest;
    int counter_breath;

public:
    device();
    ~device();

    void get_patient_status();//get patient's heart rate and vf.
    int get_battery_capacity();//get battery's capacity, for update battery label
    //int get_patient_heart_rhythm();//get patient's heart rhythm.

    void shock();//deliver shock to patient
    void display_device_status();//show status when the device turned on
    int detect_rhythm();//getter for patient's heart rhythm

    void workflow();//init for patients and blabla.
    void display_bad_CPR_feedback();//when pressed button, tell user if it is bad or good.
    void display_good_CPR_feedback();//when pressed button, tell user if it is bad or good.
    //void error_mode();//if the device wait for too long, enter error mode.(asking to give CPR)
    //void display_prompt();//maybe qstring?
    void display_bad_electrode();
    void display_good_electrode();
    void init_sequence();//member function for init the divece, and wait for 3s to start the device
    void battery_decrease();//function for battery capacity goes down.
    void heart_rhythm_analysis();//compare the heart rhythm of patient with the shockable heart rhythm.
    friend class MainWindow;
    void shut_down();

    //update
    void cpr_analysis(int chest,int breath);
    void on_press_breath();
    void on_press_chest();

    //update dec 12
    void recharge();
    void disconnect();



signals:
    void text_prompt_update(const QString &str);
    void text_CPR_update(const QString &str);
    void text_status_update(const QString &str);
    void signal_shock();
    void battery_changed();


    //edit dec 6
    void image_timer_statr();
    void image_timer_stop();
    void battery_label_clear();
    void image_clear();
    void image_select();


public slots:
    //void debug();
   // void temp();





};

#endif
