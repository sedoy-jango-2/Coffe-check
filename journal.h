#ifndef JOURNAL_H
#define JOURNAL_H
#include "basenote.h"
#include "note.h"
#include "testnote.h"
#include <QFile>
#include <QString>
#include <QTextStream>
#include <QDateTime>

class Journal
{
public:
    Journal();
    Journal(const Journal &copywrite);
    BaseNote ** mass;
    BaseNote &operator[](int i);
    int size();
    void deleteElement(int index);
    void addTestElement(int index, TestNote addElement);
    void addRegularElement(int index, Note addElement);
    void readFromF(QString nameOfFile);
    void writeToF(QString fname);
    void show(int i);
    bool isEmpty();
    bool getIsCorrect();
    int getCoffeeVolume();
    void setIsCorrect(TestNote note);
    ~Journal();
private:
    bool isCorrect;
    int coffeeValume;
    int cupValue;
    int sizeOfMass;
    int currentSize;
    void resize();
    int coffeeSize(int currentValume);
};



#endif // JOURNAL_H
