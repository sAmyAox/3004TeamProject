#include "device.h"

device::device()
{   //update
    counter_breath = 0;
    counter_chest = 0;


    //update above
    battery = 100;
    operational = false;
    shockable = false;
    state = 0;
    myPatient = new patient;
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
    connect(rhythm_analysis_timer, &QTimer::timeout, this, &device::heart_rhythm_analysis);
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
        myPatient->set_status();
        qDebug()<<"patient's heart rate is"<<myPatient->get_heart_rate();
        qDebug()<<"patient's shock status is "<<myPatient->get_shock_status();
        battery -= 15;
        emit battery_changed();
        qDebug() << "'audio prompt'";
        emit text_prompt_update("Shock dilivered\n\nPlease follow the instruction to perform CPR until medical help arrives\nGive 30 chest compressions\nHand position: Two hands centered on the chest\nBody position: Shoulders directly over hands; elbows locked\nDepth: At least 2 inches\nRate: 100 to 120 per minute\nAllow chest to return to normal position after each compression\n give 30 compression and 2 breathes\n");
        shockable = false;
        state = 3;
        emit image_select();
        //emit text_CPR_update("Give 30 chest compressions\nHand position: Two hands centered on the chest\nBody position: Shoulders directly over hands; elbows locked\nDepth: At least 2 inches\nRate: 100 to 120 per minute\nAllow chest to return to normal position after each compression\n give 2 breathes after 30 compression\n");
        // fail
    }
    else if (shockable == true && battery < 15)
    {
        emit text_status_update("not enough battery lefted to diliver a shock.\n\nPlease seek medical instruction.");
        qDebug() << "'audio prompt'";
    }
    else if (shockable == false && state == 1)
    { // just turn the divice on, no pads
        emit text_status_update("please attach electrode pads before diliver a shock.");
        qDebug() << "'audio prompt'";
    }
    else if (shockable == false && state == 3)
    { // shocked already
        emit text_status_update("already dilivered a shock");
        qDebug() << "'audio prompt'";
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
        qDebug() << "'audio prompt'";
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
        battery_timer->start(5000); // 5s
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


    if (operational == true && state == 1)
    {
        QString status_message = "status: operational \nbattery remaining: " + QString::number(battery) + "\nCharge/Discharge: functional\nHeart rhythm analysis: functional";

        emit text_status_update(status_message);
        qDebug() << "status print";
    }
}

void device::workflow(){ // will connect after display status/when pressed on
    if (state == 1)
    {
        qDebug() << "work flow started\n";
        const QString message = "Place one pad on the right side of the chest, on the area just below the collarbone. \nPlace the other pad on the lower left side of the chest, underneath the armpit area.\n\n\nwaiting for manual input...";
        qDebug() << "'audio prompt'";
        emit text_prompt_update(message);


        // connect to display device status;     ok
        // display instruction for placeing pads and ask for user's interaction; ok

    }
};
void device::display_good_CPR_feedback()
{
    if (state == 3 && operational == true)
    {
        qDebug() << "good cpr";
        emit text_CPR_update("please continue CPR until furthur instructions");
        qDebug() << "'audio prompt'";
        state = 4;
    }
};

void device::display_bad_CPR_feedback()
{
    if (state == 3 && operational == true)
    {
        qDebug() << "bad cpr";
        emit text_CPR_update("please follow the instruction to give CPR");
        qDebug() << "'audio prompt'";
        //emit text_CPR_update("Give 30 chest compressions\nHand position: Two hands centered on the chest\nBody position: Shoulders directly over hands; elbows locked\nDepth: At least 2 inches\nRate: 100 to 120 per minute\nAllow chest to return to normal position after each compression");
    }
};

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
        qDebug() << "'audio prompt'";
        emit image_timer_statr();

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
        qDebug() << "'audio prompt'";
    }
}

void device::heart_rhythm_analysis(){
    if (operational == false){
        return;
    }
    qDebug()<<"from HRA";
    if ((myPatient->get_heart_rate() < 50 || myPatient->get_heart_rate() > 120)||myPatient->get_vf()==true){
        shockable = true;
        emit text_prompt_update("Shockable heart rhythm detected, STAND CLEAR and press 'shock'.");
        qDebug() << "'audio prompt'";
    }
    else{
        shockable = false;
        emit text_prompt_update("Unshockable heart rhythm detected, not suitable for delivering a shock");
        qDebug() << "'audio prompt'";
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
    emit image_timer_stop();
    emit battery_label_clear();
    emit image_clear();
    state = 0;
}
//update

void device::cpr_analysis(int chest, int breath){
    counter_chest+=chest;
    counter_breath+=breath;
    qDebug()<<"counter chest: "<<counter_chest<<"  counter breath"<<counter_breath;
    QString message = "breath count = "+QString::number(counter_breath)+"\nchest compression count = "+QString::number(counter_chest);

    text_CPR_update(message);
    if (counter_chest == 30&&counter_breath==2){
        qDebug()<<"good cpr";
        qDebug() << "'audio prompt'";
        counter_breath=0;
        counter_chest = 0;
        display_good_CPR_feedback();
    }else if(counter_chest<30 && counter_breath>0){
        qDebug()<<"less than 30 press";
        qDebug() << "'audio prompt'";
        counter_breath=0;
        counter_chest = 0;
        //text_CPR_update("Please start again and give chest compressions");
        display_bad_CPR_feedback();
    }else if(counter_chest==30&&counter_breath>2){
        counter_breath=0;
        counter_chest = 0;
        //text_CPR_update("Please start again and give chest compressions");
        qDebug()<<"more than 2 breath";
        qDebug() << "'audio prompt'";
        display_bad_CPR_feedback();
    }else if (counter_chest>30){
        counter_breath=0;
        counter_chest = 0;
        //text_CPR_update("Please start again and give chest compressions");
        qDebug()<<"more than 30 chest press";
        qDebug() << "'audio prompt'";
        display_bad_CPR_feedback();
    }
    //counter_breath
}

void device::on_press_breath(){
    if (state == 3 && operational == true){
        qDebug()<<"breath add";
        cpr_analysis(0,1);

    }

}
void device::on_press_chest(){
    if (state == 3 && operational == true){
        qDebug()<<"chest add";
        cpr_analysis(1,0);

    }
}
