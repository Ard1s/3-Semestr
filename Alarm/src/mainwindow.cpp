#include "mainwindow.h"
#include "simpletimer.h"

#include <QInputDialog>
#include <QScreen>

unsigned long MainWindow::currentNumWindows = 0; 
unsigned long MainWindow::theWindowID = 0;
QIcon MainWindow::theIcon; 

MainWindow::MainWindow(const QString &windowTitle, QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    theWindowID++;
    currentNumWindows++;

    ui->setupUi(this);  
    myTimer = new SimpleTimer(ui, this);  
    myTrayMenu = new QMenu();
    myTrayMenu->addAction(windowTitle)->setDisabled(true); 
    myTrayMenu->addSeparator();
    myTrayMenu->addAction(tr("Restore timer"), this, &MainWindow::showNormal);
    myTrayMenu->addAction(tr("Create new timer"), this, &MainWindow::pushButton_2_clicked);
    myTrayMenu->addAction(tr("Close timer"), this, &MainWindow::close);

    myTray = new QSystemTrayIcon(theIcon); 
    myTray->hide();
    myTray->setContextMenu(myTrayMenu);

    connect(myTray, &QSystemTrayIcon::activated, this, &MainWindow::tray_clicked); 
    connect(ui->pushButton, &QPushButton::clicked, myTimer, &SimpleTimer::startStopTimer);
    connect(ui->pushButton_2, &QPushButton::clicked, this, &MainWindow::pushButton_2_clicked);
    connect(ui->lineEdit, &QLineEdit::textChanged, this, &MainWindow::lineEdit_textEdited);
    connect(ui->lineEdit, &QLineEdit::returnPressed, myTimer, &SimpleTimer::startStopTimer);

    this->setWindowTitle(windowTitle);
    this->move(QGuiApplication::primaryScreen()->geometry().center() - this->geometry().center()); 
    this->setWindowIcon(theIcon); 
    this->setAttribute(Qt::WA_DeleteOnClose, true); 
}

MainWindow::~MainWindow() {
    delete myTray;
    delete myTrayMenu;
    delete myTimer;
    delete ui;
}

void MainWindow::tray_clicked(QSystemTrayIcon::ActivationReason reason) {
    if(reason == QSystemTrayIcon::Context) {
        myTray->show();
    } else if(reason == QSystemTrayIcon::DoubleClick) {
        showNormal(); 
    }
}

void MainWindow::lineEdit_textEdited(const QString &arg1) const {
    ui->pushButton->setEnabled(arg1.length() > 0); 
    ui->comboBox->setVisible(!arg1.contains(":"));
}

void MainWindow::closeEvent(QCloseEvent *) {
    isClosed = true;  
    myTray->hide(); 

    currentNumWindows--;

    if(!currentNumWindows) {
        QApplication::quit();
    }
}

void MainWindow::hideEvent(QHideEvent *) {
    if(!isClosed && QSystemTrayIcon::isSystemTrayAvailable()) {
        myTray->show();
        this->hide();
    }
}

void MainWindow::showEvent(QShowEvent *) {
    myTray->hide();
    this->show();
    this->activateWindow();
    this->raise();
}

void MainWindow::pushButton_2_clicked() const {
    QString tempWindowTitle = tr("Little Timer ") + QString::number(theWindowID);

    if(QGuiApplication::keyboardModifiers() & Qt::ShiftModifier) {
        QInputDialog dialog;
        dialog.setWindowTitle(tr("Custom Name"));
        dialog.setLabelText(tr("Set the name of the new timer:"));
        dialog.setTextValue(tempWindowTitle);
        dialog.setWindowIcon(theIcon);

        if(dialog.exec() == QDialog::Accepted) {
            tempWindowTitle = dialog.textValue();
        } else {
            return;
        }
    }

    MainWindow *w = new MainWindow(tempWindowTitle); 
    w->show();
}
