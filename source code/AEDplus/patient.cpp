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

void patient::set_status(){//random num
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
