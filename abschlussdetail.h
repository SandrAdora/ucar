#ifndef ABSCHLUSSDETAIL_H
#define ABSCHLUSSDETAIL_H

#include <QDialog>
#include "buchungsverwaltung.h"
#include "person.h"

namespace Ui {
class AbschlussDetail;
}

class AbschlussDetail : public QDialog
{
    Q_OBJECT

public:
    explicit AbschlussDetail(Person *, Buchung *, Buchungsverwaltung *, QWidget *parent = nullptr);
    ~AbschlussDetail();

private:
    Ui::AbschlussDetail *ui;
    Person *person;
    Buchung *akt_buchung;
    Buchungsverwaltung *verwaltung;

private slots:
    void pushButton_absenden_clicked();
};

#endif // ABSCHLUSSDETAIL_H
