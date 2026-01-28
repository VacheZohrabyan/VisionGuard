#-------------------------------------------------
# Project created by QtCreator
#-------------------------------------------------

QT       += core gui widgets multimedia multimediawidgets
QT += core gui multimedia widgets
TARGET = VisionGuard
TEMPLATE = app

# Միացնում ենք C++11 ստանդարտը (քանի որ Qt 5.7-ը դրա վրա է աշխատում)
CONFIG += c++11

# OpenCV-ի կարգավորումները
# Եթե libopencv-dev տեղադրված է, սա ամենաճիշտ ձևն է
INCLUDEPATH += /usr/include/opencv4

LIBS += -lopencv_core \
        -lopencv_highgui \
        -lopencv_imgproc \
        -lopencv_videoio \
        -lopencv_objdetect \
        -lopencv_imgcodecs
# Նախագծի ֆայլերը
SOURCES += main.cpp \
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

# Սա ավելացնում ենք, որպեսզի Build-ը մաքուր լինի
DESTDIR = bin
OBJECTS_DIR = obj
MOC_DIR = moc
RCC_DIR = rcc
UI_DIR = ui

