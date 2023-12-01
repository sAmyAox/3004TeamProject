#include "patient.h"

patient::patient()
{
    vf = false;
    heart_rate = 0;
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
