#include "buchungdialogmieter.h"
#include "ui_buchungdialogmieter.h"
#include "abschlussdetail.h"
#include "rechnungdetail.h"

BuchungDialogMieter::BuchungDialogMieter(Person *p, Buchung *b, Buchungsverwaltung *v, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BuchungDialogMieter),
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
    if(status == Buchungsstatus::offen || status == Buchungsstatus::abgelehnt) {
        ui->pushButton_abschliessen->hide();
    }

    if(status == Buchungsstatus::bestaetigt || status == Buchungsstatus::abgelehnt) {
        ui->pushButton_stornieren->hide();
    }

    if(status == Buchungsstatus::abgeschlossen) {
        ui->pushButton_rechnung->show();
        ui->pushButton_abschliessen->hide();
        ui->pushButton_stornieren->hide();
    }
}

BuchungDialogMieter::~BuchungDialogMieter()
{
    delete ui;
}

QString BuchungDialogMieter::print_info() {
    QString text = "Gebuchtes Fahrzeug:\n" + akt_buchung->get_akt_fahrzeug()->print_daten() +
                   "\n\n" + akt_buchung->print_daten();
    return text;
}

void BuchungDialogMieter::pushButton_stornieren_clicked() {
    bool ok = verwaltung->buchung_stornieren(akt_buchung->get_buchung_id());
    if(ok) {
        close();
    }
}

void BuchungDialogMieter::pushButton_abschliessen_clicked() {
    AbschlussDetail *dialog = new AbschlussDetail(person, akt_buchung, verwaltung);
    dialog->open();
}

void BuchungDialogMieter::pushButton_rechnung_clicked() {
    if(akt_buchung->get_rechnung()) {
        RechnungDetail *dialog = new RechnungDetail(person, akt_buchung, verwaltung);
        dialog->open();
    }
}
