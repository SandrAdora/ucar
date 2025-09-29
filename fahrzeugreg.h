#ifndef FAHRZEUGREG_H
#define FAHRZEUGREG_H

#include <QDialog>
#include "fahrzeugverwaltung.h"
#include "person.h"

namespace Ui {
class FahrzeugReg;
}

class FahrzeugReg : public QDialog
{
    Q_OBJECT

public:
    explicit FahrzeugReg(Person *, Fahrzeugverwaltung *, QWidget *parent = nullptr);
    ~FahrzeugReg();

private:
    Ui::FahrzeugReg *ui;
    Person *person;
    Fahrzeugverwaltung *verwaltung;

private slots:
    void pushButton_absenden_clicked();
};

#endif // FAHRZEUGREG_H
