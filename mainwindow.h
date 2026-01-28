#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <opencv2/opencv.hpp>
#include <QDebug>
#include <QCamera>
#include <QCamera>
#include <QCameraInfo>
#include <QCameraViewfinder>
#include <QTimer>
#include <QListWidgetItem>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    void openCamera();
    void updateFrame();
    void resizeEvent(QResizeEvent* event);

private:
    Ui::MainWindow *ui;
    QTimer* timer;
    cv::VideoCapture cap;
    cv::CascadeClassifier faseCascade;
    QListWidget *manualListFace;
};

#endif // MAINWINDOW_H
