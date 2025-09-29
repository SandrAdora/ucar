#ifndef FAHRZEUGVERWALTUNG_H
#define FAHRZEUGVERWALTUNG_H

#include <QString>
#include <vector>
#include <QtSql/QSql>
#include <QDebug>
#include <QtSql/QSqlQuery>
#include "fahrzeug.h"
#include "datenbank_verbindung.h"
#include "person.h"

class Fahrzeugverwaltung
{

public:
    Fahrzeugverwaltung();
    ~Fahrzeugverwaltung();
    int fahrzeug_registrieren(int nutzerID, QString kennzeichen, QString marke, QString art, QString farbe, int baujahr, int sitzplaetze, QString fahrzeugtyp, int beschaedigung, QString stadt, QString plz, QString strasse, QString hausnr,
                              int parkplatznr, QTime mo_von, QTime mo_bis, QTime di_von, QTime di_bis, QTime mi_von, QTime mi_bis, QTime do_von, QTime do_bis, QTime fr_von, QTime fr_bis,
                              QTime sa_von, QTime sa_bis, QTime so_von, QTime so_bis);
    int zeitraum_ueberpruefen(int fid, int tag, QTime startzeit, QTime endzeit);
    int stellplatz_registrieren(QString stadt, QString plz, QString strasse, QString hausnr, int parkplatznr);
    std::vector<Fahrzeug *> vector_erstellen(QSqlQuery q);
    std::vector<Fahrzeug *> fahrzeug_suchen(int, QString, int, QDate, QTime, QTime);
    std::vector<Fahrzeug *> fahrzeuge_zu_person(int);

private:

    Datenbank_verbindung * db;

};

#endif // FAHRZEUGVERWALTUNG_H
