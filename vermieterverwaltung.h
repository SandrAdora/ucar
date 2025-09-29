#ifndef VERMIETERVERWALTUNG_H
#define VERMIETERVERWALTUNG_H

#include <QString>
#include <vector>
#include <new>
#include <memory>
#include "adresse.h"
//für die Datenbank verbindung
#include <QSqlQuery>
#include"datenbank_verbindung.h"

#include "vermieter.h"


class Vermieterverwaltung : public Vermieter{
public:

    Vermieterverwaltung();
    ~Vermieterverwaltung();
    Vermieterverwaltung* get_vermieterverwaltung();


    std::vector<Vermieter*> get_vermieter(const QString, const QString);
    std::vector<Vermieter*>_sql(QSqlQuery );

    std::vector<Vermieter*>  vermieter_suche(Vermieter& );
    /// bool vermieter_bearbeiten(Vermieter&, QString, QString);

   //!Vermieter Registrierung
    bool vermieter_registrierung( QString &, QString & ,  QDate &, Geschlecht &,  QString & ,  QString & , QString & , QString & , QString &, QString &, QString & ,  QString & , Berechtigung &);

    ///bool vermieter_loeschen(int , QString, QString , QDate);
    bool vermieter_anmelden(QString, QString);

protected:
    Vermieter* vermieter_instanz;
//!hilfsfunktion bei der registrierung von neuen Vermieter

    bool  vermieter_ist_registriert(Vermieter& );

private:
     Datenbank_verbindung *db ;
    static Vermieterverwaltung* v_instanz;

};
#endif
