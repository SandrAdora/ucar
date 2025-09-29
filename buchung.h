
#ifndef BUCHUNG_H
#define BUCHUNG_H

#include <QObject>
#include <QDateTime>
#include <QMainWindow>
#include <QString>
#include <QDate>
#include <iostream>
#include "fahrzeug.h"
#include "verleih.h"
#include "rechnung.h"

enum class Buchungsstatus {
    offen,
    bestaetigt,
    abgelehnt,
    abgeschlossen
};

class Buchung
{
public:
    Buchung();
    Buchung( QDateTime dat, QDateTime abholdatum, QDateTime rueckgabedatum,
            Buchungsstatus stat, int buch_id);
    Buchung( QDateTime dat, QDateTime abholdatum, QDateTime rueckgabedatum,
    Buchungsstatus stat, int buch_id, Fahrzeug *f);


    void set_datum(const QDateTime dat);
    void set_abholdatum(const QDateTime abholdatum);
    void set_rueckgabedatum(const QDateTime rueckgabeatum);
    void set_status(Buchungsstatus stat);
    void set_akt_fahrzeug(Fahrzeug *);
    void set_verleih(Verleih *);
    void set_rechnung(Rechnung *);

    QDateTime get_datum() const;
    QDateTime get_abholdatum() const;
    QDateTime get_rueckgabedatum() const;
    Buchungsstatus get_status() const;
    int get_buchung_id() const;
    Fahrzeug * get_akt_fahrzeug();
    Verleih * get_verleih();
    Rechnung * get_rechnung();

    virtual void printBuchungsdaten() const;

    QString print_daten();

private:
    QDateTime datum;
    QDateTime abholdatum;
    QDateTime rueckgabedatum;
    Buchungsstatus buchungsstatus;
    Fahrzeug *akt_fahrzeug;
    Verleih *akt_verleih;
    Rechnung *akt_rechnung;
    int buchung_id;
};

int status_toInt(Buchungsstatus);
QString status_toString(Buchungsstatus);
Buchungsstatus int_toStatus(int);

#endif // BUCHUNG_H





