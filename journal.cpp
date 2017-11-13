#include "journal.h"
#include <iostream>
#include <fstream>

Journal::Journal()
{
    sizeOfMass = 2;
    currentSize = 0;
    coffeeValume = 0;
    cupValue = 1000;
    isCorrect = false;
    mass = new BaseNote* [sizeOfMass];
}

Journal::Journal(const Journal &copywrite)
{
    sizeOfMass = copywrite.sizeOfMass;
    currentSize = copywrite.currentSize;
    for(int i = 1; i <= copywrite.currentSize; i++)
    {
        mass[i] = copywrite.mass[i];
    }
}

bool Journal::isEmpty()
{
    if(size() != 0)
        {
            return false;
        }
        else
        {
            return true;
        }
}

int Journal::coffeeSize(int currentValume)
{
    if (coffeeValume + currentValume < 0)
        return 0;
    else if(coffeeValume + currentValume > cupValue)
    {
        return cupValue;
    }
    else
        return coffeeValume += currentValume;
}

void Journal::setIsCorrect(TestNote note)
{
    int coffeeSizeInTime = 0;
    QDateTime noteDateTime = QDateTime::fromString(QString::number(note.getDateYear()) + "." +
            QString::number(note.getDateMonth()) + "." +
            QString::number(note.getDateDay()) + "." +
            QString::number(note.getDateHours()) + "." +
            QString::number(note.getDateMinutes()), "yyyy.MM.dd.h.m");
    for(int i = 0; i < size(); i++)
    {
        if(mass[i]->getType())
        {
            Note * currentNote = dynamic_cast<Note*>(mass[i]);
            QDateTime currentNumber = QDateTime::fromString(QString::number(currentNote->getDateYear()) + "." +
                    QString::number(currentNote->getDateMonth()) + "." +
                    QString::number(currentNote->getDateDay()) + "." +
                    QString::number(currentNote->getDateHours()) + "." +
                    QString::number(currentNote->getDateMinutes()), "yyyy.MM.dd.h.m");
            if(currentNumber < noteDateTime)
            {
                coffeeSizeInTime += currentNote->getVolume();
            }
        }

    }
    isCorrect = (coffeeSizeInTime = this->coffeeValume);
}

int Journal::getCoffeeVolume()
{
    return (this->coffeeValume);
}

bool Journal::getIsCorrect()
{
    return (this->isCorrect);
}

int Journal::size()
{
    return (this->currentSize);
}

void Journal::resize()
{
    BaseNote **reserve, **old = mass;
    reserve = new BaseNote*[this->sizeOfMass*2];
    for(int i = 0; i<this->sizeOfMass; i++)
        reserve [i] = mass[i];
    delete [] old;
    mass = reserve;
    sizeOfMass *= 2;
}

void Journal::deleteElement(int index)
{
    if(!mass[index]->getType())
    {
        Note * note;
        note = dynamic_cast<Note*>(mass[index]);
        coffeeValume = coffeeSize(-note->getVolume());
    }
    delete mass[index];
    for(int countDeleteNumber = index; countDeleteNumber < size(); countDeleteNumber++)
        this->mass[countDeleteNumber] = this->mass[countDeleteNumber + 1];
    currentSize--;
}

void Journal::addTestElement(int index, TestNote addElement)
{
    mass[currentSize] = NULL;
    currentSize++;
    if(size() == sizeOfMass)
        resize();
    for(int countAddNumber = size(); countAddNumber > index; countAddNumber--)
    {
        this->mass[countAddNumber] = this->mass[countAddNumber - 1];
    }
    this->mass[index] = new TestNote(addElement);
    setIsCorrect(addElement);
}

void Journal::addRegularElement(int index, Note addElement)
{
    mass[currentSize] = NULL;
    currentSize++;
    if(size() == sizeOfMass)
        resize();
    for(int countAddNumber = size(); countAddNumber > index; countAddNumber--)
    {
        this->mass[countAddNumber] = this->mass[countAddNumber - 1];
    }
    this->mass[index] = new Note(addElement);
    coffeeValume = coffeeSize(addElement.getVolume());
}

BaseNote &Journal::operator[](int i)
{
    return *mass[i];
}

void Journal::readFromF(QString fName)
{
    QFile file;
    file.setFileName(fName);
    file.open(QIODevice::ReadOnly);
    int counter = size();
    while(!file.atEnd())
    {
        QRegExp checkpoint("\\d+");
        QString currentHours = file.readLine();
        QString currentMinutes =file.readLine();
        QString currentDay = file.readLine();
        QString currentMonth = file.readLine();
        QString currentYear = file.readLine();
        QString currentStr = file.readLine();
        currentStr.remove("\r\n");
        currentStr.remove("\n");
        if(checkpoint.exactMatch(currentStr))
        {
            QString countOfCoffee = currentStr;
            currentHours.remove("\r\n");
            currentHours.remove("\n");
            currentMinutes.remove("\r\n");
            currentMinutes.remove("\n");
            currentDay.remove("\r\n");
            currentDay.remove("\n");
            currentMonth.remove("\r\n");
            currentMonth.remove("\n");
            currentYear.remove("\r\n");
            currentYear.remove("\n");
            countOfCoffee.remove("\r\n");
            countOfCoffee.remove("\n");
            TestNote a(currentHours,
                   currentMinutes,
                   currentDay,
                   currentMonth,
                   currentYear,
                   countOfCoffee);
            addTestElement(counter, a);
        }
        else
        {
            QString currentName = currentStr;
            QString currentSurname = file.readLine();
            QString currentFathername = file.readLine();
            QString currentPosition = file.readLine();
            QString currentDegree = file.readLine();
            QString currentVolume = file.readLine();
            currentHours.remove("\r\n");
            currentHours.remove("\n");
            currentMinutes.remove("\r\n");
            currentMinutes.remove("\n");
            currentDay.remove("\r\n");
            currentDay.remove("\n");
            currentMonth.remove("\r\n");
            currentMonth.remove("\n");
            currentYear.remove("\r\n");
            currentYear.remove("\n");
            currentName.remove("\r\n");
            currentName.remove("\n");
            currentSurname.remove("\r\n");
            currentSurname.remove("\n");
            currentFathername.remove("\r\n");
            currentFathername.remove("\n");
            currentPosition.remove("\r\n");
            currentPosition.remove("\n");
            currentDegree.remove("\r\n");
            currentDegree.remove("\n");
            currentVolume.remove("\r\n");
            currentVolume.remove("\n");
            Note a(currentHours,
                   currentMinutes,
                   currentDay,
                   currentMonth,
                   currentYear,
                   currentName,
                   currentSurname,
                   currentFathername,
                   currentPosition,
                   currentDegree,
                   currentVolume);
            addRegularElement(counter, a);
        }

        counter+=1;
    }
    file.close();
}

void Journal::writeToF(QString fname)
{

    QFile file1;
    file1.setFileName(fname);
    file1.open(QIODevice::WriteOnly);
    QTextStream stream(&file1);
    for(int i = 0; i<size(); i++)
    {
        if(this->mass[i]->getType() == 1)
        {
            Note *note = dynamic_cast<Note*>(this->mass[i]);
            stream<<QString::number(note->getDateHours())+"\r\n"+
                QString::number(note->getDateMinutes())+"\r\n"+
                QString::number(note->getDateDay())+"\r\n"+
                QString::number(note->getDateMonth())+"\r\n"+
                QString::number(note->getDateYear())+"\r\n"+
                note->getPersonName()+"\r\n"+
                note->getPersonSurname()+"\r\n"+
                note->getPersonFathername()+"\r\n"+
                note->getPersonPosition()+"\r\n"+
                note->getPersonDegree()+"\r\n"+
                QString::number(note->getVolume())+"\r\n";
        }
        else
        {
            TestNote *testNote = dynamic_cast<TestNote*>(this->mass[i]);
            stream<<QString::number(testNote->getDateHours())+"\r\n"+
                QString::number(testNote->getDateMinutes())+"\r\n"+
                QString::number(testNote->getDateDay())+"\r\n"+
                QString::number(testNote->getDateMonth())+"\r\n"+
                QString::number(testNote->getDateYear())+"\r\n"+
                QString::number(testNote->getCountOfCoffee())+"\r\n";
        }
    }
    file1.close();
}
void Journal::show(int i)
{
    this->mass[i]->show();
}

Journal::~Journal()
{
    for(int i = 0; i < size(); i++)
        delete mass[i];
    delete [] mass;
}
