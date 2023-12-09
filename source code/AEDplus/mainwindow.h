#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "device.h"
#include <QTimer>
#include <QPixmap>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void select_image();

signals:



public slots:
   
    void update_text_prompt(const QString &text);
    void update_text_CPR(const QString &text);
    void update_text_status(const QString &text);
    void update_battery_label();
    void battery_shut_down();
    void update_image();
    void timer_start();
    void timer_stop();
    void image_stop();
    void input_patient();
    void vf_true_input();
    void vf_false_input();

private:
    Ui::MainWindow *ui;
    device *myDevice ;
    QPixmap myPixmap;
    QTimer *timer;
    int startingX;
    int startingY;
    int cur_length;
    int cur_height;
    int max_length;
    int max_height;
    int origin_length;

};
#endif // MAINWINDOW_H
