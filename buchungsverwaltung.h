

#ifndef BUCHUNGSVERWALTUNG_H
#define BUCHUNGSVERWALTUNG_H


#include <QObject>
#include <iostream>
#include <QString>
#include <vector>
#include <QDate>
#include <new>
#include "buchung.h"
#include "datenbank_verbindung.h"
#include <QFile>
#include <QTextStream>
#include <QSqlQuery>
#include <QVariant>
#include "fahrzeug.h"
#include "person.h"
#include "verleih.h"

#define KM_PREIS 2
#define TANK_KOSTEN 40

#define KM_PREIS 2
#define TANK_KOSTEN 40

class Buchungsverwaltung : public QObject, public Buchung {
public:
    std::vector<Buchung>& get_buchungsverwaltung();
    std::vector<Buchung> get_buchung_gesamt(QDateTime abholdatum, QDateTime rueckgabedatum, Buchungsstatus stat, int buchung_id);
    void set_neue_buchung_einfuegen(QDateTime abholdatum, QDateTime rueckgabedatum,  Buchungsstatus stat, int buchung_id);
    void buchung_bearbeiten(QDateTime abholdatum, QDateTime rueckgabedatum, Buchungsstatus stat, int buchung_id);
    std::vector<Buchung> pruefe_buchung_daten(QDateTime abholdatum, QDateTime rueckgabedatum, Buchungsstatus stat, int buchung_id);
    void buchung_loeschen(QDateTime abholdatum, QDateTime rueckgabedatum, Buchungsstatus stat, int buchung_id);
    bool buchung_abschliessen(Verleih *verleih, Buchung *buchung, Person *mieter);
    bool rechnung_erstellen(Verleih *verleih, Buchung *buchung);

    Buchungsverwaltung();
    ~Buchungsverwaltung();

    bool fahrzeug_buchen(int, int, QDateTime, QDateTime);
    bool buchung_status_aendern(int, Buchungsstatus);
    bool buchung_stornieren(int);
    std::vector<Buchung *> buchungen_zu_person(int);
    Fahrzeug * fahrzeug_zu_buchung(int);
    Verleih * verleih_zu_buchung(int);
    Rechnung * rechnung_zu_buchung(int);
    void datei_schreiben(int, QString);

private:
    std::vector<Buchung> buchungsverwaltung;
    Datenbank_verbindung *db;
};

#endif // BUCHUNGSVERWALTUNG_H
