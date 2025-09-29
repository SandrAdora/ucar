#include "adresse.h"
//definition der Adressen

Adresse::Adresse(QString str, QString hn, QString plz, QString wohnort)
{
    strasse = str;
    hausnummer = hn;
    this->plz = plz;
    this->wohnort = wohnort;
}
QString Adresse::get_strasse() const {return strasse;}
void Adresse::set_strasse(QString str){ this->strasse = str;}
QString Adresse::get_hausnummer() const{ return hausnummer;}
void Adresse::set_hausnummer(QString hn){ this->hausnummer = hn;}
QString Adresse::get_plz() const{ return plz;}
void Adresse::set_plz(QString plz) { this->plz = plz;}
QString Adresse::get_wohnort() const{ return wohnort;}
void Adresse::set_wohnort(QString wohnort){ this->wohnort = wohnort;}

QString Adresse::print_adresse() {
    QString text = strasse + " " + hausnummer + ", " + plz + " " + wohnort;
    return text;
}
