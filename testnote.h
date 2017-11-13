#ifndef TESTNOTE_H
#define TESTNOTE_H
#include <QString>
#include <stdio.h>
#include <stdlib.h>
#include <QStringList>
#include <QString>

#include <iostream>
#include <basenote.h>

class TestNote: public BaseNote
{
public:
    TestNote();
    TestNote(const TestNote &copywrite);
    TestNote(
            QString current_hours,
            QString current_minutes,
            QString current_day,
            QString current_month,
            QString current_year,
            QString current_countOfCoffee
            );
    ~TestNote();
    int getCountOfCoffee();
    void setCountOfCoffee(QString setmentCountOfCoffee);
    virtual int getType();
    virtual void show();
protected:
    int countOfCoffee;
};

#endif // TESTNOTE_H
