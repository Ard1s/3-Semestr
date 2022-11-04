#ifndef SIMPLETIMER_H
#define SIMPLETIMER_H

#include <QTimer>

#include "ui_mainwindow.h"

#ifdef LITTLETIMER_DO_WIN_TASKBAR_PROGRESSBAR
#include <QWinTaskbarButton>
#include <QWinTaskbarProgress>
#endif /* LITTLETIMER_DO_WIN_TASKBAR_PROGRESSBAR */

class MainWindow;

enum class conversion_factor { ms, sec, min, h };

class SimpleTimer : public QObject {
        Q_OBJECT

    private:
        mutable QString myFactorString;  ("min"/"sec")
        mutable QString myRemainingTimeString; // "6" "6min"
        MainWindow *theMainWindow;
        QPushButton *thePushButton;
        QLineEdit *theLineEdit;
        QComboBox *theComboBox;
        QProgressBar *theProgressBar;
        QTimer myTimer; 
        QTimer myProgressBarUpdateTimer; 
#ifdef LITTLETIMER_DO_WIN_TASKBAR_PROGRESSBAR
        QWinTaskbarButton wintasbarbutton;
        QWinTaskbarProgress *wintaskprogress;
#endif /* LITTLETIMER_DO_WIN_TASKBAR_PROGRESSBAR */
        void startStuff(); 

    public:
        bool running; 
        SimpleTimer(const Ui::MainWindow * const ui, MainWindow * const mainwindow);  

    public slots:
        void stopStuff(); 
        void timerFired() const; 
        void updateProgressBar() const; 
        void startStopTimer(); 
};

#endif // SIMPLETIMER_H
