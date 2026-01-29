#include "camerawidget.h"

CameraWidget::CameraWidget(QWidget* ptr) : QLabel(ptr)
{
    this->setMinimumSize(320, 240);
    this->setStyleSheet("border: 2px solid #333; background: black;");
    this->setScaledContents(true);
}

void CameraWidget::updateView(const cv::Mat& frame)
{
    if (frame.empty())
        return;
    cv::Mat resizedFrame;
    cv::resize(frame, resizedFrame, cv::Size(640, 360));
    cv::Mat rgbFrame;
    cv::cvtColor(resizedFrame, rgbFrame, cv::COLOR_BGR2RGB);
    QImage qimeg((const unsigned char*)(rgbFrame.data),
                 rgbFrame.cols, rgbFrame.rows,
                 rgbFrame.step, QImage::Format_RGB888);
    QPixmap pix = QPixmap::fromImage(qimeg.copy());
    if (!pix.isNull() && this->width() > 0 && this->height() > 0)
    {
        this->setPixmap(pix.scaled(this->size(),
                                   Qt::KeepAspectRatio,
                                   Qt::FastTransformation));
    }
}

void CameraWidget::showNoSignal(int camIndex)
{
    QPixmap noSignal(640, 380);
    noSignal.fill(Qt::black);

    QPainter painter(&noSignal);
    painter.setPen(Qt::white);
    painter.setFont(QFont("Arial", 20, QFont::Black));
    QString message = QString("CAMERA %1\nNO SIGNAL").arg(camIndex + 1);
    painter.drawText(noSignal.rect(), Qt::AlignCenter, message);
    painter.end();
    if (this->width() > 0 && this->height() > 0)
        this->setPixmap(noSignal.scaled(this->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
}

void CameraWidget::resizeEvent(QResizeEvent *event)
{
    QLabel::resizeEvent(event);
    if (this->pixmap() && !this->pixmap()->isNull())
        this->setPixmap(this->pixmap()->scaled(this->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
}
