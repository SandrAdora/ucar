#ifndef MIETERVERWALTUNG_H
#define MIETERVERWALTUNG_H

#include <QObject>
#include <QString>
#include <vector>
#include <new>
#include "mieter.h"
#include <QSqlQuery>
#include"datenbank_verbindung.h"
class Mieterverwaltung : public Mieter {

public:

    static Mieterverwaltung* get_mieterverwaltung(); //Instanz Funktion
    std::vector<Mieter*> get_mieter(const QString, const QString); ///liefert die person
    Mieterverwaltung(); //Konstruktor
    ~Mieterverwaltung(); //Destruktor

    std::vector<Mieter*>  mieter_suchen(Mieter& );

    std::vector<Mieter*>_sql(QSqlQuery );

    //hilfsfunktion
    bool mieter_ist_registriert(Mieter &) const ; ///UC_Funktion
    bool mieter_anmelden(QString, QString); ///UC_Funktion


    bool mieter_registrierung( QString & nname,  QString & vname,  QDate & gebdatum, Geschlecht geschlecht,  QString & pw,  QString & email,  QString & telnr,
                              QString & stadt,  QString & plz, QString & str, QString & hausnr, QString & fuehrerscheinklasse, Berechtigung berechtigung);

protected:

    static Mieter* mieter_instanz; 

private:
    Datenbank_verbindung *db ;
    static Mieterverwaltung* m_instanz; ///Singleton

};
#endif
