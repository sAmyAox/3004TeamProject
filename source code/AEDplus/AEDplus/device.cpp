#include "device.h"

device::device()//need a state mechine/enum to help porform the entire work flow.check fo status befor emit signal.
// divece will not respond for incorrect input.
{
    battery = 100;
    operational = false;
    shockable = false;
    //create a battery timer for auto decrease feature.
    battery_timer = new QTimer(this);
    connect(battery_timer, &QTimer::timeout,this, &device::battery_decrease);


    //create a timer for work flow , 1 time feature.
    init_timer = new QTimer(this);
    connect(init_timer, &QTimer::timeout,this, &device::display_device_status);
    connect(init_timer, &QTimer::timeout,this, &device::workflow);
    init_timer->setSingleShot(true);

    //create a timer for rhythm analysis , 1 time feature.
    rhythm_analysis_timer = new QTimer(this);
    connect(rhythm_analysis_timer, &QTimer::timeout,this, &device::temp);
    rhythm_analysis_timer->setSingleShot(true);

};
device::~device(){};

void device::get_patient_status(){

};
void device::shock(){
    qDebug()<<"shock";
    emit signal_shock();
    emit text_prompt_update("Shock dilivered./n/nPlease follow the instruction to perform CPR until medical help arrives");

};

int device::get_battery_capacity(){
    return battery;
}

void device::battery_decrease(){

    if (battery >0){
        battery-=1;
    }else if (battery ==0){
        battery_timer->stop();
    }
    emit battery_changed();
    qDebug()<<"battery signal emited";
}



void device::init_sequence(){


    emit text_status_update("initializing");
    qDebug()<<"init";
    battery_timer->start(10000);//10s
    init_timer->start(3000);//3s
    //display_device_status();
}


void device::display_device_status(){

    //qDebug()<<"waited for 3 second";
    QString status_message ="status: operational \nbattery remaining: "+QString::number(battery)+"";
    emit text_status_update(status_message);
    qDebug()<<"status print";



};
void device::detect_rhythm(){

};
void device::workflow(){//will connect after display status/when pressed on
    qDebug()<<"work flow started";
    const QString message = "Please follow the instruction on electrode pad to place them correctly\n\n\nUnpackage electrode pads and place them to their coresponding place that shows on the instruction.\n\nwaiting for manual input...";
    emit text_prompt_update(message);


    //connect to display device status;
    //display instruction for placeing pads and ask for user's interaction;
    //need more script for button clicked.
};
void device::display_good_CPR_feedback(){
    qDebug()<<"good cpr";
    emit text_CPR_update("please continue until furthur instructions");


};

void device::display_bad_CPR_feedback(){
    qDebug()<<"bad cpr";
    emit text_CPR_update("please follow the instructions");
};

void device::display_prompt(){
    qDebug()<<"prompting";
    emit text_prompt_update("display prompts");

    if (shockable==false){
        emit text_prompt_update("patient is not suitable for dilivering a shock, please seek medical help immediately");
    }else if(shockable == true){
        emit text_prompt_update("stand clear, do not touch patient. shock will be diliver as press the 'Shock' button.");
    }

}

void device::display_good_electrode(){
    qDebug()<<"good electrode";
    emit text_status_update("electrode pad placed correctly ");
    emit text_prompt_update("Please wait for rhythm analysis...");

        //add implementation for result of analysis of heart rhythm here.
        //continue the work flow here,i.e. shock
    rhythm_analysis_timer->start(3000);//3s for analysis. connect to another function that uses the result to porform prompt.
}

void device::display_bad_electrode(){
    qDebug()<<"bad electrode";
    emit text_status_update("electrode pad placed incorrectly, please follow the instruction");

}

void device::debug(){
    qDebug()<<"debuging";
    emit text_prompt_update("lmao");
    //MainWindow::update_text_prompt("abcde");
}

void device::temp(){
    bool result = true;
    if(result){
        emit text_prompt_update("Shockable rhythm detected, STAND CLEAR and press 'shock'");
    }else{
        emit text_prompt_update("Rhythm detected but is not suitable for diliver a shock. please seek for medical help immediatly");
    }
}
