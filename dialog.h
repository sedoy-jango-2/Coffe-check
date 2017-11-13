#ifndef DIALOG_H
#define DIALOG_H
#include <QDateTime>
#include <QDialog>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit Dialog(QWidget *parent = 0);
    Dialog(QDateTime dateTime, QString str);
    ~Dialog();
    
private:
    Ui::Dialog *ui;
};

#endif // DIALOG_H
