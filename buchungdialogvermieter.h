#ifndef BUCHUNGDIALOGVERMIETER_H
#define BUCHUNGDIALOGVERMIETER_H

#include <QDialog>
#include "buchungsverwaltung.h"
#include "person.h"

namespace Ui {
class BuchungDialogVermieter;
}

class BuchungDialogVermieter : public QDialog
{
    Q_OBJECT

public:
    explicit BuchungDialogVermieter(Person *, Buchung *, Buchungsverwaltung *, QWidget *parent = nullptr);
    ~BuchungDialogVermieter();
    QString print_info();

private:
    Ui::BuchungDialogVermieter *ui;
    Person *person;
    Buchung *akt_buchung;
    Buchungsverwaltung *verwaltung;

private slots:
    void pushButton_bestaetigen_clicked();
    void pushButton_ablehnen_clicked();
    void pushButton_rechnung_clicked();
};

#endif // BUCHUNGDIALOGVERMIETER_H
