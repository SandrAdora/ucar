
#include "buchung.h"
#include <QString>

Buchung::Buchung(){}

Buchung::Buchung(QDateTime dat, QDateTime abholdatum, QDateTime rueckgabedatum, Buchungsstatus stat, int buch_id)
    : datum(dat), abholdatum(abholdatum), rueckgabedatum(rueckgabedatum), buchungsstatus(stat), buchung_id(buch_id)
{
    akt_fahrzeug = nullptr;
    akt_verleih = nullptr;
    akt_rechnung = nullptr;
}

Buchung::Buchung(QDateTime dat, QDateTime abholdatum, QDateTime rueckgabedatum, Buchungsstatus stat, int buch_id, Fahrzeug *f)
    : datum(dat), abholdatum(abholdatum), rueckgabedatum(rueckgabedatum), buchungsstatus(stat), buchung_id(buch_id),
    akt_fahrzeug(f)
{
    akt_verleih = nullptr;
    akt_rechnung = nullptr;
}

void Buchung::set_datum(const QDateTime dat)
{
    datum = dat;
}

void Buchung::set_abholdatum(const QDateTime abholdatum)
{
    this->abholdatum = abholdatum;
}

void Buchung::set_rueckgabedatum(const QDateTime rueckgabeatum)
{
    rueckgabedatum = rueckgabeatum;
}

void Buchung::set_status(Buchungsstatus stat)
{
    buchungsstatus = stat;
}

void Buchung::set_akt_fahrzeug(Fahrzeug *f) {
    akt_fahrzeug = f;
}

void Buchung::set_verleih(Verleih *v) {
    akt_verleih = v;
}

void Buchung::set_rechnung(Rechnung *r) {
    akt_rechnung = r;
}

QDateTime Buchung::get_datum() const
{
    return datum;
}

QDateTime Buchung::get_abholdatum() const
{
    return abholdatum;
}

QDateTime Buchung::get_rueckgabedatum() const
{
    return rueckgabedatum;
}

Buchungsstatus Buchung::get_status() const
{
    return buchungsstatus;
}

int Buchung::get_buchung_id() const
{
    return buchung_id;
}

Fahrzeug * Buchung::get_akt_fahrzeug() {
    return akt_fahrzeug;
}

Verleih * Buchung::get_verleih() {
    return akt_verleih;
}

Rechnung * Buchung::get_rechnung() {
    return akt_rechnung;
}

void Buchung::printBuchungsdaten() const
{
    std::cout << "Buchungsdaten:" << std::endl;
    std::cout << "Datum: " << datum.toString().toStdString() << std::endl;
    std::cout << "Abholdatum: " << abholdatum.toString().toStdString() << std::endl;
    std::cout << "Rückgabedatum: " << rueckgabedatum.toString().toStdString() << std::endl;
            std::cout << "Status: ";
    switch (buchungsstatus) {
    case Buchungsstatus::offen:
        std::cout << "offen";
        break;
    case Buchungsstatus::bestaetigt:
        std::cout << "bestätigt";
            break;
    case Buchungsstatus::abgelehnt:
        std::cout << "abgelehnt";
        break;
    case Buchungsstatus::abgeschlossen:
        std::cout << "abgeschlossen";
        break;
    }
    std::cout << std::endl;
    std::cout << "Buchung ID: " << buchung_id << std::endl;
}

QString Buchung::print_daten() {
    QString abholung_str = abholdatum.toString();
    QString rueckgabe_str = rueckgabedatum.toString();
    QString status_str = status_toString(buchungsstatus);
    QString text = "Gebuchter Zeitraum:\n" + abholung_str + " bis " + rueckgabe_str +
                   "\n\nStatus: " + status_str;
    return text;
}



int status_toInt(Buchungsstatus s) {
    int ret;
    switch(s) {
    case Buchungsstatus::offen:
        ret = 0;
        break;
    case Buchungsstatus::bestaetigt:
        ret = 1;
        break;
    case Buchungsstatus::abgelehnt:
        ret = 2;
        break;
    case Buchungsstatus::abgeschlossen:
        ret = 3;
        break;
    default:
        ret = -1;
        break;
    }
    return ret;
}

QString status_toString(Buchungsstatus s) {
    QString ret;
    switch(s) {
    case Buchungsstatus::offen:
        ret = "offen";
        break;
    case Buchungsstatus::bestaetigt:
        ret = "bestaetigt";
        break;
    case Buchungsstatus::abgelehnt:
        ret = "abgelehnt";
        break;
    case Buchungsstatus::abgeschlossen:
        ret = "abgeschlossen";
        break;
    default:
        ret = "";
        break;
    }
    return ret;
}

Buchungsstatus int_toStatus(int i) {
    Buchungsstatus ret;
    switch(i) {
    case 0:
        ret = Buchungsstatus::offen;
        break;
    case 1:
        ret = Buchungsstatus::bestaetigt;
        break;
    case 2:
        ret = Buchungsstatus::abgelehnt;
        break;
    case 3:
        ret = Buchungsstatus::abgeschlossen;
        break;
    default:
        ret = Buchungsstatus::offen;
        break;
    }
    return ret;
}
