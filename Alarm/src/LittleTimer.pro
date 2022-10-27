lessThan(QT_MAJOR_VERSION, 5): error("need at least Qt version 5 to compile")
equals(QT_MAJOR_VERSION, 5) : lessThan(QT_MINOR_VERSION, 7) : error("need at least Qt version 5.7.x to compile")

QT          += core gui widgets

qtHaveModule(winextras) {
QT          += winextras
DEFINES     += LITTLETIMER_DO_WIN_TASKBAR_PROGRESSBAR
}

TARGET       = LittleTimer
TEMPLATE     = app
SOURCES     += main.cpp\
               mainwindow.cpp \
               simpletimer.cpp

HEADERS     += mainwindow.h \
               simpletimer.h

FORMS       += mainwindow.ui
RESOURCES   += ../resource/images.qrc
CONFIG      += c++11
