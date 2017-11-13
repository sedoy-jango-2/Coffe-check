#include "testnote.h"
//#include <iostream>
//#include <QRegExp>
#include <journal.h>

int TestNote::getType()
{
    return 0;
}

int TestNote::getCountOfCoffee()
{
    return (this->countOfCoffee);
}

void TestNote::setCountOfCoffee(QString setmentCountOfCoffee)
{
    QRegExp checkpoint("\\d+");
    if(
         checkpoint.exactMatch(setmentCountOfCoffee)&&
            setmentCountOfCoffee.toInt() >= 0 &&
            setmentCountOfCoffee.toInt() <= 1000
         )
        countOfCoffee = setmentCountOfCoffee.toInt();
    else
    {
        countOfCoffee = TestNote().countOfCoffee;
    }
}


TestNote::TestNote():BaseNote()
{
    countOfCoffee = 0;
}

TestNote::TestNote(
        QString current_hours, QString current_minutes,
        QString current_day, QString current_month,
        QString current_year, QString current_countOfCoffee
        ):BaseNote(current_hours,
                   current_minutes,
                   current_day,
                   current_month,
                   current_year
                   )
{
    TestNote::setDateHours(current_hours);
    TestNote::setDateMinutes(current_minutes);
    TestNote::setDateDay(current_day);
    TestNote::setDateMonth(current_month);
    TestNote::setDateYear(current_year);
    TestNote::setCountOfCoffee(current_countOfCoffee);
}

TestNote::TestNote(const TestNote &copywrite): BaseNote(copywrite)
{
    countOfCoffee = copywrite.countOfCoffee;
}

void TestNote::show()
{
    std::cout <<"|=======================|\n";
    std::cout << "Hours: " << this->getDateHours() << "\n";
    std::cout << "Minutes: " << this->getDateMinutes() << "\n";
    std::cout << "Day: " << this->getDateDay() << "\n";
    std::cout << "Month: " << this->getDateMonth() << "\n";
    std::cout << "Year: " << this->getDateYear() << "\n";
    std::cout << "Count Of Coffee: " << this->getCountOfCoffee() << "\n";
    std::cout <<"|=======================|\n";

}

TestNote::~TestNote()
{

}
