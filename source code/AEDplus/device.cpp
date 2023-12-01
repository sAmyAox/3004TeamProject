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

};
void device::display_device_status(){

};
void device::detect_rhythm(){

};
void device::workflow(){

};
void device::display_good_CPR_feedback(){
    qDebug()<<"good cpr";
};

void device::display_bad_CPR_feedback(){
    qDebug()<<"bad cpr";
};

void device::display_prompt(){

};

void device::debug(){
    qDebug()<<"debuging";
    emit text_prompt_update("lmao");
    //MainWindow::update_text_prompt("abcde");
}
