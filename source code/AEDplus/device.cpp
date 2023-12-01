#include "device.h"

device::device()
{
    battery = 100;
    operational = false;
    shockable = false;
};
device::~device(){};

void device::get_patient_status(){

};
void device::shock(){
    qDebug()<<"shock";
    emit signal_shock();

};
void device::init_sequence(){
    QTimer timer ;



    emit text_status_update("initializing");
    qDebug()<<"init";
    display_device_status();
}


void device::display_device_status(){

    //qDebug()<<"waited for 3 second";
    QString status_message ="status: operational \nbattery remaining: "+QString::number(battery)+"";
    emit text_status_update(status_message);
    qDebug()<<"status print";



};
void device::detect_rhythm(){

};
void device::workflow(){

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

};

void device::display_good_electrode(){
    qDebug()<<"good electrode";
    emit text_status_update("electrode pad placed correctly ");
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

