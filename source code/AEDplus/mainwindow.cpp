#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

   // myPatient = new patient;
    myDevice = new device;

    connect(ui->button_on,&QPushButton::pressed,myDevice,&device::init_sequence);
    connect(ui->button_shock,&QPushButton::pressed,myDevice,&device::shock);
    connect(ui->button_good_CPR,&QPushButton::pressed,myDevice,&device::display_good_CPR_feedback);
    connect(ui->button_bad_CPR,&QPushButton::pressed,myDevice,&device::display_bad_CPR_feedback);
    connect(ui->button_bad_electrode,&QPushButton::pressed,myDevice,&device::display_bad_electrode);
    connect(ui->button_good_electrode,&QPushButton::pressed,myDevice,&device::display_good_electrode);

    connect(myDevice,&device::text_prompt_update,this,&MainWindow::update_text_prompt);
    connect(myDevice,&device::text_CPR_update,this,&MainWindow::update_text_CPR);
    connect(myDevice,&device::text_status_update,this,&MainWindow::update_text_status);
    //connect(myDevice,&device::signal_shock,myPatient,&patient::set_status);

    connect(myDevice, &device::battery_changed,this,&MainWindow::update_battery_label);



}

MainWindow::~MainWindow()
{
    delete ui;
    delete myDevice;
    //delete myPatient;
}



void MainWindow::update_battery_label(){
    int battery = myDevice->get_battery_capacity();

    ui->batterylabel->setText("battery: "+QString::number(battery)+"%");
    qDebug()<<"update battery capacity by getter function";
}


void MainWindow::update_text_prompt(const QString &text){
    ui->text_prompt->setText(text);
}

void MainWindow::update_text_CPR(const QString &text){
    ui->text_feedback->setText(text);
}

void MainWindow::update_text_status(const QString &text){
    ui->text_device_status->setText(text);
}
/*void MainWindow::button_clicked_on(){
    emit signal1();
}*/
