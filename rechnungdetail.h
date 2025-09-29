#ifndef RECHNUNGDETAIL_H
#define RECHNUNGDETAIL_H

#include <QDialog>
#include "person.h"
#include "buchung.h"
#include "buchungsverwaltung.h"
#include "fahrzeugverwaltung.h"

namespace Ui {
class RechnungDetail;
}

class RechnungDetail : public QDialog
{
    Q_OBJECT

public:
    explicit RechnungDetail(Person *, Buchung *, Buchungsverwaltung *, QWidget *parent = nullptr);
   // void RechnungDetail::queryMieter(const QString& , const QString& );
    ~RechnungDetail();
    QString daten_ausgeben();

private:
    Ui::RechnungDetail *ui;
    Person *person;
    Buchung *akt_buchung;
    Buchungsverwaltung *verwaltung;

};

#endif // RECHNUNGDETAIL_H
