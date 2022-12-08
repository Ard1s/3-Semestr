QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = timetable
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    timetable.cpp \
    grouptimetablewidget.cpp \
    daytimetablewidget.cpp \
    timetablefileimporter.cpp

HEADERS  += mainwindow.h \
    timetable.h \
    grouptimetablewidget.h \
    daytimetablewidget.h \
    definitions.h \
    timetablefileimporter.h






