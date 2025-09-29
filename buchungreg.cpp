#include "buchungreg.h"
#include "ui_buchungreg.h"

BuchungReg::BuchungReg(Person *p, Fahrzeug *f, QDate d, QTime b, QTime e, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BuchungReg),
    person(p),
    akt_fahrzeug(f),
    datum(d),
    beginn(b),
    ende(e)
{
    ui->setupUi(this);
    setWindowTitle(akt_fahrzeug->get_fahrzeug_marke() + " " + akt_fahrzeug->get_fahrzeugmodell()->get_fahrzeug_art());
    verwaltung = new Buchungsverwaltung();

    QString datum_str = datum.toString();
    QString beginn_str = beginn.toString();
    QString ende_str = ende.toString();

    QString text = akt_fahrzeug->print_daten() +
                   "\n\nAusgewählter Zeitraum:\n" + datum_str + " " + beginn_str + " bis " + ende_str;
    ui->label_info->setText(text);
}

BuchungReg::~BuchungReg()
{
    delete ui;
}

void BuchungReg::pushButton_buchen_clicked() {
    QDateTime ausleihe(datum, beginn);
    QDateTime rueckgabe(datum, ende);
    bool ok = verwaltung->fahrzeug_buchen(akt_fahrzeug->get_fahrzeug_id(), person->get_person_id(), ausleihe, rueckgabe);
    if(ok) {
        close();
    }
}
