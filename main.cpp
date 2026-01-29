#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qRegisterMetaType<cv::Mat>("cv::Mat");
    MainWindow w;
    w.show();

    cv::Mat test = cv::Mat::zeros(2160, 3840, CV_8UC1);
    qDebug() << "OPencv works" << test.cols << "x" << test.rows;

    return a.exec();
}
