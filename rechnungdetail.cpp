#include "rechnungdetail.h"
#include "ui_rechnungdetail.h"
#include "fahrzeug.h"
#include "mieter.h"
#include "buchung.h"
#include "buchungsverwaltung.h"
#include "person.h"
#include <QPushButton>
#include <rechnung.h>
#include <QDebug>

RechnungDetail::RechnungDetail(Person *p, Buchung *b, Buchungsverwaltung *v, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RechnungDetail),
    person(p),
    akt_buchung(b),
    verwaltung(v)
{
    ui->setupUi(this);
    setWindowTitle("Rechnung");
    ui->label_info->setText(daten_ausgeben());

}

RechnungDetail::~RechnungDetail()
{
    delete ui;
}

QString RechnungDetail::daten_ausgeben() {

    QString text = "";
    // Vérifier si le statut de la réservation est "abgeschlossen"
    if (akt_buchung->get_status() == Buchungsstatus::abgeschlossen)
    {
        text = akt_buchung->print_daten() + "\n\n" + akt_buchung->get_verleih()->print_daten()
             + "\n" + akt_buchung->get_rechnung()->print_daten();

    }
    return text;
}
