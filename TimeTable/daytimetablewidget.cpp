#include "daytimetablewidget.h"
#include <QLabel>
#include <QDate>
#include <QDebug>
#include <QMessageBox>
#include <QHeaderView>
#include <QObject>
#include <QAction>
#include <QMenu>
#include <QSignalMapper>

#include "definitions.h"

const int DayTimeTableWidget::EVENT_COUNT = 8;
const int DayTimeTableWidget::MINIMUM_HEIGHT = 240;

DayTimeTableWidget::DayTimeTableWidget( int dayNumber,QWidget *parent) :
    QGroupBox(parent),
    dayNumber_( dayNumber)
{
    tableWidget_ = new QTableWidget( this);
    tableWidget_->setColumnCount(8);
    QStringList headerLabels;
    headerLabels << "Время" << "Неделя" << "Название" << "Тип занятия" << "Место занятия" << "Фамилия "<< "Имя" << "Отчество";
    tableWidget_->setHorizontalHeaderLabels( headerLabels);

    nameLabel_ = new QLabel( QDate::longDayName( dayNumber+1), this);

    addTaskButton_ = new QPushButton( QString::fromUtf8("Добавить пару"), this);

    mainLayout_ = new QVBoxLayout(this);
    mainLayout_->addWidget( nameLabel_);
    mainLayout_->addWidget( addTaskButton_);
    mainLayout_->addWidget( tableWidget_);
    connect( addTaskButton_, SIGNAL(clicked()), this, SLOT(addTask()));
    setAutoFillBackground(true);

    setMinimumHeight( MINIMUM_HEIGHT);

    tableWidget_->verticalHeader()->setContextMenuPolicy(Qt::CustomContextMenu);

    connect(tableWidget_->verticalHeader(), SIGNAL(customContextMenuRequested(QPoint)),
    SLOT(customMenuRequested(QPoint)));
}

void DayTimeTableWidget::addTask()
{
    int currentRow = tableWidget_->rowCount();
    tableWidget_->insertRow( currentRow);

    QComboBox* eventTimeComboBox;
    QComboBox* weekComboBox;
    QLineEdit* eventNameLineEdit;
    QComboBox* eventTypeComboBox;
    QLineEdit* eventLocationLineEdit;
    QLineEdit* teacherNameLineEdit;
    QLineEdit* teacherLastNameLineEdit;
    QLineEdit* teacherSureNameLineEdit;

    weekComboBox = new QComboBox( this);
    QStringList weekList;
    weekList << "1" << "2" << "Все";
    weekComboBox->addItems( weekList);

    eventNameLineEdit = new QLineEdit( this);

    eventTimeComboBox = new QComboBox( this);
    QStringList timeList;
    for( int i = 1; i <= EVENT_COUNT; i++)
    {
        switch( i)
            {
                case 1:
                    timeList << QString::number( i) + " " + "08:00 - 09:30";
                    break;

                case 2:
                    timeList << QString::number( i) + " " + "09:40 - 11:10";
                    break;

                case 3:
                    timeList << QString::number( i) + " " + "11:20 - 12:50";
                    break;

                case 4:
                    timeList << QString::number( i) + " " + "13:15 - 14:45";
                    break;

                case 5:
                    timeList << QString::number( i) + " " + "15:00 - 16:30";
                    break;

                case 6:
                    timeList << QString::number( i) + " " + "16:40 - 18:10";
                    break;

                case 7:
                    timeList << QString::number( i) + " " + "18:20 - 19:50";
                    break;
                case 8:
                    timeList << QString::number( i) + " " + "19:55 - 21:25";
                    break;
            }
    }
    eventTimeComboBox->addItems( timeList);

    eventTypeComboBox = new QComboBox( this);
    QStringList typeList;
    typeList << "Лекция" << "Практика" << "Собрание СССУ" << "Экзмен/Зачет";
    eventTypeComboBox->addItems( typeList);

    eventLocationLineEdit = new QLineEdit( this);

    teacherNameLineEdit = new QLineEdit( this);
    teacherLastNameLineEdit = new QLineEdit( this);
    teacherSureNameLineEdit = new QLineEdit( this);

    tableWidget_->setCellWidget( currentRow,0,eventTimeComboBox);
    tableWidget_->setCellWidget( currentRow,1,weekComboBox);
    tableWidget_->setCellWidget( currentRow,2,eventNameLineEdit);
    tableWidget_->setCellWidget( currentRow,3,eventTypeComboBox);
    tableWidget_->setCellWidget( currentRow,4,eventLocationLineEdit);
    tableWidget_->setCellWidget( currentRow,5,teacherLastNameLineEdit);
    tableWidget_->setCellWidget( currentRow,6,teacherNameLineEdit);
    tableWidget_->setCellWidget( currentRow,7,teacherSureNameLineEdit);
    tableWidget_->resizeRowsToContents();
    tableWidget_->resizeColumnsToContents();
}

DayTimeTableWidget::ValueList* DayTimeTableWidget::saveTask()
{
    qDebug() << "Расписание сохранено";
    for( int i = 0; i < tableWidget_->rowCount(); i++)
    {
        ValueMapPtr valueMap = ValueMapPtr( new ValueMap);

        for( int j = 0; j < tableWidget_->columnCount(); j++)
        {
            QWidget* widget = tableWidget_->cellWidget( i, j);
            QComboBox* combo;
            QLineEdit* lineEdit;
            switch( j)
            {
            case 0:
                combo = qobject_cast<QComboBox*>(widget);
                qDebug() << QString::number(combo->currentIndex()+1);
                valueMap->insert( EVENT_TIME_KEY, QString::number(combo->currentIndex()+1));
                break;
            case 1:
                combo = qobject_cast<QComboBox*>(widget);
                qDebug() << QString::number(combo->currentIndex()+1);
                valueMap->insert( WEEK_KEY, QString::number(combo->currentIndex()+1));
                break;
            case 2:
                lineEdit = qobject_cast<QLineEdit*>(widget);
                qDebug() << lineEdit->text();
                valueMap->insert( EVENT_NAME_KEY, lineEdit->text());
                break;
            case 3:
                combo = qobject_cast<QComboBox*>(widget);
                qDebug() << QString::number(combo->currentIndex()+1);
                valueMap->insert( EVENT_TYPE_KEY, QString::number(combo->currentIndex()+1));
                break;
            case 4:
                lineEdit = qobject_cast<QLineEdit*>(widget);
                qDebug() << lineEdit->text();
                valueMap->insert( EVENT_LOCATION_KEY, lineEdit->text());
                break;
            case 5:
                lineEdit = qobject_cast<QLineEdit*>(widget);
                qDebug() << lineEdit->text();
                valueMap->insert( LAST_NAME_KEY, lineEdit->text());
                break;
            case 6:
                lineEdit = qobject_cast<QLineEdit*>(widget);
                qDebug() << lineEdit->text();
                valueMap->insert( NAME_KEY, lineEdit->text());
                break;
            case 7:
                lineEdit = qobject_cast<QLineEdit*>(widget);
                qDebug() << lineEdit->text();
                valueMap->insert( SURE_NAME_KEY, lineEdit->text());
                break;
            }
        }
        valueList_.push_back( valueMap);
    }
    return &valueList_;
}

void DayTimeTableWidget::clear()
{
    if( tableWidget_->rowCount())
    {
        while( tableWidget_->rowCount())
            tableWidget_->removeRow( 0);
    }
    valueList_.clear();
}


void DayTimeTableWidget::removeTask( int row)
{
    if( tableWidget_->rowCount())
    {
        tableWidget_->removeRow( row);
    }
    valueList_.clear();
}

void DayTimeTableWidget::customMenuRequested(QPoint pos)
{

    QModelIndex index = tableWidget_->indexAt(pos);
    qDebug() << "INDEX: " << index.row();

}
