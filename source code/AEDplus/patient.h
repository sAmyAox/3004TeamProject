#ifndef PATIENT_H
#define PATIENT_H

class patient
{
private:
    bool vf;//venticular fibrillation
    int heart_rate;
    //bool vt;//venticular tacgycardia, heart_rate>120 == true
    bool shocked;//the status of patient, false==before shock




public:
    patient(/* args */);
    ~patient();



};


#endif
