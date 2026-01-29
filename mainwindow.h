#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <opencv2/opencv.hpp>
#include <QDebug>
#include <QCamera>
#include <QCamera>
#include <QLabel>
#include <QCameraInfo>
#include <QCameraViewfinder>
#include <QTimer>
#include <QListWidgetItem>
#include <QGridLayout>

#include "camerawidget.h"
#include "cameraworker.h"

#define DEFAULT_CAMERA_SIZE 6

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public:
    void startThreads();

private:
    Ui::MainWindow *ui;
    QTimer* timer;
    std::vector<CameraWidget*> cameraViews;
    std::vector<cv::VideoCapture> cap;
    cv::CascadeClassifier faseCascade;
    QListWidget *manualListFace;
};

#endif // MAINWINDOW_H
