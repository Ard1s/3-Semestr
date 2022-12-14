#include "timetablefileimporter.h"
#include <QFile>
#include <QTextStream>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>

const QString TimetableFileImporter::PAIR_FIELD = "pair";
const QString TimetableFileImporter::LASTNAME_FIELD = "lastname";
const QString TimetableFileImporter::FIRSTNAME_FIELD = "firstname";
const QString TimetableFileImporter::PATRONYMIC_FIELD = "patronymic";
const QString TimetableFileImporter::TYPE_FIELD = "type";
const QString TimetableFileImporter::TEACHER_FIELD = "teacher";
const QString TimetableFileImporter::LOCATION_FIELD = "location";
const QString TimetableFileImporter::START_TIME_FIELD = "starttime";
const QString TimetableFileImporter::TIME_FIELD = "time";
const QString TimetableFileImporter::END_TIME_FIELD = "endtime";
const QString TimetableFileImporter::WEEK_FIELD = "week";

const QString TimetableFileImporter::DAY_FIELD = "day";

const QString TimetableFileImporter::GROUP_FIELD = "group";
const QString TimetableFileImporter::WEEK_NAME = "week";

const QString TimetableFileImporter::GROUP_ID_TAG = "groupId";
const QString TimetableFileImporter::GROUP_NAME_TAG = "groupName";
const QString TimetableFileImporter::FACULTY_NAME_TAG = "facultyName";
const QString TimetableFileImporter::WARDAY_FIELD = "isWarDay";

TimetableFileImporter::TimetableFileImporter(TimeTable* timetable, QObject *parent):
    QObject(parent),
    timetable_(timetable)
{
    days_.insert( std::pair<QString, int>( QString::fromUtf8("ПН"), 0));
    days_.insert( std::pair<QString, int>( QString::fromUtf8("ВТ"), 1));
    days_.insert( std::pair<QString, int>( QString::fromUtf8("СР"), 2));
    days_.insert( std::pair<QString, int>( QString::fromUtf8("ЧТ"), 3));
    days_.insert( std::pair<QString, int>( QString::fromUtf8("ПТ"), 4));
    days_.insert( std::pair<QString, int>( QString::fromUtf8("СБ"), 5));
    days_.insert( std::pair<QString, int>( QString::fromUtf8("ВС"), 6));

    time_.insert( std::pair<QString, int>( QString::fromUtf8("8:00"), 1));
    time_.insert( std::pair<QString, int>( QString::fromUtf8("9:40"), 2));
    time_.insert( std::pair<QString, int>( QString::fromUtf8("08:00"), 1));
    time_.insert( std::pair<QString, int>( QString::fromUtf8("09:40"), 2));
    time_.insert( std::pair<QString, int>( QString::fromUtf8("11:20"), 3));
    time_.insert( std::pair<QString, int>( QString::fromUtf8("13:15"), 4));
    time_.insert( std::pair<QString, int>( QString::fromUtf8("15:00"), 5));
    time_.insert( std::pair<QString, int>( QString::fromUtf8("16:40"), 6));
    time_.insert( std::pair<QString, int>( QString::fromUtf8("18:20"), 7));
    time_.insert( std::pair<QString, int>( QString::fromUtf8("19:55"), 8));

    type_.insert( std::pair<QString, int>( QString::fromUtf8("лек"), 1));
    type_.insert( std::pair<QString, int>( QString::fromUtf8("Лекция"), 1));
    type_.insert( std::pair<QString, int>( QString::fromUtf8("пр"), 2));
    type_.insert( std::pair<QString, int>( QString::fromUtf8("Практика"), 2));
}

void TimetableFileImporter::import( QString filename)
{
    QFile textFile( filename, this);
    QString jsonData;
    bool ret = textFile.open(QIODevice::ReadOnly | QIODevice::Text);
    if( ret)
    {
        QTextStream in(&textFile);
        jsonData = in.readAll();
    }

    QJsonDocument timeTable = QJsonDocument::fromJson( jsonData.toUtf8());
    QJsonArray jsonArray = timeTable.array();

    foreach (const QJsonValue & value, jsonArray)
    {
        QJsonObject groupTimeTable = value.toObject();
        QString groupName = groupTimeTable[GROUP_FIELD].toString();

        int week = 3;
        if( groupTimeTable[WEEK_FIELD].toString() != "" )
            week = groupTimeTable[WEEK_FIELD].toString().toInt();

        int eventTimeNumber = time_[groupTimeTable[TIME_FIELD].toString()];

        QString eventName = groupTimeTable[PAIR_FIELD].toString();

        int eventType = 1;
        if( groupTimeTable[TYPE_FIELD].toString() != "" )
            eventType = type_[groupTimeTable[TYPE_FIELD].toString()];

        QString location;
        if( groupTimeTable[WARDAY_FIELD].toBool())
        {
            location = QString::fromUtf8("ИВО");
        }
        else
            location = groupTimeTable[LOCATION_FIELD].toString();

        int day = days_[groupTimeTable[DAY_FIELD].toString()];

        QString teacher = groupTimeTable[TEACHER_FIELD].toString();
        QString teacherLastName = teacher;
        QString teacherFirstName;
        QString teacherSureName;

        qDebug() << teacher;

        int ptFirstPos = teacher.indexOf( ".");
        if( ptFirstPos != -1)
        {
            teacherLastName= teacher.mid( 0, ptFirstPos-1);
            int spacePos = teacherLastName.indexOf( " ");
            if( spacePos != -1)
            {
                teacherLastName = teacherLastName.mid( 0, teacherLastName.length()-1);
            }
            qDebug() << teacherLastName;

            teacherFirstName = teacher.mid( ptFirstPos - 1, 2);
            qDebug() << teacherFirstName;

            if( teacher.indexOf( ".", ptFirstPos+1) != -1)
                teacherSureName = teacher.right(2);

            qDebug() << teacherSureName;
        }
        timetable_->
                addEvent( groupName, week, eventTimeNumber, eventName, eventType, location, day, teacherFirstName,teacherLastName,teacherSureName);
    }
}



