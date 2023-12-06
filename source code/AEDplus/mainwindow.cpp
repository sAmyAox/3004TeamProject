#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    timer = new QTimer;


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

    //update
    connect(myDevice,&device::battery_label_clear,this,&MainWindow::battery_shut_down);
    connect(timer, &QTimer::timeout,this,&MainWindow::update_image);
    connect(myDevice,&device::image_timer_statr,this,&MainWindow::timer_start);
    connect(myDevice,&device::image_timer_stop,this,&MainWindow::timer_stop);




       //handle ecg:
    startingX = 500;
    startingY = 0;
    cur_length = 1;
    cur_height = 200;
    max_length = 500;
    max_height = 200;



    if(myDevice->myPatient->get_shock_status()==false && myDevice->myPatient->get_vf()==true){
        myPixmap.load(":/heartrate_graph/VF.png");
        qDebug()<<"loading vf";
    }else if(myDevice->myPatient->get_shock_status()==false &&myDevice->myPatient->get_heart_rate()>120){
        myPixmap.load(":/heartrate_graph/VTpng.png");
        qDebug()<<"loading vt";
    }

    origin_length = myPixmap.width();

    QPixmap graph = myPixmap.copy(startingX,startingY,cur_length,cur_height);
    ui->ecg_graph->setPixmap(graph);


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

void MainWindow::battery_shut_down(){
    ui->batterylabel->setText("battery:  %");
}

void MainWindow::timer_start(){
    this->timer->start(500);
}

void MainWindow::timer_stop(){
    this->timer->stop();
    ui->ecg_graph->clear();
}

void MainWindow::image_stop(){
    startingX = 000;
    startingY = 0;
    cur_length = 1;
    cur_height = 200;
    max_length = 500;
    max_height = 200;
}

void MainWindow::update_image(){

    //ui->ecg_graph->setScaledContents(true);

    //updating starting x and y with timer, then copy and set.
    int x = origin_length;

    if(cur_length < max_length){
        cur_length+=100;
        qDebug()<<"cur length:"<<cur_length;

        qDebug()<<"cur_length <= max_length";
        x -=cur_length;

        QPixmap updated = myPixmap.copy(x,0,cur_length,cur_height);
        ui->ecg_graph->setPixmap(updated);
        qDebug()<<"updated graph from x:"<<x<<" and length of "<<cur_length;
    }else if(cur_length>max_length){

        cur_length+=100;
        qDebug()<<"cur length:"<<cur_length;

        qDebug()<<"cur_length > max_length";
        x -=cur_length;

        QPixmap updated = myPixmap.copy(x,0,max_length,max_height);
        ui->ecg_graph->setPixmap(updated);
        qDebug()<<"updated graph from x:"<<x<<" and length of "<<cur_length;

    }
}
//implementation of switch images:
//also implement the animation here
