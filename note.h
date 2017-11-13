#ifndef NOTE_H
#define NOTE_H
//#include <QString>
//#include <stdio.h>
//#include <stdlib.h>
//#include <QStringList>
#include <basenote.h>
#include <iostream>

struct person
{
    QString name;
    QString surname;
    QString fathername;
    QString position;
    QString degree;
};

class Note: public BaseNote
{
public:
    QString getPersonName();
    QString getPersonSurname();
    QString getPersonFathername();
    QString getPersonPosition();
    QString getPersonDegree();
    int getVolume();
    void setPersonName(QString set_name);
    void setPersonSurname(QString set_surname);
    void setPersonFathername(QString set_fathername);
    void setPersonPosition(QString set_position);
    void setPersonDegree(QString set_degree);
    void setVolume(QString set_volume);
    Note();
    Note(const Note &copywrite);
    Note(
            QString current_hours,
            QString current_minutes,
            QString current_day,
            QString current_month,
            QString current_year,
            QString current_name,
            QString current_surname,
            QString current_fathername,
            QString current_position,
            QString current_degree,
            QString current_volume
         );
    ~Note();
    virtual int getType();
    virtual void show();
private:
    person Person;
    int volume;
};

#endif // NOTE_H
