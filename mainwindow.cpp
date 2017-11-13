#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <journal.h>
#include <note.h>
#include <QDebug>
#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    checkTimer = new QTimer;
    checkTimer->start(100);
    ui->label_27->setText(QString::fromLocal8Bit("<FONT COLOR=red>No file</FONT>"));
    ui->label_28->setText(QString::fromLocal8Bit("<FONT COLOR=red>No file</FONT>"));
    ui->label_23->setText(QString::fromLocal8Bit("<FONT COLOR=red>List is empty</FONT>"));
    ui->label_24->setText(QString::fromLocal8Bit("<FONT COLOR=red>List is empty</FONT>"));
    ui->spinBox->setMinimum(0);
    ui->spinBox->setMaximum(1000);
    ui->spinBox_4->setMinimum(0);
    ui->spinBox_4->setMaximum(1000);
    ui->spinBox_2->setMinimum(0);
    ui->spinBox_2->setMaximum(0);
    ui->spinBox_3->setMinimum(0);
    ui->spinBox_3->setMaximum(0);
    ui->pushButton->setDisabled(true);
    ui->pushButton_3->setDisabled(true);
    ui->pushButton_4->setDisabled(true);
    ui->checkBox_2->setChecked(true);
    ui->spinBox_3->setVisible(false);
    ui->pushButton_2->setVisible(false);
    QObject::connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(addNote()));
    QObject::connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(clearF()));
    QObject::connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(showNote()));
    QObject::connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(delNote()));
    QObject::connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(readFromF()));
    QObject::connect(ui->pushButton_6, SIGNAL(clicked()), this, SLOT(writeToF()));
    QObject::connect(ui->pushButton_7, SIGNAL(clicked()), this, SLOT(uploadFile()));
    QObject::connect(ui->pushButton_8, SIGNAL(clicked()), this, SLOT(randomPostAdd()));
    QObject::connect(ui->pushButton_9, SIGNAL(clicked()), this, SLOT(randomTestPostAdd()));
    QObject::connect(ui->pushButton_10, SIGNAL(clicked()), this, SLOT(changePost()));
    QObject::connect(ui->pushButton_11, SIGNAL(clicked()), this, SLOT(randomTestPostShow()));
    QObject::connect(ui->pushButton_12, SIGNAL(clicked()), this, SLOT(randomPostShow()));
    QObject::connect(ui->pushButton_13, SIGNAL(clicked()), this, SLOT(changeRandomPost()));
    QObject::connect(checkTimer, SIGNAL(timeout()), this, SLOT(checkButtons()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::uploadFile()
{
    QString rFile = QFileDialog::getOpenFileName(0, "Open Dialog", "", "*.cpp *.txt");
    ui->label_28->setText(rFile);

}

void MainWindow::clearF()
{
    ui->label_27->setText(QString::fromLocal8Bit("<FONT COLOR=red>No file</FONT>"));
    ui->pushButton_2->setVisible(false);
}

void MainWindow::changePost()
{
    int changeNumber = ui->spinBox_2->value() - 1;
    journal.deleteElement(changeNumber);
    QString str = (ui->dateTimeEdit_3->dateTime()).toString("h.m.dd.MM.yyyy");
    QStringList list1 = str.split(".");
    journal.addRegularElement(changeNumber,Note(
                           list1[0],
                           list1[1],
                           list1[2],
                           list1[3],
                           list1[4],
                           ui->lineEdit_8->text(),
                           ui->lineEdit_9->text(),
                           ui->lineEdit_10->text(),
                           ui->lineEdit_11->text(),
                           ui->lineEdit_12->text(),
                           QString::number(ui->spinBox_5->value())));
    ui->spinBox->setMinimum(-journal.getCoffeeVolume());
    ui->spinBox->setMaximum(1000-journal.getCoffeeVolume());
    showJournal();
}

void MainWindow::changeRandomPost()
{
    int changeNumber = ui->spinBox_2->value() - 1;
    journal.deleteElement(changeNumber);
    QString str = (ui->dateTimeEdit_3->dateTime()).toString("h.m.dd.MM.yyyy");
    QStringList list1 = str.split(".");
    journal.addTestElement(changeNumber, TestNote(
                           list1[0],
                           list1[1],
                           list1[2],
                           list1[3],
                           list1[4],
                           QString::number(ui->spinBox_6->value())));
    showJournal();
}

void MainWindow::addNote()
{
    if(ui->label_27->text() != "No file")
        journal.readFromF(ui->label_27->text());
    if(!(ui->lineEdit_1->text()==""||
        ui->lineEdit_2->text()==""||
        ui->lineEdit_3->text()==""||
        ui->lineEdit_4->text()==""||
        ui->lineEdit_5->text()=="") &&
        ui->toolBox->widget(0)->isVisible())
    {
        int addNumber;
        if(ui->checkBox_2->isChecked())
            addNumber = journal.size();
        else
            addNumber = ui->spinBox_3->value() - 1;
        QString str = (ui->dateTimeEdit->dateTime()).toString("h.m.dd.MM.yyyy");
        QStringList list1 = str.split(".");
        journal.addRegularElement(addNumber, Note(
                           list1[0],
                           list1[1],
                           list1[2],
                           list1[3],
                           list1[4],
                           ui->lineEdit_1->text(),
                           ui->lineEdit_2->text(),
                           ui->lineEdit_3->text(),
                           ui->lineEdit_4->text(),
                           ui->lineEdit_5->text(),
                           QString::number(ui->spinBox->value())));
    }
    if(ui->toolBox->widget(1)->isVisible())
    {
        QString str = (ui->dateTimeEdit_2->dateTime()).toString("h.m.dd.MM.yyyy");
        QStringList list1 = str.split(".");
        TestNote testNote(
                        list1[0],
                    list1[1],
                    list1[2],
                    list1[3],
                    list1[4],
                    QString::number(ui->spinBox_4->value()));
        journal.addTestElement(0, testNote);
        if(journal.getIsCorrect())
        {
            //Qdialog
            QString str = "Volume of coffee was " + QString::number(testNote.getCountOfCoffee());
            dialog = new Dialog(ui->dateTimeEdit_2->dateTime(), str);
            dialog->show();
        }
        else
        {
            QString str = "Volume of coffee was not " + QString::number(testNote.getCountOfCoffee());
            dialog = new Dialog(ui->dateTimeEdit_2->dateTime(), str);
            dialog->show();
        }
    }
    ui->spinBox->setMinimum(-journal.getCoffeeVolume());
    ui->spinBox->setMaximum(1000-journal.getCoffeeVolume());
    ui->spinBox_5->setMinimum(-journal.getCoffeeVolume());
    ui->spinBox_5->setMaximum(1000-journal.getCoffeeVolume());
    ui->spinBox_2->setMinimum(1);
    ui->spinBox_2->setMaximum(journal.size());
    ui->spinBox_3->setMinimum(1);
    ui->spinBox_3->setMaximum(journal.size());
    ui->label_23->setText(QString::fromLocal8Bit("<FONT COLOR=green>List is not empty</FONT>"));
    ui->label_24->setText(QString::fromLocal8Bit("<FONT COLOR=green>List is not empty</FONT>"));
    ui->label_26->setText(QString::number(journal.getCoffeeVolume()));
    showJournal();
}

void MainWindow::delNote()
{
    int delNumber = ui->spinBox_2->value() - 1;
    journal.deleteElement(delNumber);
    ui->spinBox_2->setMaximum(journal.size());
    ui->spinBox_3->setMaximum(journal.size());
    showJournal();
}

void MainWindow::showNote()
{
    Note * note;
    TestNote * testNote;
    int showmentNumber = ui->spinBox_2->value() - 1;
    if(journal.mass[showmentNumber]->getType() == 1)
    {

        note = dynamic_cast<Note*>(journal.mass[showmentNumber]);
        ui->lineEdit_8->setText(note->getPersonName());
        ui->lineEdit_9->setText(note->getPersonSurname());
        ui->lineEdit_10->setText(note->getPersonFathername());
        ui->lineEdit_11->setText(note->getPersonPosition());
        ui->lineEdit_12->setText(note->getPersonDegree());
        QString timeString = QString::number(note->getDateHours()) + "." +
                QString::number(note->getDateMinutes()) + "." +
                QString::number(note->getDateDay()) + "." +
                QString::number(note->getDateMonth()) + "." +
                QString::number(note->getDateYear());
        ui->dateTimeEdit_3->setDateTime(QDateTime::fromString(timeString, "h.m.dd.MM.yyyy"));
        ui->spinBox_5->setValue(note->getVolume());

    }
    else
    {
        testNote = dynamic_cast<TestNote*>(journal.mass[showmentNumber]);
        QString timeString = QString::number(testNote->getDateHours()) + "." +
                QString::number(testNote->getDateMinutes()) + "." +
                QString::number(testNote->getDateDay()) + "." +
                QString::number(testNote->getDateMonth()) + "." +
                QString::number(testNote->getDateYear());
        ui->dateTimeEdit_4->setDateTime(QDateTime::fromString(timeString, "h.m.dd.MM.yyyy"));
        ui->spinBox_6->setValue(testNote->getCountOfCoffee());
    }
}

void MainWindow::showJournal()
{
    Note * note;
    TestNote * testNote;
    int showmentNumber = journal.size();
    ui->tableWidget->clear();
    ui->tableWidget->setRowCount(journal.size());
    ui->tableWidget->setColumnCount(9);
    ui->tableWidget->setHorizontalHeaderItem(0, new QTableWidgetItem(QString::fromLocal8Bit("Date")));
    ui->tableWidget->setHorizontalHeaderItem(1, new QTableWidgetItem(QString::fromLocal8Bit("Time")));
    ui->tableWidget->setHorizontalHeaderItem(2, new QTableWidgetItem(QString::fromLocal8Bit("Name")));
    ui->tableWidget->setHorizontalHeaderItem(3, new QTableWidgetItem(QString::fromLocal8Bit("Surname")));
    ui->tableWidget->setHorizontalHeaderItem(4, new QTableWidgetItem(QString::fromLocal8Bit("Fathername")));
    ui->tableWidget->setHorizontalHeaderItem(5, new QTableWidgetItem(QString::fromLocal8Bit("Position")));
    ui->tableWidget->setHorizontalHeaderItem(6, new QTableWidgetItem(QString::fromLocal8Bit("Degree")));
    ui->tableWidget->setHorizontalHeaderItem(7, new QTableWidgetItem(QString::fromLocal8Bit("Volume on coffe")));
    ui->tableWidget->setHorizontalHeaderItem(8, new QTableWidgetItem(QString::fromLocal8Bit("Current volume of coffee")));
    for(int i = 0; i < showmentNumber; i++)
    {
        if(journal.mass[i]->getType())
        {
            note = dynamic_cast<Note*>(journal.mass[i]);
            QString time = QString::number(note->getDateHours()) + "." + QString::number(note->getDateMinutes());
            ui->tableWidget->setItem(i, 0 , new QTableWidgetItem(time));
            QString date = QString::number(note->getDateDay()) + "." + QString::number(note->getDateMonth()) + "." + QString::number(note->getDateYear());
            ui->tableWidget->setItem(i, 1 , new QTableWidgetItem(date));
            QString name = note->getPersonName();
            ui->tableWidget->setItem(i, 2 , new QTableWidgetItem(name));
            QString surname = note->getPersonSurname();
            ui->tableWidget->setItem(i, 3 , new QTableWidgetItem(surname));
            QString fathername = note->getPersonFathername();
            ui->tableWidget->setItem(i, 4 , new QTableWidgetItem(fathername));
            QString position = note->getPersonPosition();
            ui->tableWidget->setItem(i, 5 , new QTableWidgetItem(position));
            QString degree = note->getPersonDegree();
            ui->tableWidget->setItem(i, 6 , new QTableWidgetItem(degree));
            QString volume = QString::number(note->getVolume());
            ui->tableWidget->setItem(i, 7 , new QTableWidgetItem(volume));
            ui->tableWidget->setItem(i, 8 , new QTableWidgetItem("none"));
        }
        else
        {
            testNote = dynamic_cast<TestNote*>(journal.mass[i]);
            QString time = QString::number(testNote->getDateHours()) + "." + QString::number(testNote->getDateMinutes());
            ui->tableWidget->setItem(i, 0 , new QTableWidgetItem(time));
            QString date = QString::number(testNote->getDateDay()) + "." + QString::number(testNote->getDateMonth()) + "." + QString::number(testNote->getDateYear());
            ui->tableWidget->setItem(i, 1 , new QTableWidgetItem(date));
            ui->tableWidget->setItem(i, 2 , new QTableWidgetItem("none"));
            ui->tableWidget->setItem(i, 3 , new QTableWidgetItem("none"));
            ui->tableWidget->setItem(i, 4 , new QTableWidgetItem("none"));
            ui->tableWidget->setItem(i, 5 , new QTableWidgetItem("none"));
            ui->tableWidget->setItem(i, 6 , new QTableWidgetItem("none"));
            ui->tableWidget->setItem(i, 7 , new QTableWidgetItem("none"));
            QString volumeOfCup = QString::number(testNote->getCountOfCoffee());
            ui->tableWidget->setItem(i, 8 , new QTableWidgetItem(volumeOfCup));
        }
    }
}

void MainWindow::readFromF()
{
    QString rFile = QFileDialog::getOpenFileName(0, "Open Dialog", "", "*.cpp *.txt");
    ui->label_27->setText(rFile);
    ui->pushButton_2->setVisible(true);
}

void MainWindow::writeToF()
{
    if(ui->label_28->text() != "No file")
        journal.writeToF(ui->label_28->text());
}

void MainWindow::randomPostAdd()
{
    ui->lineEdit_1->clear();
    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();
    ui->lineEdit_4->clear();
    ui->lineEdit_5->clear();
    QString names[10] = {
            "Artem", "Igor", "Georgiy",
            "Maria", "Elizabeta", "Pavel",
            "Daniil", "Andrey", "Aleksandr", "Katelynn"
        };
    ui->lineEdit_1->setText(names[ qrand() % 10 ]);

    QString surnames[10] = {
            "Avdeev", "Li", "Klenevskiy",
            "Dudkina", "Frolova", "Kolesnik",
            "Volchkov", "Smolnikov", "Bondarevskiy", "Raley"
        };
    ui->lineEdit_2->setText(surnames[ qrand() % 10 ]);

    QString fathernames[10] = {
            "Artemovich", "Igorevich", "Georgievich",
            "Olegovna", "Joshovna", "Pavlovich",
            "Daniilovich", "Andreevich", "Aleksandrovich", "Chemodanovich"
        };
    ui->lineEdit_3->setText(fathernames[ qrand() % 10 ]);
    QString position[6] = {
            "Director", "HR-manager", "IT-director",
            "Consulting", "Merchendaizer", "Casher"
        };
    ui->lineEdit_4->setText(position[ qrand() % 6 ]);
    QString degree[4] = {
            "Doctor", "Scientist", "Student",
            "Bacaluvr"
        };
    ui->lineEdit_5->setText(degree[ qrand() % 4 ]);
    int hours = 0 + qrand() % (23 - 0);
    int minutes = 0 + qrand() % (59 - 0);
    int day = 1 + qrand() % (31 - 1);
    int month = 1 + qrand() % (12 - 1);
    int year = 2000 + qrand() % (2018 - 2000);
    QString timeString = QString::number(hours) + "." +
            QString::number(minutes) + "." +
            QString::number(day) + "." +
            QString::number(month) + "." +
            QString::number(year);
    ui->dateTimeEdit->setDateTime(QDateTime::fromString(timeString, "h.m.dd.MM.yyyy"));
    ui->spinBox->setValue(-journal.getCoffeeVolume() + qrand() % (1000));
}

void MainWindow::randomPostShow()
{
    ui->lineEdit_8->clear();
    ui->lineEdit_9->clear();
    ui->lineEdit_10->clear();
    ui->lineEdit_11->clear();
    ui->lineEdit_12->clear();
    QString names[10] = {
            "Artem", "Igor", "Georgiy",
            "Maria", "Elizabeta", "Pavel",
            "Daniil", "Andrey", "Aleksandr", "Katelynn"
        };
    ui->lineEdit_8->setText(names[ qrand() % 10 ]);

    QString surnames[10] = {
            "Avdeev", "Li", "Klenevskiy",
            "Dudkina", "Frolova", "Kolesnik",
            "Volchkov", "Smolnikov", "Bondarevskiy", "Raley"
        };
    ui->lineEdit_9->setText(surnames[ qrand() % 10 ]);

    QString fathernames[10] = {
            "Artemovich", "Igorevich", "Georgievich",
            "Olegovna", "Joshovna", "Pavlovich",
            "Daniilovich", "Andreevich", "Aleksandrovich", "Chemodanovich"
        };
    ui->lineEdit_10->setText(fathernames[ qrand() % 10 ]);
    QString position[6] = {
            "Director", "HR-manager", "IT-director",
            "Consulting", "Merchendaizer", "Casher"
        };
    ui->lineEdit_11->setText(position[ qrand() % 6 ]);
    QString degree[4] = {
            "Doctor", "Scientist", "Student",
            "Bacaluvr"
        };
    ui->lineEdit_12->setText(degree[ qrand() % 4 ]);
    int hours = 0 + qrand() % (23 - 0);
    int minutes = 0 + qrand() % (59 - 0);
    int day = 1 + qrand() % (31 - 1);
    int month = 1 + qrand() % (12 - 1);
    int year = 2000 + qrand() % (2018 - 2000);
    QString timeString = QString::number(hours) + "." +
            QString::number(minutes) + "." +
            QString::number(day) + "." +
            QString::number(month) + "." +
            QString::number(year);
    ui->dateTimeEdit_3->setDateTime(QDateTime::fromString(timeString, "h.m.dd.MM.yyyy"));
    ui->spinBox_5->setValue(-journal.getCoffeeVolume() + qrand() % (1000));
}

void MainWindow::randomTestPostAdd()
{
    int hours = 0 + qrand() % (23 - 0);
    int minutes = 0 + qrand() % (59 - 0);
    int day = 1 + qrand() % (31 - 1);
    int month = 1 + qrand() % (12 - 1);
    int year = 2000 + qrand() % (2018 - 2000);
    QString timeString = QString::number(hours) + "." +
            QString::number(minutes) + "." +
            QString::number(day) + "." +
            QString::number(month) + "." +
            QString::number(year);
    ui->dateTimeEdit_2->setDateTime(QDateTime::fromString(timeString, "h.m.dd.MM.yyyy"));
    ui->spinBox_4->setValue(1000 + qrand() % (1000));
}

void MainWindow::randomTestPostShow()
{
    int hours = 0 + qrand() % (23 - 0);
    int minutes = 0 + qrand() % (59 - 0);
    int day = 1 + qrand() % (31 - 1);
    int month = 1 + qrand() % (12 - 1);
    int year = 2000 + qrand() % (2018 - 2000);
    QString timeString = QString::number(hours) + "." +
            QString::number(minutes) + "." +
            QString::number(day) + "." +
            QString::number(month) + "." +
            QString::number(year);
    ui->dateTimeEdit_4->setDateTime(QDateTime::fromString(timeString, "h.m.dd.MM.yyyy"));
    ui->spinBox_6->setValue(1000 + qrand() % (1000));
}

void MainWindow::checkButtons()
{
    if(ui->checkBox_2->isChecked())
        ui->spinBox_3->setVisible(false);
    else
        ui->spinBox_3->setVisible(true);
    if(ui->label_27->text() == "No file")
        ui->pushButton_2->setDisabled(true);
    else
        ui->pushButton_2->setDisabled(false);
    if(
            ((ui->lineEdit_1->text()==""||
            ui->lineEdit_2->text()==""||
            ui->lineEdit_3->text()==""||
            ui->lineEdit_4->text()==""||
            ui->lineEdit_5->text()=="") && (ui->label_27->text() == "No file")) ||
            !(ui->toolBox->widget(1)->isVisible() ||
             ui->toolBox->widget(0)->isVisible())
            )
        ui->pushButton->setDisabled(true);
    else
        ui->pushButton->setDisabled(false);
    if(
            ui->lineEdit_8->text()==""||
            ui->lineEdit_9->text()==""||
            ui->lineEdit_10->text()==""||
            ui->lineEdit_11->text()==""||
            ui->lineEdit_12->text()==""||
            journal.size() == 0
            )
        ui->pushButton_10->setDisabled(true);
    else
        ui->pushButton_10->setDisabled(false);
    if(journal.size() > 0)
    {
        ui->pushButton_3->setDisabled(false);
        ui->pushButton_4->setDisabled(false);
        ui->tabWidget->widget(1)->setDisabled(false);
    }
    else if(journal.size() == 0)
    {
        ui->pushButton_3->setDisabled(true);
        ui->pushButton_4->setDisabled(true);
        ui->label_23->setText(QString::fromLocal8Bit("<FONT COLOR=red>List is empty</FONT>"));
        ui->label_24->setText(QString::fromLocal8Bit("<FONT COLOR=red>List is empty</FONT>"));
        ui->tabWidget->widget(1)->setDisabled(true);
    }
    if(ui->label_28->text() == "No file")
        ui->pushButton_6->setDisabled(true);
    else
        ui->pushButton_6->setDisabled(false);
}
