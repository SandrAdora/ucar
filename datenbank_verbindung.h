#ifndef DATENBANK_VERBINDUNG_H
#define DATENBANK_VERBINDUNG_H

#include <QString>
#include <QtSql/QSql>
#include <QtSql/QSqlDatabase>
#include <QDate>

class Datenbank_verbindung
{
private:
    static Datenbank_verbindung * instanz;
    QSqlDatabase instanz_db;
    QString db_pfad="/home/sunaro/team-4/Code/U-Car-db/U-Car-db.db";

protected:
    Datenbank_verbindung();

public:
    static Datenbank_verbindung * get_instanz();
    //Personfunktionen
    int add_person(const QString & nname, const QString & vname, const QDate & gebdatum, const int & geschlecht, const QString & pw, const QString & email, const QString & telnr, const QString & stadt,
                 const QString & plz, const QString & str, const QString & hausnr, const QString & fuehrerscheinklasse, const int & berechtigung);
    QSqlQuery get_person(const int id);
    //bool update_person_name(const int id, const QString nname, const QString vname);
    //bool update_person_passwort(const int id, const QString pw);
    //bool update_person_adresse(const int id, const QString stadt, const QString plz, const QString strasse, const QString Hausnr);
    //bool update_person_fuehrerscheinklasse(const int id, const QString fklasse);
    //bool update_person_email(const int id, const QString email);
    //bool delete_person(const int id);
    QSqlQuery get_person_alle();
    QSqlQuery get_mieter_alle();
    QSqlQuery get_vermieter_alle();
    QSqlQuery get_person_zu_fahrzeug(const int fid);
    QSqlQuery get_mieter_email_mit_passwort(const QString email, const QString pw);
    QSqlQuery get_vermieter_email_mit_passwort(const QString email, const QString pw);
    QSqlQuery get_mieter_zu_buchung(const int & bid);
    QSqlQuery get_vermieter_zu_buchung(const int & bid);

    //Rechnungfunktionen
    int add_rechnung(const int & buchungid, const double & betrag, const double & km, const double & tankstand);
    bool delete_rechnung(const int & rid);
    QSqlQuery get_rechnung(const int id);
    QSqlQuery get_rechnung_alle();
    QSqlQuery get_rechnung_zu_person(const int pid);

    //Fahrzeugfunktionen
    int add_fahrzeug(const QString & kennzeichen, const QString & marke, const QString & farbe, const int & baujahr, const int & beschaedigung, const int sitzplaetze,
                      const QString & fahrzeugart, const int & fmodell, const int & stellplatzid, const int & parkplatznr, const int & besitzerid);
    bool delete_fahrzeug(const int & id);
    QSqlQuery get_fahrzeug_suchen(const int & sitzplatze, const QString & stadt, const int & fmodell, const int & tag, const double & startzeit, const double & endzeit);
    QSqlQuery get_fahrzeug_zu_person(const int & pid);
    QSqlQuery get_fahrzeug(const int & id);
    QSqlQuery get_fahrzeug_alle();
    QSqlQuery get_fahrzeug_zeitraum_nach_zeitraum(const int & tag, const double & startzeit, const double & endzeit);
    QSqlQuery get_fahrzeug_zu_stellplatz(const int sid);
    int get_fahrzeug_zu_werten(const QString & kennzeichen, const QString & marke, const QString & farbe, const int & baujahr, const int & beschaedigung, const int sitzplaetze,
                                     const QString & fahrzeugart, const int & fmodell, const int & besitzerid);

    //Zeitraumfunktionen
    int add_zeitraum(const int & fahrzeugid, const int & tag, const double & startzeit, const double & endzeit);
    QSqlQuery get_zeitraum_zu_fahrzeug(const int & fid);

    //Stellplatzfunktionen
    int add_stellplatz(const QString & stadt, const QString & plz, const QString & strasse, const QString & hausnr);
    bool delete_stellplatz(const int & id);
    QSqlQuery get_stellplatz(const int & id);
    QSqlQuery get_stellplatz_alle();
    int get_stellplatz_zu_adresse(const QString & stadt, const QString & plz, const QString & strasse, const QString & hausnr);

    //Buchungfunktionen
    int add_buchung(const QDateTime & ausleihzeit, const QDateTime & rueckgabezeit, const int & fahrzeugid, const int & mieterid, const int & vermieterid);
    bool delete_buchung(const int & id);
    QSqlQuery get_buchung(const int & id);
    QSqlQuery get_buchung_alle();
    QSqlQuery get_buchung_zu_person(const int & pid);
    QSqlQuery get_buchung_zu_fahrzeug(const int & fid);
    bool update_buchung_rechnung(const int & bid, const int & rid);
    bool update_buchung_zahlung(const int & bid, const int & zid);
    bool update_buchung_status(const int & bid, const int & status);
    bool update_buchung_verleih(const int & bid, const int & vid);

    //Verleihfunktionen
    int add_verleih(const int & buchungid, const QDateTime & abholzeit, const QDateTime & rueckgabezeit);
    QSqlQuery get_verleih(const int & id);
    QSqlQuery get_verleih_alle();
    QSqlQuery get_verleih_zu_person(const int & pid);
    bool delete_verleih(const int & id);

    //Zahlungfunktionen
    int add_zahlung(const int & bid, const double & betrag);
    QSqlQuery get_zahlung(const int & id);
    QSqlQuery get_zahlung_alle();
    QSqlQuery get_zahlung_zu_person(const int & pid);
    QSqlQuery get_zahlung_zu_buchung(const int & bid);
    bool update_zahlung_status(const int & id, const int & status);

};

#endif // DATENBANK_VERBINDUNG_H

