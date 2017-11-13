#include "note.h"

int Note::getType()
{
    return 1;
}

QString Note::getPersonName()
{
    return (this->Person.name);
}

void Note::setPersonName(QString set_name)
{
    if(set_name.length() != 0 && !set_name.contains("/n", Qt::CaseInsensitive))
        Person.name = set_name;
    else
    {
        Person.name = Note().Person.name;
    }
}

QString Note::getPersonSurname()
{
    return (this->Person.surname);
}

void Note::setPersonSurname(QString set_surname)
{
    if(set_surname.length() != 0 && !set_surname.contains("/n", Qt::CaseInsensitive))
        Person.surname = set_surname;
    else
    {
        Person.surname = Note().Person.surname;
    }
}

QString Note::getPersonFathername()
{
    return (this->Person.fathername);
}

void Note::setPersonFathername(QString set_fathername)
{
    if(set_fathername.length() != 0 && !set_fathername.contains("/n", Qt::CaseInsensitive))
        Person.fathername = set_fathername;
    else
    {
        Person.fathername = Note().Person.fathername;
    }
}

QString Note::getPersonPosition()
{
    return (this->Person.position);
}

void Note::setPersonPosition(QString set_position)
{
    if(set_position.length() != 0 && !set_position.contains("/n", Qt::CaseInsensitive))
        Person.position = set_position;
    else
    {
        Person.position = Note().Person.position;
    }
}

QString Note::getPersonDegree()
{
    return (this->Person.degree);
}

void Note::setPersonDegree(QString set_degree)
{
    if(set_degree.length() != 0 && !set_degree.contains("/n", Qt::CaseInsensitive))
        Person.degree = set_degree;
    else
    {
        Person.degree = Note().Person.degree;
    }
}

void Note::setVolume(QString set_volume)
{
//    QRegExp checkpoint1("\\d*");
//    if(checkpoint1.exactMatch(set_volume))
        this->volume = set_volume.toInt();
//    else
//    {
//        this->volume = Note().volume;
//    }
}

int Note::getVolume()
{
    return (this->volume);
}

void Note::show()
{
    std::cout <<"|=======================|\n";
    std::cout << "Hours: " << this->getDateHours() << "\n";
    std::cout << "Minutes: " << this->getDateMinutes() << "\n";
    std::cout << "Day: " << this->getDateDay() << "\n";
    std::cout << "Month: " << this->getDateMonth() << "\n";
    std::cout << "Year: " << this->getDateYear() << "\n";
    std::cout << "Name: " << this->getPersonName().toAscii().data() << "\n";
    std::cout << "Surname: " << this->getPersonSurname().toAscii().data() << "\n";
    std::cout << "Fathername: " << this->getPersonFathername().toAscii().data() << "\n";
    std::cout << "Position: " << this->getPersonPosition().toAscii().data() << "\n";
    std::cout << "Degree: " << this->getPersonDegree().toAscii().data() << "\n";
    std::cout << "Volume: " << this->getVolume() << "\n";
    std::cout <<"|=======================|\n";

}

Note::Note() : BaseNote ()
{
    Person.name = "none";
    Person.surname = "none";
    Person.fathername = "none";
    Person.position = "none";
    Person.degree = "none";
    volume = 0;
}

Note::Note(
        QString current_hours, QString current_minutes,
        QString current_day, QString current_month,
        QString current_year, QString current_name, QString current_surname,
        QString current_fathername, QString current_position,
        QString current_degree,QString current_volume)
     :BaseNote(current_hours,
               current_minutes,
               current_day,
               current_month,
               current_year
               )
{
    Note::setDateHours(current_hours);
    Note::setDateMinutes(current_minutes);
    Note::setDateDay(current_day);
    Note::setDateMonth(current_month);
    Note::setDateYear(current_year);
    Note::setPersonName(current_name);
    Note::setPersonSurname(current_surname);
    Note::setPersonFathername(current_fathername);
    Note::setPersonPosition(current_position);
    Note::setPersonDegree(current_degree);
    Note::setVolume(current_volume);
}

Note::Note(const Note &copywrite): BaseNote(copywrite)
{
    Person.name = copywrite.Person.name;
    Person.surname = copywrite.Person.surname;
    Person.fathername = copywrite.Person.fathername;
    Person.position = copywrite.Person.position;
    Person.degree = copywrite.Person.degree;
    volume = copywrite.volume;
}

Note::~Note()
{

}



