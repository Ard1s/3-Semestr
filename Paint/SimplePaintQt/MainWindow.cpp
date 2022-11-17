#include <QtWidgets>
#include "MainWindow.h"
#include "ScribbleArea.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    area = new ScribbleArea(this);
    setCentralWidget(area);
    resize(500, 500);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if(maybeSave()){
        event->accept();
    }else{
        event->ignore();
    }
}

bool MainWindow::maybeSave()
{
    if(area->isModify()){
        QMessageBox::StandardButton ret;
        ret = QMessageBox::warning(this, tr("Может все-таки сохранишь?"), tr("Эта картинка была изменена. \n"
                                                            "Хочешь ли сохранить ее?"),
                                   QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
        if(ret == QMessageBox::Save){
            return saveFile("png");
        }else if(ret == QMessageBox::Cancel){
            return false;
        }
    }
    return true;
}

bool MainWindow::saveFile(const QByteArray &fileFormat)
{
    QString initialPath = QDir::currentPath() + "/untitled." + fileFormat;
    QString fileName = QFileDialog::getSaveFileName(this, tr("Сохранить как.."), initialPath,
                                                    tr("%1 Files (*.%2);;All Files (*)")
                                                    .arg(QString::fromLatin1(fileFormat.toUpper()))
                                                    .arg(QString::fromLatin1(fileFormat)));
    if(fileName.isEmpty()){
        return false;
    }
    return area->saveImage(fileName, fileFormat.constData());
}


void MainWindow::on_actionOpen_triggered()
{
    if(maybeSave()){
        QString fileName = QFileDialog::getOpenFileName(this, tr("Открыть файл"), QDir::currentPath());
        if(!fileName.isEmpty()){
            area->openImage(fileName);
        }
    }
}


void MainWindow::on_actionSave_triggered()
{
    QByteArray format = QImageWriter::supportedImageFormats().at(0);
    saveFile(format);
}


void MainWindow::on_actionColor_triggered()
{
    QColor color = QColorDialog::getColor(area->getPenColor());
    if(color.isValid()){
        area->setPenColor(color);
    }
}


void MainWindow::on_actionWidth_triggered()
{
    bool ok;

    auto newWidth = QInputDialog::getInt(this, tr("Толщина ручки"), tr("Выбрать толщину ручки"),area->getPenWidth(), 1, 50, 1, &ok);
    if(ok){
        area->setPenWidth(newWidth);
    }
}


void MainWindow::on_actionAbout_Qt_triggered()
{
    QMessageBox::aboutQt(this);
}

