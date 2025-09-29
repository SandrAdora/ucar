#ifndef FAHRZEUG_H
#define FAHRZEUG_H

#include <QString>
#include <array>
#include "fahrzeugmodell.h"
#include "zeitraum.h"
#include "stellplatz.h"
#include "adresse.h"

enum schaden {
    KEINE,
    LEICHT,
    MITTEL,
    SCHWER
};

class Fahrzeug
{
    int fahrzeug_id;
    int fahrzeugschein_nr;
    QString fahrzeug_marke = "";
    Fahrzeugmodell *fahrzeugmodell;
    QString kennzeichen = "";
    QString farbe = "";
    int fahrzeug_baujahr;
    enum schaden beschaedigungsgrad = KEINE;
    std::array<Zeitraum *, 7> mietzeitraum;     //ein Feld für jeden Wochentag
    Stellplatz *fahrzeug_stellplatz;
    int anzahl_sitze = 2;

public:
    Fahrzeug();
    Fahrzeug(int, QString, enum typ, QString, QString, QString, int, enum schaden, std::array<Zeitraum *, 7>, Adresse *, QString, int);
    Fahrzeug(int, QString, enum typ, QString, QString, QString, int, enum schaden, Adresse *, QString, int);
    ~Fahrzeug();
    QString print_daten();
    QString print_vermieter_daten();

    int get_fahrzeug_id();
    int get_fahrzeugschein_nr();
    void set_fahrzeugschein_nr(int);
    QString get_fahrzeug_marke();
    void set_fahrzeug_marke(QString);
    Fahrzeugmodell * get_fahrzeugmodell();
    void set_fahrzeugmodell(Fahrzeugmodell *);
    void set_fahrzeugmodell(enum typ, QString);
    QString get_kennzeichen();
    void set_kennzeichen(QString);
    QString get_farbe();
    void set_farbe(QString);
    int get_fahrzeug_baujahr();
    void set_fahrzeug_baujahr(int);
    enum schaden get_beschaedigungsgrad();
    void set_beschaedigungsgrad(enum schaden);
    std::array<Zeitraum *, 7> get_mietzeitraum();
    Zeitraum * get_mietzeitraum_at(int);
    Stellplatz * get_stellplatz();
    void set_stellplatz(Stellplatz *);
    void set_stellplatz(Adresse *, QString);
    int get_anzahl_sitze();
    void set_anzahl_sitze(int);
};

enum schaden int_toSchaden(int);
QString schaden_toString(enum schaden);

#endif // FAHRZEUG_H
