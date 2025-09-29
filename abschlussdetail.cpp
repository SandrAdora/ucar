#include "abschlussdetail.h"
#include "ui_abschlussdetail.h"

#include "verleih.h"

AbschlussDetail::AbschlussDetail(Person *p, Buchung *b, Buchungsverwaltung *v, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AbschlussDetail),
    person(p),
    akt_buchung(b),
    verwaltung(v)
{
    ui->setupUi(this);
    setWindowTitle("Buchung abschließen");
}

AbschlussDetail::~AbschlussDetail()
{
    delete ui;
}

void AbschlussDetail::pushButton_absenden_clicked() {
    // Erstelle den Verleih
       QDateTime abholung = ui->dateTimeEdit_beginn->dateTime();
       QDateTime rueckgabe = ui->dateTimeEdit_ende->dateTime();
       double km_vor = ui->doubleSpinBox_kilometer_vor->value();
       double km_nach = ui->doubleSpinBox_kilometer_nach->value();
       double tank_vor = ui->doubleSpinBox_tank_vor->value();
       double tank_nach = ui->doubleSpinBox_tank_nach->value();
       double km = km_nach - km_vor;
       double tank = tank_vor - tank_nach;

       Verleih *verleih = new Verleih(abholung, rueckgabe, person, km, tank);
       akt_buchung->set_verleih(verleih);

       // Rufe die Methode zur Buchungsverwaltung auf, um die Buchung abzuschließen
       bool ok = verwaltung->buchung_abschliessen(verleih, akt_buchung, person);
       if(ok) {
           bool ok = verwaltung->rechnung_erstellen(verleih, akt_buchung);
           if(ok) {
               close();
           }
       }
}
