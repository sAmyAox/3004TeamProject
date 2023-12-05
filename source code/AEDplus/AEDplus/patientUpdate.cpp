#include "patient.h"
#include "ui_mainwindow.h"  // Assuming this is the correct UI file for your MainWindow
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>

patient::patient()
{
    vf = false;
    heart_rate = 0;
    // vt = false;
    shocked = false;

    // Create a QTimer for updating ECG images
    ecgTimer = new QTimer(this);
    connect(ecgTimer, SIGNAL(timeout()), this, SLOT(updateECG()));
    ecgTimer->start(1000);  // Set the interval in milliseconds (adjust as needed)

    // Assuming you have a QGraphicsScene to display images
    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
}

patient::~patient()
{
    // Clean up resources
    delete ui;
    delete ecgTimer;
    delete scene;
}

void patient::set_status(){
    this->shocked = true;
    qDebug()<<"set shocked to true";

    // Implement logic to cycle through ECG images based on patient's status
    if (vf)
    {
        // Update ECG for ventricular fibrillation
        qDebug() << "Updating ECG for ventricular fibrillation";
    }
    else if (heart_rate > 120)
    {
        // Update ECG for ventricular tachycardia
        qDebug() << "Updating ECG for ventricular tachycardia";
    }
    else if (shocked)
    {
        // Update ECG for normal rhythm after shock
        qDebug() << "Updating ECG for normal rhythm after shock";
    }
    else
    {
        // Update ECG for other cases
        qDebug() << "Updating ECG for other cases";
    }
}

void patient::updateECG()
{
    QImage ecgImage;
    int heart_rate = 110;
    bool shocked=false;

    if (true)
    {
        // Load image for ventricular fibrillation
        ecgImage.load("vf.jpg");
    }
    else if (heart_rate > 120)
    {
        // Load image for ventricular tachycardia
        ecgImage.load(":/path/to/vt_image.png");
    }
    else if (shocked)
    {
        // Load image for normal rhythm after shock
        ecgImage.load(":/path/to/normal_image.png");
    }
    else
    {
        // Load image for other cases
        ecgImage.load(":/path/to/default_image.png");
    }

    // Convert QImage to QPixmap
    QPixmap pixmap = QPixmap::fromImage(ecgImage);

    // Clear the scene before adding a new image
    scene->clear();

    // Add the new image to the scene
    QGraphicsPixmapItem* item = new QGraphicsPixmapItem(pixmap);
    scene->addItem(item);

    // Set the loaded image to the QGraphicsView
    // ui->graphicsView->setScene(scene);
    // ui->graphicsView->show();
}
