#ifndef BUCHUNGDIALOGMIETER_H
#define BUCHUNGDIALOGMIETER_H

#include <QDialog>
#include "buchungsverwaltung.h"
#include "person.h"

namespace Ui {
class BuchungDialogMieter;
}

class BuchungDialogMieter : public QDialog
{
    Q_OBJECT

public:
    explicit BuchungDialogMieter(Person *, Buchung *, Buchungsverwaltung *, QWidget *parent = nullptr);    //, Buchung * (Eingabeparameter fehlt)
    ~BuchungDialogMieter();
    QString print_info();

private:
    Ui::BuchungDialogMieter *ui;
    Person *person;
    Buchung *akt_buchung;
    Buchungsverwaltung *verwaltung;

private slots:
    void pushButton_stornieren_clicked();
    void pushButton_abschliessen_clicked();
    void pushButton_rechnung_clicked();
};

#endif // BUCHUNGDIALOGMIETER_H
