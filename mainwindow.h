#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <note.h>
#include <testnote.h>
#include <journal.h>
#include <QTimer>
#include <QtGlobal>
#include <QDateTime>
#include <QFileDialog>
#include <dialog.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
private:
    Ui::MainWindow *ui;
    Journal journal;
    QTimer *checkTimer;
    Dialog *dialog;
private slots:
    void addNote();
    void delNote();
    void showNote();
    void showJournal();
    void clearF();
    void randomTestPostAdd();
    void randomTestPostShow();
    void readFromF();
    void writeToF();
    void randomPostAdd();
    void randomPostShow();
    void checkButtons();
    void changePost();
    void changeRandomPost();
    void uploadFile();
};

#endif // MAINWINDOW_H
