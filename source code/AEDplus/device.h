#ifndef DEVICE_H
#define DEVICE_H


class device
{
private:
    int battery;
    bool operational;//if =false(didn;t press on), no respose, check before each function?
    bool shockable;//if shockable==true, then wait for the button_shock,else display prompt, ask for CPR


public:
    device(/* args */);
    ~device();

    void get_patient_status();//get patient's heart rate and vf.
    void shock();//deliver shock to patient
    void display_device_status();//show status when the device turned on
    void detect_rhythm();//getter for patient's heart rhythm
    void workflow();
    void display_CPR_feedback();//when pressed button, tell user if it is bad or good.
    //void error_mode();//if the device wait for too long, enter error mode.(asking to give CPR)
    void display_prompt();//maybe qstring?
};

#endif
