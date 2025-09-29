#ifndef BUCHUNGREG_H
#define BUCHUNGREG_H

#include <QDialog>
#include "fahrzeug.h"
#include "buchungsverwaltung.h"
#include "person.h"
#include <QDateTime>

namespace Ui {
class BuchungReg;
}

class BuchungReg : public QDialog
{
    Q_OBJECT

public:
    explicit BuchungReg(Person *, Fahrzeug *, QDate, QTime, QTime, QWidget *parent = nullptr);
    ~BuchungReg();

private:
    Ui::BuchungReg *ui;
    Person *person;
    Fahrzeug *akt_fahrzeug;
    Buchungsverwaltung *verwaltung;
    QDate datum;
    QTime beginn, ende;

private slots:
    void pushButton_buchen_clicked();
};

#endif // BUCHUNGREG_H
