#ifndef CAMERAWIDGET_H
#define CAMERAWIDGET_H

#include <QLabel>
#include <opencv2/opencv.hpp>
#include <QPainter>

class CameraWidget : public QLabel
{
    Q_OBJECT
public:
    explicit CameraWidget(QWidget* ptr = nullptr);

public:
    void updateView(const cv::Mat& frame);
    void showNoSignal(int camIndex);
    void resizeEvent(QResizeEvent *event);

private:

};

#endif // CAMERAWIDGET_H
