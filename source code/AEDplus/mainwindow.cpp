#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    device *myDevice = new device;
    connect(ui->button_on,&QPushButton::pressed,myDevice,&device::debug);
    connect(ui->button_shock,&QPushButton::pressed,myDevice,&device::shock);
    connect(ui->button_good_CPR,&QPushButton::pressed,myDevice,&device::display_good_CPR_feedback);
    connect(ui->button_bad_CPR,&QPushButton::pressed,myDevice,&device::display_bad_CPR_feedback);
    connect(myDevice,&device::text_prompt_update,this,&MainWindow::update_text_prompt);



}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::update_text_prompt(QString &text){
    ui->text_prompt->setText(text);
}
/*void MainWindow::button_clicked_on(){
    emit signal1();
}*/
