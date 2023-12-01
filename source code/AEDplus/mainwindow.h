#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "patient.h"
#include "device.h"
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:


public slots:
    /*

    void button_clicked_goodCPR();
    void button_clicked_badCPR();
    void button_clicked_goodElectrode();
    void button_clicked_badElectrode();
    void button_clicked_shock();*/
    //void button_clicked_on();
    void update_text_prompt(const QString &text);
private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
