#include "cameraworker.h"

CameraWorker::CameraWorker(int index) : camIndex(index), running(true)
{

}
void CameraWorker::process()
{
    cv::VideoCapture cap;

    if (!cap.open(camIndex, cv::CAP_V4L2)) {
        qDebug() << "Cannot open camera with Index:" << camIndex;
        emit connectionLost(camIndex);
        return;
    }

    cap.set(cv::CAP_PROP_FRAME_WIDTH, 640);
    cap.set(cv::CAP_PROP_FRAME_HEIGHT, 360);
    cap.set(cv::CAP_PROP_FPS, 30);

    if (!cap.isOpened()) {
        qDebug() << "Camera is NOT opened at index:" << camIndex;
        emit connectionLost(camIndex);
        return;
    }

    qDebug() << "Camera started successfully at index:" << camIndex;

    cv::CascadeClassifier faceCascade;
    if (!faceCascade.load("/usr/share/opencv4/haarcascades/haarcascade_frontalface_default.xml")) {
        // Եթե Cascade-ը չբեռնվեց, գոնե տեսանյութը ցույց տանք առանց դեմքի
    }

    int frameCounter = 0;
    while (running)
    {
        cv::Mat frame, gray, smallFrame;
        cap >> frame;

        if (!frame.empty())
        {
            frameCounter++;

            cv::resize(frame, smallFrame, cv::Size(640, 360));

            if (!faceCascade.empty())
            {
                cv::cvtColor(smallFrame, gray, cv::COLOR_BGR2GRAY);
                cv::equalizeHist(gray, gray);

                std::vector<cv::Rect> faces;
                faceCascade.detectMultiScale(gray, faces, 1.1, 8, 0, cv::Size(80, 80));

                for (const auto& face : faces)
                {
                    cv::rectangle(smallFrame, face, cv::Scalar(0, 255, 0), 2);
                    if (frameCounter % 30 == 0)
                    {
                        cv::Mat faceROI = smallFrame(face).clone();
                        emit faceDetected(faceROI);
                    }
                }
            }
            emit frameReady(smallFrame.clone());
        } else {
            emit connectionLost(camIndex);
            QThread::msleep(500);
        }

        QThread::msleep(10);
    }

    cap.release();
}

void CameraWorker::stop() {
    running = false;
}


