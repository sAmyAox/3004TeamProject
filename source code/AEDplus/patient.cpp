#include "patient.h"

patient::patient()
{
    vf = true;
    heart_rate = 150;
    // vt = false;
    shocked = false;
}

patient::~patient()
{
}

void patient::set_status(){
    this->shocked = true;
    qDebug()<<"set shocked to true";
}

int patient::get_heart_rate(){

    return this->heart_rate;
}
bool patient::get_vf(){
    return this->vf;

}
bool patient::get_shock_status(){
    return this->shocked;
}

void patient::set_heart_rate(int input){
    this->heart_rate = input;
    qDebug()<<"now patient's heart rate is:"<<heart_rate;
}
void patient::set_vf(bool input){
    this->vf = input;
    qDebug()<<"now patient's vf status is:"<<vf;
}

