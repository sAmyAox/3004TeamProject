#include "device.h"

device::device() // need update instructions
{
    battery = 100;
    operational = false;
    shockable = false;
    state = 0;
    // create a battery timer for auto decrease feature.
    battery_timer = new QTimer(this);
    connect(battery_timer, &QTimer::timeout, this, &device::battery_decrease);

    // create a timer for work flow , 1 time feature.
    init_timer = new QTimer(this);
    connect(init_timer, &QTimer::timeout, this, &device::display_device_status);
    connect(init_timer, &QTimer::timeout, this, &device::workflow);
    init_timer->setSingleShot(true);

    // create a timer for rhythm analysis , 1 time feature.
    rhythm_analysis_timer = new QTimer(this);
    connect(rhythm_analysis_timer, &QTimer::timeout, this, &device::temp);
    rhythm_analysis_timer->setSingleShot(true);
};
device::~device(){};

void device::get_patient_status(){

};
void device::shock()
{
    // success senario
    if (battery >= 15 && shockable == true && state == 2)
    {
        qDebug() << "shock";
        emit signal_shock();
        battery -= 15;
        emit battery_changed();
        emit text_prompt_update("Shock dilivered\n\nPlease follow the instruction to perform CPR until medical help arrives");
        shockable = false;
        state = 3;
        // fail
    }
    else if (shockable == true && battery < 15)
    {
        emit text_status_update("not enough battery lefted to diliver a shock.\n\nPlease seek medical instruction.");
    }
    else if (shockable == false && state == 1)
    { // just turn the divice on, no pads
        emit text_status_update("please attach electrode pads before diliver a shock.");
    }
    else if (shockable == false && state == 3)
    { // shocked already
        emit text_status_update("already dilivered a shock");
    }
};

int device::get_battery_capacity()
{
    return battery;
}

void device::battery_decrease()
{

    if (battery > 10 && operational == true)
    {
        battery -= 1;
    }
    else if (battery <= 10 && operational == true && battery >= 1)
    {
        battery -= 1;
        emit text_status_update("battery less then 10%, not able to diliver shock");
    }
    else if (battery == 0 && operational == true)
    {
        battery_timer->stop();
        shut_down();
    }
    emit battery_changed();
    qDebug() << "battery signal emited, auto decrease by 1%";
}

void device::init_sequence()
{

    if (operational == false)
    {
        operational = true;
        state = 1;
        qDebug() << "operational set to true";

        emit text_status_update("initializing");
        qDebug() << "init";
        emit battery_changed();
        battery_timer->start(1000); // 10s
        init_timer->start(3000);    // 3s
        // display_device_status();
    }
    else if (operational == true)
    {
        operational = false;
        state = 0;
        qDebug() << "operational set to false";
        shut_down();
    }
}

void device::display_device_status()
{

    // qDebug()<<"waited for 3 second";
    if (operational == true && state == 1)
    {
        QString status_message = "status: operational \nbattery remaining: " + QString::number(battery) + "\nCharge/Discharge: functional\nHeart rhythm analysis: functional";
        // need battery check, able to shock?, analysis?
        emit text_status_update(status_message);
        qDebug() << "status print";
    }
}
void device::detect_rhythm(){

};
void device::workflow()
{ // will connect after display status/when pressed on
    if (state == 1)
    {
        qDebug() << "work flow started\n";
        const QString message = "Please follow the instruction on electrode pad to place them correctly\n\n\nUnpackage electrode pads and place them to their coresponding place that shows on the instruction.\n\nwaiting for manual input...";
        emit text_prompt_update(message);

        // connect to display device status;     ok
        // display instruction for placeing pads and ask for user's interaction; ok
        // need more script for button clicked.
    } // ok
};
void device::display_good_CPR_feedback()
{
    if (state == 3 && operational == true)
    {
        qDebug() << "good cpr";
        emit text_CPR_update("please continue CPR until furthur instructions");
        state = 4;
    }
};

void device::display_bad_CPR_feedback()
{
    if (state == 3 && operational == true)
    {
        qDebug() << "bad cpr";
        emit text_CPR_update("please follow the instructions while porforming the CPR");
    }
};
/*
void device::display_prompt(){
    if(operational==false){return;}

    qDebug()<<"prompting";
    emit text_prompt_update("display prompts");

    if (shockable==false){
        emit text_prompt_update("patient is not suitable for dilivering a shock, please seek medical help immediately");
    }else if(shockable == true){
        emit text_prompt_update("stand clear, do not touch patient. shock will be diliver as press the 'Shock' button.");
    }

}*/

void device::display_good_electrode()
{ // if
    if (operational == false)
    {
        return;
    }
    else if (operational == true && state == 1)
    {
        state = 2;
        qDebug() << "good electrode";
        emit text_status_update("electrode pad placed correctly ");
        emit text_prompt_update("Please wait for rhythm analysis...");

        // add implementation for result of analysis of heart rhythm here.
        // continue the work flow here,i.e. shock
        rhythm_analysis_timer->start(3000); // 3s for analysis. connect to another function that uses the result to porform prompt.
    }
}

void device::display_bad_electrode()
{
    if (operational == false)
    {
        return;
    }
    else if (operational == true && state == 1)
    {
        qDebug() << "bad electrode";
        emit text_status_update("electrode pad placed incorrectly, please follow the instruction");
    }
}

void device::debug()
{

    qDebug() << "debuging";
    emit text_prompt_update("lmao");
    // MainWindow::update_text_prompt("abcde");
}

void device::temp()
{
    if (operational == false)
    {
        return;
    }
    bool result = true;
    if (result)
    {
        shockable = true;
        emit text_prompt_update("Shockable rhythm detected, STAND CLEAR and press 'shock'");
        state = 2;
    }
    else
    {
        shockable = false;
        emit text_prompt_update("Rhythm detected but is not suitable for diliver a shock. please seek for medical help immediatly");
    }
}

void device::heart_rhythm_analysis(int heartRate){
    if (operational == false){
        return;
    }
    if (heartRate < 60 || heartRate > 100){
        shockable = true;
        emit text_prompt_update("Shockable heart rhythm detected, STAND CLEAR and press 'shock'.")
    }
    else{
        shockable = false;
        emit text_prompt_update("Unshockable heart rhythm detected, not suitable for delivering a shock")
    }
}

void device::shut_down()
{
    // stop all timer,
    // clear every text browser(emit("") is fine),
    // disable every button,
    // set device status
    operational = false;
    battery_timer->stop();
    emit text_status_update("");
    emit text_prompt_update("");
    emit text_CPR_update("");
    state = 0;
}
