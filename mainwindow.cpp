#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setStyleSheet("MainWindow { "
                        "border-image: /home/user/Pictures/tenc"
                        "}");

    manualListFace = new QListWidget(this);
    manualListFace->setGeometry(10, 450, 600, 150);
    manualListFace->setViewMode(QListView::IconMode);
    manualListFace->setIconSize(QSize(100, 100));
    openCamera();
}

MainWindow::~MainWindow()
{
    delete timer;
    delete ui;
}

void MainWindow::openCamera()
{
    faseCascade.load("/usr/share/opencv4/haarcascades/haarcascade_frontalface_default.xml");
    if (!cap.open(0))
    {
        qDebug() << "failed to open camera";
        return ;
    }
    cap.set(cv::CAP_PROP_FRAME_WIDTH, 1280);
    cap.set(cv::CAP_PROP_FRAME_HEIGHT, 720);
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::updateFrame);
    timer->start(30);
}

void MainWindow::updateFrame()
{
    cv::Mat frame, gray;
    cap >> frame;

    if (!frame.empty())
    {
        static int frameCounter = 0;
        frameCounter++;

        cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);
        cv::equalizeHist(gray, gray);

        std::vector<cv::Rect> faces;
        faseCascade.detectMultiScale(gray, faces, 1.1, 8, 0, cv::Size(80, 80));

        for (const auto& face: faces)
        {
            cv::rectangle(frame, face, cv::Scalar(0, 255, 0), 2);
            cv::Mat faceROI = frame(face).clone();
            if (frameCounter % 30 == 0)
            {
                cv::cvtColor(faceROI, faceROI, cv::COLOR_BGR2RGB);
                QImage faceImage((const unsigned char*)faceROI.data, faceROI.cols, faceROI.rows, faceROI.step, QImage::Format_RGB888);
                QIcon faceIcon(QPixmap::fromImage(faceImage.copy()));
                /*QListWidgetItem * item = new QListWidgetItem(faceIcon, QString::asprintf("face %d", ui->listFace->count() + 1));
                ui->listFace->insertItem(0, item);*/
                QListWidgetItem* item = new QListWidgetItem(faceIcon, "Face");
                manualListFace->insertItem(0, item);
            }
        }

        cv::cvtColor(frame, frame, cv::COLOR_BGR2RGB);
        QImage qimeg((const unsigned char*)(frame.data), frame.cols, frame.rows, frame.step, QImage::Format_RGB888);
        ui->labelView->setPixmap(QPixmap::fromImage(qimeg).scaled(
            this->width(),
            this->height(),
            Qt::IgnoreAspectRatio, // Սա կստիպի նկարին ամբողջությամբ լցնել էկրանը
            Qt::SmoothTransformation
        ));
    }
}

void MainWindow::resizeEvent(QResizeEvent* event)
{
    QMainWindow::resizeEvent(event);
    // Սա ստիպում է labelView-ին զբաղեցնել ամբողջ հասանելի տարածքը
    ui->labelView->setGeometry(0, 0, this->width(), this->height());
}
