#include "buchungdialogvermieter.h"
#include "ui_buchungdialogvermieter.h"

#include "rechnungdetail.h"

BuchungDialogVermieter::BuchungDialogVermieter(Person *p, Buchung *b, Buchungsverwaltung *v, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BuchungDialogVermieter),
    person(p),
    akt_buchung(b),
    verwaltung(v)
{
    ui->setupUi(this);
    QString id_str;
    id_str.setNum(akt_buchung->get_buchung_id());
    setWindowTitle("Buchung Nr. " + id_str);
    ui->pushButton_rechnung->hide();
    ui->label_info->setText(print_info());

    Buchungsstatus status = akt_buchung->get_status();
    if(status == Buchungsstatus::abgeschlossen) {
        ui->pushButton_rechnung->show();
    }

    if(status == Buchungsstatus::bestaetigt || status == Buchungsstatus::abgelehnt || status == Buchungsstatus::abgeschlossen) {
        ui->pushButton_bestaetigen->hide();
        ui->pushButton_ablehnen->hide();
    }
}

QString BuchungDialogVermieter::print_info() {
    QString text = "Gebuchtes Fahrzeug:\n" + akt_buchung->get_akt_fahrzeug()->print_daten() +
                   "\n\n" + akt_buchung->print_daten();
    return text;
}

BuchungDialogVermieter::~BuchungDialogVermieter()
{
    delete ui;
}

void BuchungDialogVermieter::pushButton_bestaetigen_clicked() {
    bool ok = verwaltung->buchung_status_aendern(akt_buchung->get_buchung_id(), Buchungsstatus::bestaetigt);
    if(ok) {
        akt_buchung->set_status(Buchungsstatus::bestaetigt);
        ui->label_info->setText(print_info());
        ui->pushButton_bestaetigen->hide();
        ui->pushButton_ablehnen->hide();
    }
}

void BuchungDialogVermieter::pushButton_ablehnen_clicked() {
    bool ok = verwaltung->buchung_status_aendern(akt_buchung->get_buchung_id(), Buchungsstatus::abgelehnt);
    if(ok) {
        akt_buchung->set_status(Buchungsstatus::abgelehnt);
        ui->label_info->setText(print_info());
        ui->pushButton_bestaetigen->hide();
        ui->pushButton_ablehnen->hide();
    }
}

void BuchungDialogVermieter::pushButton_rechnung_clicked() {
    if(akt_buchung->get_rechnung()) {
        RechnungDetail *dialog = new RechnungDetail(person, akt_buchung, verwaltung);
        dialog->open();
    }
}
