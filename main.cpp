#include <QtGui/QApplication>
#include "mainwindow.h"
#include <stdio.h>
#include <iostream>
#include "journal.h"
#include <cassert>

QString checkFileName()
{
    QString fname;
    std::string str;
    while(!QFile::exists(fname))
    {
        std::cout <<"Input name of file to read:\n";
        std::getline(std::cin, str);
        fname = QString::fromStdString(str);
    }
    return fname;
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
//    QString fname1;
//    QString fname2;
//    Journal b;
//    Journal t;
//    int coffee;
//    int k = 2;
//    int current_hour;
//    Note *test_data = new Note("12",
//                   "30",
//                   "1",
//                   "11",
//                   "2000",
//                   "Avdeev",
//                   "Artem",
//                   "Sergeevich",
//                   "dhdrh",
//                   "Student",
//                   "5");
//    TestNote *test_data2= new TestNote("12",
//                   "30",
//                   "1",
//                   "11",
//                   "2000",
//                   "11");
//    Journal a;
//    //----------------------
//    assert(a.isEmpty());
//    assert(a.size() == 0);
//    for(int i = 0; i < k + 1; i++)
//    {
//       a.addElement(i , test_data);
//    }
//    b = a;
//    assert(a.mass[0]->getDateDay() == b.mass[0]->getDateDay());
//    assert(!a.isEmpty());
//    assert(a.size() == k + 1);
//    //----------------------
//    fname1 = checkFileName();
//    t.readFromF(fname1);
//    for(int i = 0; i < t.size(); i++)
//    {
//        t.show(i);
//        coffee += t.mass[i]->getVolume();
//    }
//    current_hour = t.size();
//    assert(t.getCoffeeVolume() != coffee);
//    t.deleteElement(k);
//    assert(t.size() == current_hour - 1);
//    for(int i = 0; i < t.size(); i++)
//        t.show(i);
//    fname2 = checkFileName();
//    t.writeToF(fname2);
//    a.addElement(0, test_data2);
//    for(int i = 0; i < a.size(); i++)
//        a.show(i);
}
