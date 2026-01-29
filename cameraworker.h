#ifndef CAMERAWORKER_H
#define CAMERAWORKER_H

#include <QObject>
#include <opencv2/opencv.hpp>
#include <QThread>
#include <QDebug>
class CameraWorker : public QObject
{
    Q_OBJECT
public:
    CameraWorker(int index);

public:
    void stop();

public slots:
    void process();

signals:
    void frameReady(const cv::Mat& frame);
    void faceDetected(const cv::Mat& face);
    void connectionLost(int index);
private:
    int camIndex;
    bool running;
};

#endif // CAMERAWORKER_H
