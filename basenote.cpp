#include "basenote.h"

//-------virtual functions-------------
int BaseNote::getType()
{

}

//--------get and set functions-----------
int BaseNote::getDateHours()
{
    return (this->Date.hours);
}

void BaseNote::setDateHours(QString set_hours)
{
    QRegExp checkpoint("\\d+");
    if(
         checkpoint.exactMatch(set_hours) &&
         set_hours.toInt()>-1 &&
         set_hours.toInt()<24
         )
        Date.hours = set_hours.toInt();
    else
    {
        Date.hours = 0;
    }
}

int BaseNote::getDateMinutes()
{
    return (this->Date.minutes);
}

void BaseNote::setDateMinutes(QString set_minutes)
{
    QRegExp checkpoint("\\d+");
    if(
         checkpoint.exactMatch(set_minutes) &&
         set_minutes.toInt()>-1 &&
         set_minutes.toInt()<60
         )
        Date.minutes = set_minutes.toInt();
    else
    {
        Date.minutes = 0;
    }
}

int BaseNote::getDateDay()
{
    return (this->Date.day);
}

void BaseNote::setDateDay(QString set_day)
{
    QRegExp checkpoint("\\d+");
    if(
         checkpoint.exactMatch(set_day) &&
         set_day.toInt()>0 &&
         set_day.toInt()<32
         )
        Date.day = set_day.toInt();
    else
    {
        Date.day = 1;
    }
}

int BaseNote::getDateMonth()
{
    return (this->Date.month);
}

void BaseNote::setDateMonth(QString set_month)
{
    QRegExp checkpoint("\\d+");
    if(
         checkpoint.exactMatch(set_month) &&
         set_month.toInt()>0 &&
         set_month.toInt()<13
         )
        Date.month = set_month.toInt();
    else
    {
        Date.month = 1;
    }
}

int BaseNote::getDateYear()
{
    return (this->Date.year);
}

void BaseNote::setDateYear(QString set_year)
{
    QRegExp checkpoint("\\d+");
    if(
         checkpoint.exactMatch(set_year) &&
         set_year.toInt()>1975
         )
        Date.year = set_year.toInt();
    else
    {
        Date.year = 1975;
    }
}

BaseNote::BaseNote()
{
    Date.hours = 1;
    Date.minutes = 1;
    Date.day = 1;
    Date.month = 1;
    Date.year = 1975;
}
BaseNote::BaseNote(
        QString current_hours, QString current_minutes,
        QString current_day, QString current_month,
        QString current_year
        )
{
    BaseNote::setDateHours(current_hours);
    BaseNote::setDateMinutes(current_minutes);
    BaseNote::setDateDay(current_day);
    BaseNote::setDateMonth(current_month);
    BaseNote::setDateYear(current_year);
}

BaseNote::BaseNote(const BaseNote &copywrite)
{
    Date.hours = copywrite.Date.hours;
    Date.minutes = copywrite.Date.minutes;
    Date.day = copywrite.Date.day;
    Date.month = copywrite.Date.month;
    Date.year = copywrite.Date.year;
}

BaseNote::~BaseNote()
{

}
