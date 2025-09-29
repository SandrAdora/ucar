
#include "stellplatz.h"

Stellplatz::Stellplatz()
    : standort(), stellplatz(""), verfuegbar(true) {}

Stellplatz::Stellplatz(Adresse *standort, QString stellplatz, bool verfuegbar)
    : standort(standort), stellplatz(stellplatz), verfuegbar(verfuegbar){}

Adresse * Stellplatz::get_standort() const {
    return this->standort;
}

void Stellplatz::set_standort(Adresse *standort) {
    this->standort = standort;
}

QString Stellplatz::get_stellplatz() const {
    return stellplatz;
}

void Stellplatz::set_stellplatz(QString stellplatz) {
    this->stellplatz = stellplatz;
}

bool Stellplatz::is_verfuegbar() const {
    return verfuegbar;
}

void Stellplatz::set_verfuegbar(bool verfuegbar) {
    this->verfuegbar = verfuegbar;
}

/*void Stellplatz::fahrzeug_einstellen(Fahrzeug* fahrzeug) {
    if (!parkende_fahrzeuge.contains(fahrzeug)) {
        parkende_fahrzeuge.append(fahrzeug);
        verfuegbar = false;
    }
}

void Stellplatz::fahrzeug_entfernen(Fahrzeug* fahrzeug) {
    if (parkende_fahrzeuge.contains(fahrzeug)) {
        parkende_fahrzeuge.removeOne(fahrzeug);
        if (parkende_fahrzeuge.isEmpty()) {
            verfuegbar = true;
        }
    }
}

QList<Fahrzeug*> Stellplatz::get_parkende_fahrzeuge() const {
    return parkende_fahrzeuge;
}*/
