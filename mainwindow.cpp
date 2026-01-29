#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QWidget *central = new QWidget(this);
    this->setCentralWidget(central);

    QGridLayout* mainLayout = new QGridLayout(central);
    central->setLayout(mainLayout);
    mainLayout->setSpacing(10);
    mainLayout->setContentsMargins(10, 10, 10, 10);

    this->setStyleSheet("MainWindow { "
                        "border-image: /home/user/Pictures/tenc"
                        "}");

    manualListFace = new QListWidget(this);
    manualListFace->setGeometry(10, 450, 600, 150);
    manualListFace->setViewMode(QListView::IconMode);
    manualListFace->setIconSize(QSize(100, 100));

    mainLayout->addWidget(manualListFace, 2, 0, 1, 2);

    for (int i = 0; i < DEFAULT_CAMERA_SIZE; ++i)
    {
        CameraWidget* cameraView = new CameraWidget(this);
        mainLayout->addWidget(cameraView, i / 2, i % 2);
        cameraViews.push_back(cameraView);
        cameraView->showNoSignal(i);
    }
    startThreads();
}

MainWindow::~MainWindow()
{
    delete timer;
    delete ui;
}

void MainWindow::startThreads()
{
    for (int i = 0; i < DEFAULT_CAMERA_SIZE; ++i)
    {
        QThread* thread = new QThread(this);
        CameraWorker* worker = new CameraWorker(i); // camIndex = i
        worker->moveToThread(thread);

        connect(worker, &CameraWorker::frameReady, cameraViews[i], &CameraWidget::updateView);

        connect(worker, &CameraWorker::faceDetected, this, [this](cv::Mat faceROI){
            if (faceROI.empty()) return;

            cv::Mat rgbFace;
            cv::cvtColor(faceROI, rgbFace, cv::COLOR_BGR2RGB);

            QImage img((const unsigned char*)rgbFace.data, rgbFace.cols, rgbFace.rows, rgbFace.step, QImage::Format_RGB888);
            QListWidgetItem* item = new QListWidgetItem(QIcon(QPixmap::fromImage(img.copy())), "Detected");

            if (manualListFace) {
                manualListFace->insertItem(0, item);
                if (manualListFace->count() > 50) delete manualListFace->takeItem(50);
            }
        });

        connect(worker, &CameraWorker::connectionLost, cameraViews[i], [this, i](){
            cameraViews[i]->showNoSignal(i);
        });

        connect(thread, &QThread::started, worker, &CameraWorker::process);
        connect(thread, &QThread::finished, worker, &QObject::deleteLater);

        thread->start();
    }
}
