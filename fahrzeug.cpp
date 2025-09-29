#include <algorithm>
#include "fahrzeug.h"

Fahrzeug::Fahrzeug()
{

}

Fahrzeug::Fahrzeug(int id, QString marke, enum typ typ, QString art, QString kennz, QString n_farbe, int baujahr,
                   enum schaden beschaedigung, std::array<Zeitraum *, 7> zeit, Adresse *standort, QString stellplatz_nr, int sitze) {
    fahrzeug_id = id;
    fahrzeug_marke = marke;
    fahrzeugmodell = new Fahrzeugmodell(typ, art);
    kennzeichen = kennz;
    farbe = n_farbe;
    fahrzeug_baujahr = baujahr;
    beschaedigungsgrad = beschaedigung;
    mietzeitraum = zeit;
    fahrzeug_stellplatz = new Stellplatz(standort, stellplatz_nr, false);
    anzahl_sitze = sitze;
}

Fahrzeug::Fahrzeug(int id, QString marke, enum typ typ, QString art, QString kennz, QString n_farbe, int baujahr,
                   enum schaden beschaedigung, Adresse *standort, QString stellplatz_nr, int sitze) {
    fahrzeug_id = id;
    fahrzeug_marke = marke;
    fahrzeugmodell = new Fahrzeugmodell(typ, art);
    kennzeichen = kennz;
    farbe = n_farbe;
    fahrzeug_baujahr = baujahr;
    beschaedigungsgrad = beschaedigung;
    mietzeitraum.fill(nullptr);
    fahrzeug_stellplatz = new Stellplatz(standort, stellplatz_nr, false);
    anzahl_sitze = sitze;
}

Fahrzeug::~Fahrzeug() {
    delete fahrzeugmodell;
    for(int i = 0; i < 7; i++) {
        if(mietzeitraum.at(i) != nullptr) {
            delete mietzeitraum.at(i);
        }
    }
}

QString Fahrzeug::print_daten() {
    QString baujahr_str;
    baujahr_str.setNum(fahrzeug_baujahr);
    QString sitze_str;
    sitze_str.setNum(anzahl_sitze);
    QString text = "Modell: " + fahrzeug_marke + " " + fahrzeugmodell->get_fahrzeug_art() +
                   "\nTyp: " + typ_toString(fahrzeugmodell->get_fahrzeug_typ()) +
                   "\nKennzeichen: " + kennzeichen +
                   "\nBaujahr: " + baujahr_str +
                   "\nFarbe: " + farbe +
                   "\nAnzahl der Sitze: " + sitze_str +
                   "\nBeschädigungen: " + schaden_toString(beschaedigungsgrad) +
                   "\nStandort: " + fahrzeug_stellplatz->get_standort()->print_adresse() +
                   "\nStellplatz Nr.: " + fahrzeug_stellplatz->get_stellplatz();
    return text;
}

QString Fahrzeug::print_vermieter_daten() {
    QString text = print_daten() + "\n\nAngegebene Zeiträume:";
    for(int i = 0; i < 7; i++) {
        Zeitraum *z = mietzeitraum.at(i);
        if(z) {
            QString beginn_str = z->get_beginn().toString();
            QString ende_str = z->get_ende().toString();
            text += "\n" + int_toTag(i) + ": " + beginn_str + " bis " + ende_str;
        }
    }
    return text;
}

int Fahrzeug::get_fahrzeug_id() {
    return fahrzeug_id;
}

int Fahrzeug::get_fahrzeugschein_nr() {
    return fahrzeugschein_nr;
}

void Fahrzeug::set_fahrzeugschein_nr(int nr) {
    fahrzeugschein_nr = nr;
}

QString Fahrzeug::get_fahrzeug_marke() {
    return fahrzeug_marke;
}

void Fahrzeug::set_fahrzeug_marke(QString s) {
    fahrzeug_marke = s;
}

Fahrzeugmodell * Fahrzeug::get_fahrzeugmodell() {
    return fahrzeugmodell;
}

void Fahrzeug::set_fahrzeugmodell(Fahrzeugmodell * modell) {
    fahrzeugmodell = modell;
}

void Fahrzeug::set_fahrzeugmodell(enum typ typ, QString art) {
    fahrzeugmodell->set_fahrzeug_typ(typ);
    fahrzeugmodell->set_fahrzeug_art(art);
}

QString Fahrzeug::get_kennzeichen() {
    return kennzeichen;
}

void Fahrzeug::set_kennzeichen(QString s){
    kennzeichen = s;
}

QString Fahrzeug::get_farbe() {
    return farbe;
}

void Fahrzeug::set_farbe(QString s) {
    farbe = s;
}

int Fahrzeug::get_fahrzeug_baujahr() {
    return fahrzeug_baujahr;
}

void Fahrzeug::set_fahrzeug_baujahr(int s) {
    fahrzeug_baujahr = s;
}

enum schaden Fahrzeug::get_beschaedigungsgrad() {
    return beschaedigungsgrad;
}

void Fahrzeug::set_beschaedigungsgrad(enum schaden s) {
    beschaedigungsgrad = s;
}

std::array<Zeitraum *, 7> Fahrzeug::get_mietzeitraum() {
    return mietzeitraum;
}

Zeitraum * Fahrzeug::get_mietzeitraum_at(int tag) {
    return mietzeitraum.at(tag);
}

Stellplatz * Fahrzeug::get_stellplatz() {
    return fahrzeug_stellplatz;
}

void Fahrzeug::set_stellplatz(Stellplatz * sp) {
    fahrzeug_stellplatz = sp;
}

void Fahrzeug::set_stellplatz(Adresse * a, QString nr) {
    fahrzeug_stellplatz = new Stellplatz(a, nr, false);
}

int Fahrzeug::get_anzahl_sitze() {
    return anzahl_sitze;
}

void Fahrzeug::set_anzahl_sitze(int i) {
    anzahl_sitze = i;
}



enum schaden int_toSchaden(int i) {
    enum schaden ret;
    switch(i) {
    case 0:
        ret = KEINE;
        break;
    case 1:
        ret = LEICHT;
        break;
    case 2:
        ret = MITTEL;
        break;
    case 3:
        ret = SCHWER;
        break;
    default:
        ret = KEINE;
        break;
    }
    return ret;
}

QString schaden_toString(enum schaden s) {
    QString ret;
    switch(s) {
    case KEINE:
        ret = "keine";
        break;
    case LEICHT:
        ret = "leicht";
        break;
    case MITTEL:
        ret = "mittel";
        break;
    case SCHWER:
        ret = "schwer";
        break;
    default:
        ret = "keine";
        break;
    }
    return ret;
}
