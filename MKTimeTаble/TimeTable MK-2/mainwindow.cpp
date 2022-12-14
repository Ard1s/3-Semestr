#include "mainwindow.h"

#include <QMenuBar>
#include <QKeySequence>
#include <QFileDialog>
#include <QMessageBox>

#include "timetable.h"
#include "timetablefileimporter.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("Расписание ЧелГу для МК-2");

    timetable_ = new TimeTable( "Расписание",this);
    groupWidget_ = new GroupTimeTableWidget( timetable_, this);

    menu_ = new QMenu( QString::fromUtf8("Меню"), this);

    QKeySequence saveKeySequence = Qt::CTRL + Qt::Key_S;
    QKeySequence clearKeySequence = Qt::CTRL + Qt::Key_Q;
    QKeySequence importKeySequence = Qt::CTRL + Qt::Key_I;

    saveAction_ = new QAction( QString::fromUtf8("Сохранить занятие"), this);
    clearAction_ = new QAction( QString::fromUtf8("Очистить"), this);
    importAction_ = new QAction( QString::fromUtf8("Импортировать из файла"), this);

    saveAction_->setShortcut( saveKeySequence);
    clearAction_->setShortcut( clearKeySequence);
    importAction_->setShortcut( importKeySequence);

    menu_->addAction( saveAction_);
    menu_->addAction( clearAction_);
    menu_->addAction( importAction_);

    menuBar()->addMenu( menu_);

    scrollArea_ = new QScrollArea();
    scrollArea_->setWidget( groupWidget_);
    scrollArea_->setWidgetResizable(true);

    setCentralWidget( scrollArea_);
    resize( 1200, 800);

    scrollArea_->setMinimumSize( size());

    connect( saveAction_, SIGNAL(triggered()), groupWidget_, SLOT(saveTask()));
    connect( clearAction_, SIGNAL(triggered()), groupWidget_, SLOT(clearAll()));
    connect( importAction_, SIGNAL(triggered()), this, SLOT(chooseImportFile()));
}

MainWindow::~MainWindow()
{}

void MainWindow::resizeEvent(QResizeEvent* event)
{
    QMainWindow::resizeEvent(event);
}

void MainWindow::chooseImportFile()
{
    QString filename =
            QFileDialog::getOpenFileName( this, QString::fromUtf8("Выберите файл для импорта расписания"), "", "Text Files(*.*)");
    if( !filename.isEmpty())
    {
        TimetableFileImporter importer( timetable_, this);
        importer.import( filename);
        QMessageBox::information( this, QString::fromUtf8("Импорт"),
                                  QString::fromUtf8("Импорт успешно завершен"));
    }
}
