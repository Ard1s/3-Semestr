QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11


SOURCES += \
    Board.cpp \
    Call_states.cpp \
    Click_button.cpp \
    Sapper.cpp \
    main.cpp

HEADERS += \
    Board.h \
    Call_states.h \
    Click_button.h \
    Sapper.h


RESOURCES += \
    Image.qrc
