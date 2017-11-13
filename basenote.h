#ifndef BASENOTE_H
#define BASENOTE_H
#include <QString>
#include <QRegExp>
#include <stdio.h>
#include <stdlib.h>
#include <QStringList>
#include <iostream>

struct date
{
    int hours;
    int minutes;
    int day;
    int month;
    int year;
};

class BaseNote
{
public:
    BaseNote();
    BaseNote(const BaseNote &copywrite);
    BaseNote(
            QString current_hours,
            QString current_minutes,
            QString current_day,
            QString current_month,
            QString current_year
            );

    int getDateHours();
    int getDateMinutes();
    int getDateDay();
    int getDateMonth();
    int getDateYear();
    void setDateHours(QString set_hours);
    void setDateMinutes(QString set_minutes);
    void setDateDay(QString set_day);
    void setDateMonth(QString set_month);
    void setDateYear(QString set_year);
    virtual int getType();
    virtual void show() = 0;
    ~BaseNote();
protected:
    date Date;
};

#endif // BASENOTE_H
