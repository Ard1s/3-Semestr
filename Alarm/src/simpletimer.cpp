#include <limits> 
#include <cmath> 

#include "simpletimer.h"
#include "mainwindow.h"

#include <QMessageBox>
#include <QTime>

#ifdef LITTLETIMER_DO_WIN_TASKBAR_PROGRESSBAR
#include <QWinTaskbarButton>
#include <QWinTaskbarProgress>
#endif /* LITTLETIMER_DO_WIN_TASKBAR_PROGRESSBAR */

SimpleTimer::SimpleTimer(const Ui::MainWindow * const ui, MainWindow * const mainwindow) : myTimer(this), myProgressBarUpdateTimer(this) 
{
    running = false;

    myTimer.setSingleShot(true); 
    connect(&myTimer, &QTimer::timeout, this, &SimpleTimer::stopStuff); 
    connect(&myTimer, &QTimer::timeout, this, &SimpleTimer::timerFired); 

    myProgressBarUpdateTimer.setSingleShot(false); 
    myProgressBarUpdateTimer.setInterval(1000); 
    connect(&myProgressBarUpdateTimer, &QTimer::timeout, this, &SimpleTimer::updateProgressBar);   

    theMainWindow = mainwindow;
    theLineEdit = ui->lineEdit;
    thePushButton = ui->pushButton;
    theComboBox = ui->comboBox;
    theProgressBar = ui->progressBar;
}

void SimpleTimer::updateProgressBar() const 
{
    const double percent = 100.0 * myTimer.remainingTime();
    const int value = static_cast<int>(nearbyint(percent));
    theProgressBar->setValue(value);

#ifdef LITTLETIMER_DO_WIN_TASKBAR_PROGRESSBAR
    wintaskprogress->setValue(value);
#endif /* LITTLETIMER_DO_WIN_TASKBAR_PROGRESSBAR */

    if(myTimer.remainingTime() > 60000) 
    { // >1min
        myFactorString = "min";

        if(myTimer.remainingTime() > 60000 * 5) 
        { // >5min
            myRemainingTimeString.setNum(ceil(myTimer.remainingTime() / 60000.), 'f', 0); 
        } 
        else 
        { // <=5min and >1min
            myRemainingTimeString.setNum(myTimer.remainingTime() / 60000., 'f', 1); 
        }
    } else 
    {
        myFactorString = "sec";
        myRemainingTimeString.setNum(myTimer.remainingTime() / 1000., 'f', 0); 
    }

    theProgressBar->setFormat(myRemainingTimeString + myFactorString);

    if(theMainWindow->myTray->isVisible()) 
    {
        theMainWindow->myTray->setToolTip(theMainWindow->windowTitle() + ": " + myRemainingTimeString + myFactorString);
    }
}

void SimpleTimer::startStuff() 
{
    running = true;

    thePushButton->setText(tr("Stop"));
    theLineEdit->setDisabled(true);
    theComboBox->setDisabled(true);
    theProgressBar->setEnabled(true);

#ifdef LITTLETIMER_DO_WIN_TASKBAR_PROGRESSBAR

    if(wintasbarbutton.window() == Q_NULLPTR) 
    {
        wintasbarbutton.setWindow(theMainWindow->windowHandle());
        wintaskprogress = wintasbarbutton.progress();
    }

    wintaskprogress->show();
#endif /* LITTLETIMER_DO_WIN_TASKBAR_PROGRESSBAR */

    myTimer.start();
    myProgressBarUpdateTimer.start();
    updateProgressBar(); 
}

void SimpleTimer::stopStuff() 
{
    myTimer.stop();
    myProgressBarUpdateTimer.stop();

#ifdef LITTLETIMER_DO_WIN_TASKBAR_PROGRESSBAR
    wintaskprogress->hide();
#endif /* LITTLETIMER_DO_WIN_TASKBAR_PROGRESSBAR */

    running = false;

    thePushButton->setText(tr("Start"));
    theLineEdit->setDisabled(false);
    theComboBox->setDisabled(false);
    theProgressBar->setEnabled(false);
    theProgressBar->setValue(0);
    theProgressBar->setFormat("");
}

void SimpleTimer::timerFired() const 
{
    theMainWindow->myTray->setToolTip(""); 
    theMainWindow->showNormal(); 

    QMessageBox msg(QMessageBox::Warning, tr("Attention"), tr("Alarm: ") + theMainWindow->windowTitle(), QMessageBox::Ok, thePushButton);
    msg.setWindowModality(Qt::WindowModal);
    msg.exec();
}

void SimpleTimer::startStopTimer() 
{
    if(running) 
    {
        stopStuff();
    } else 
      {
        const QString inputString = theLineEdit->text().replace(',', '.');
        const QStringList captures = QRegularExpression("^(\\d{1,2}):(\\d{1,2})$").match(inputString).capturedTexts();
        int newInterval;

        
        if(captures.length() == 3) 
       {
            const QTime timeInput = QTime(captures.at(1).toInt(), captures.at(2).toInt());

            if(!timeInput.isValid()) 
            {
                QMessageBox::warning(thePushButton->parentWidget(), tr("Attention"), tr("Invalid input time (format: HH:MM)."));
                return;
            }

            newInterval = -timeInput.msecsTo(QTime::currentTime());

            if(newInterval < 0) 
            {
                newInterval += 24 * 60 * 60 * 1000;
            }
        } else {
            unsigned long factor = 0; 

            switch(static_cast<conversion_factor>(theComboBox->currentIndex())) {
                case conversion_factor::ms:
                    factor = 1;
                    break;

                case conversion_factor::sec:
                    factor = 1000;
                    break;

                case conversion_factor::min:
                    factor = 1000 * 60;
                    break;

                case conversion_factor::h:
                    factor = 1000 * 60 * 60;
                    break;
            }

            
            bool conversionOkay;
            const double input = inputString.toDouble(&conversionOkay);  

            // Test 
            if(!conversionOkay || input * factor > std::numeric_limits<int>::max() || input <= 0.) 
            {
                QMessageBox::warning(thePushButton->parentWidget(), tr("Attention"), tr("Invalid input! Must be a positive number, which can't be too big (max 596h)."));
                return;
            }

            newInterval = static_cast<int>(input * factor);
        }

        myTimer.setInterval(newInterval);  
        startStuff();
    }
}
