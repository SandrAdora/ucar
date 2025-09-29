#include "datenbank_verbindung.h"
#include <QDebug>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlQueryModel>
#include <QtSql/QSqlError>
#include <QtSql/QSqlRecord>

//! noch Änderungen bei der finalen Anwendung: (für Prototyp erstmal weglassen)
//! QString hat Fkt toLower() --> dadurch evtl bei Suche eindeutig machen

Datenbank_verbindung * Datenbank_verbindung:: instanz=0;

Datenbank_verbindung * Datenbank_verbindung::get_instanz() {
    if(instanz==0) {
        instanz= new Datenbank_verbindung();
    }
    return instanz;
}


//try-catch-Block noch hinzufügen
//durch db.open() bereits singleton? Sonst Quellcode zu Singleton verändern
Datenbank_verbindung::Datenbank_verbindung()
{
    //vorher durch Singleton überprüfen, ob Database connection schon vorhanden
   instanz_db = QSqlDatabase::addDatabase("QSQLITE");
   instanz_db.setDatabaseName(db_pfad);

   if (!instanz_db.open())
   {
      qDebug() << "Error: connection with database failed";
   }
   else
   {
      qDebug() << "Database: connection ok";
   }

}

//erstellt neue Person & gibt die ID zurück, bei Fehler wird -1 zurück gegeben
int Datenbank_verbindung::add_person(const QString & nname, const QString & vname, const QDate & gebdatum, const int & geschlecht, const QString & pw, const QString & email, const QString & telnr,
                                     const QString & stadt, const QString & plz, const QString & str, const QString & hausnr, const QString & führerscheinklasse, const int & berechtigung)
{
   static int id = -1;

   //Parameter zu funktionierenden Parametern für db umwandeln
   //gebdatum als QString
   QString gdate=gebdatum.toString("dd.MM.yyyy");

   //Abfrage mit Parameterübergabe
   QSqlQuery query;
   query.prepare("INSERT INTO Person (PersonID, Nachname, Vorname, Geburtsdatum, Geschlecht, Passwort, Email, TelefonNr, Stadt, PLZ, Straße, HausNr, Führerscheinklasse, Berechtigung) VALUES "
                 "(null, :nachname, :vorname, :gebdate, :geschlecht, :passwort, :email, :telefonnr, :stadt, :plz, :strasse, :hausnr, :fklasse, :berechtigung)");

   query.bindValue(":nachname", nname);
   query.bindValue(":vorname", vname);
   query.bindValue(":gebdate", gdate);
   query.bindValue(":geschlecht", geschlecht);
   query.bindValue(":passwort", pw);
   query.bindValue(":email", email);
   query.bindValue(":telefonnr", telnr);
   query.bindValue(":stadt", stadt);
   query.bindValue(":plz", plz);
   query.bindValue(":strasse", str);
   query.bindValue(":hausnr", hausnr);
   query.bindValue(":fklasse", führerscheinklasse);
   query.bindValue(":berechtigung", berechtigung);

   //Abfrage ausführen
   if(query.exec())
   {
       //PersonID speichern
       query.prepare("select last_insert_rowid();");
       if(query.exec())
       {
            query.next();
            id=query.value(0).toInt();
       } else {
           qDebug() << "add_person - return id error:"
                    << query.lastError();
           qDebug() << ", letzte DB-Abfrage: " << query.lastQuery();
       }

   }
   else
   {
        qDebug() << "add_person error:"
                 << query.lastError();
        qDebug() << ", letzte DB-Abfrage: " << query.lastQuery();
   }

   return id;
}

//gibt Person zu PersonID zurück; die Tupel sind in folgender Reihenfolge:
//PersonID, Nachname, Vorname, Geburtsdatum, Geschlecht, Passwort, Email, TelefonNr, Stadt, PLZ, Straße, HausNr, Führerscheinklasse, Berechtigung
QSqlQuery Datenbank_verbindung::get_person(const int id) {
    QSqlQuery query;
    query.prepare("SELECT PersonID, Nachname, Vorname, Geburtsdatum, Geschlecht, Passwort, Email, TelefonNr, Stadt, PLZ, Straße, HausNr, Führerscheinklasse, Berechtigung FROM Person WHERE PersonID = :id");
    query.bindValue(":id", id);

    if(!query.exec())
    {
        qDebug() << "get_person error:"
                 << query.lastError();
        qDebug() << ", letzte DB-Abfrage: " << query.lastQuery();
    }
    return query;
}

//gibt alle Personen zurück; die Tupel sind in folgender Reihenfolge:
//PersonID, Nachname, Vorname, Geburtsdatum, Geschlecht, Passwort, Email, TelefonNr, Stadt, PLZ, Straße, HausNr, Führerscheinklasse, Berechtigung
QSqlQuery Datenbank_verbindung::get_person_alle() {
    QSqlQuery query;
    query.prepare("SELECT PersonID, Nachname, Vorname, Geburtsdatum, Geschlecht, Passwort, Email, TelefonNr, Stadt, PLZ, Straße, HausNr, Führerscheinklasse, Berechtigung FROM Person");

    if(!query.exec())
    {
        qDebug() << "get_person_alle error:"
                 << query.lastError();
        qDebug() << ", letzte DB-Abfrage: " << query.lastQuery();
    }

    return query;
}

//gibt alle Mieter zurück; die Tupel sind in folgender Reihenfolge:
//PersonID, Nachname, Vorname, Geburtsdatum, Geschlecht, Passwort, Email, TelefonNr, Stadt, PLZ, Straße, HausNr, Führerscheinklasse, Berechtigung
QSqlQuery Datenbank_verbindung::get_mieter_alle() {
    QSqlQuery query;
    query.prepare("SELECT PersonID, Nachname, Vorname, Geburtsdatum, Geschlecht, Passwort, Email, TelefonNr, Stadt, PLZ, Straße, HausNr, Führerscheinklasse, Berechtigung FROM Person where Berechtigung=0");

    if(!query.exec())
    {
        qDebug() << "get_mieter_alle error:"
                 << query.lastError();
        qDebug() << ", letzte DB-Abfrage: " << query.lastQuery();
    }

    return query;
}

//gibt alle Vermieter zurück; die Tupel sind in folgender Reihenfolge:
//PersonID, Nachname, Vorname, Geburtsdatum, Geschlecht, Passwort, Email, TelefonNr, Stadt, PLZ, Straße, HausNr, Führerscheinklasse, Berechtigung
QSqlQuery Datenbank_verbindung::get_vermieter_alle()
{
    QSqlQuery query;
    query.prepare("SELECT PersonID, Nachname, Vorname, Geburtsdatum, Geschlecht, Passwort, Email, TelefonNr, Stadt, PLZ, Straße, HausNr, Führerscheinklasse, Berechtigung FROM Person where Berechtigung=1");

    if(!query.exec())
    {
        qDebug() << "get_vermieter_alle error:"
                 << query.lastError();
        qDebug() << ", letzte DB-Abfrage: " << query.lastQuery();
    }

    return query;
}

//gibt Person zur übergebenen FahrzeugID zurück; die Tupel sind in folgender Reihenfolge:
//PersonID, Nachname, Vorname, Geburtsdatum, Geschlecht, Passwort, Email, TelefonNr, Stadt, PLZ, Straße, HausNr, Führerscheinklasse, Berechtigung
QSqlQuery Datenbank_verbindung::get_person_zu_fahrzeug(const int fid)
{
    QSqlQuery query;
    query.prepare("SELECT p.PersonID, p.Nachname, p.Vorname, p.Geburtsdatum, p.Geschlecht, p.Passwort, p.Email, p.TelefonNr, p.Stadt, p.PLZ, p.Straße, p.HausNr, p.Führerscheinklasse, p.Berechtigung "
                  "FROM Person p, Fahrzeug f where p.PersonID=f.BesitzerID and f.FahrzeugID=:fid");
    query.bindValue(":fid", fid);

    if(!query.exec())
    {
        qDebug() << "get_person_zu_fahrzeug error:"
                 << query.lastError();
        qDebug() << ", letzte DB-Abfrage: " << query.lastQuery();
    }
    return query;
}

//gibt Mieter zur übergebenen Email & Passwort zurück; die Tupel sind in folgender Reihenfolge:
//PersonID, Nachname, Vorname, Geburtsdatum, Geschlecht, Passwort, Email, TelefonNr, Stadt, PLZ, Straße, HausNr, Führerscheinklasse, Berechtigung
QSqlQuery Datenbank_verbindung::get_mieter_email_mit_passwort(const QString email, const QString pw) {
    QSqlQuery query;
    query.prepare("SELECT PersonID, Nachname, Vorname, Geburtsdatum, Geschlecht, Passwort, Email, TelefonNr, Stadt, PLZ, Straße, HausNr, Führerscheinklasse, Berechtigung"
                  " FROM Person where Email=:email and Passwort=:pw and Berechtigung=0");
    query.bindValue(":email", email);
    query.bindValue(":pw", pw);

    if(!query.exec())
    {
        qDebug() << "get_person_email_mit_passwort error:"
                 << query.lastError();
        qDebug() << ", letzte DB-Abfrage: " << query.lastQuery();
    }
    return query;
}

//gibt Vermieter zur übergebenen Email & Passwort zurück; die Tupel sind in folgender Reihenfolge:
//PersonID, Nachname, Vorname, Geburtsdatum, Geschlecht, Passwort, Email, TelefonNr, Stadt, PLZ, Straße, HausNr, Führerscheinklasse, Berechtigung
QSqlQuery Datenbank_verbindung::get_vermieter_email_mit_passwort(const QString email, const QString pw) {
    QSqlQuery query;
    query.prepare("SELECT PersonID, Nachname, Vorname, Geburtsdatum, Geschlecht, Passwort, Email, TelefonNr, Stadt, PLZ, Straße, HausNr, Führerscheinklasse, Berechtigung"
                  " FROM Person where Email=:email and Passwort=:pw and Berechtigung=1");
    query.bindValue(":email", email);
    query.bindValue(":pw", pw);

    if(!query.exec())
    {
        qDebug() << "get_person_email_mit_passwort error:"
                 << query.lastError();
        qDebug() << ", letzte DB-Abfrage: " << query.lastQuery();
    }
    return query;
}


//gibt Mieter zur übergebener BuchungID zurück; die Tupel sind in folgender Reihenfolge:
//PersonID, Nachname, Vorname, Geburtsdatum, Geschlecht, Passwort, Email, TelefonNr, Stadt, PLZ, Straße, HausNr, Führerscheinklasse, Berechtigung
QSqlQuery Datenbank_verbindung::get_mieter_zu_buchung(const int & bid) {
    QSqlQuery query;
    query.prepare("SELECT PersonID, Nachname, Vorname, Geburtsdatum, Geschlecht, Passwort, Email, TelefonNr, Stadt, PLZ, Straße, HausNr, Führerscheinklasse, Berechtigung "
                  "FROM Person, Buchung where Buchung.Mieter=Person.PersonID and Buchung.BuchungID=:bid");
    query.bindValue(":bid", bid);

    if(!query.exec())
    {
        qDebug() << "get_mieter_zu_buchung error:"
                 << query.lastError();
        qDebug() << ", letzte DB-Abfrage: " << query.lastQuery();
    }

    return query;
}

//gibt Mieter zur übergebener BuchungID zurück; die Tupel sind in folgender Reihenfolge:
//PersonID, Nachname, Vorname, Geburtsdatum, Geschlecht, Passwort, Email, TelefonNr, Stadt, PLZ, Straße, HausNr, Führerscheinklasse, Berechtigung
QSqlQuery Datenbank_verbindung::get_vermieter_zu_buchung(const int & bid) {
    QSqlQuery query;
    query.prepare("SELECT PersonID, Nachname, Vorname, Geburtsdatum, Geschlecht, Passwort, Email, TelefonNr, Stadt, PLZ, Straße, HausNr, Führerscheinklasse, Berechtigung "
                  "FROM Person, Buchung where Buchung.Vermieter=Person.PersonID and Buchung.BuchungID=:bid");
    query.bindValue(":bid", bid);

    if(!query.exec())
    {
        qDebug() << "get_vermieter_zu_buchung error:"
                 << query.lastError();
        qDebug() << ", letzte DB-Abfrage: " << query.lastQuery();
    }

    return query;
}

//erstellt neue Rechnung & gibt die ID zurück, bei Fehler wird -1 zurück gegeben; bei erfolgreicher Erstellung, aber Fehler beim Hinzufügen zur Buchung wird -2
int Datenbank_verbindung::add_rechnung(const int & buchungid, const double & betrag, const double & km, const double & tankstand) {
    int id = -1;

    //Abfrage mit Parameterübergabe
    QSqlQuery query;
    query.prepare("INSERT INTO Rechnung (RechnungID, Betrag, Kilometer, Tankstand) VALUES (null, :betrag, :km, :tank)");

    query.bindValue(":betrag", betrag);
    query.bindValue(":km", km);
    query.bindValue(":tank", tankstand);

    //Abfrage ausführen
    if(query.exec())
    {
        //RechnungID speichern & Rechnung zu Buchung hinzufügen
        query.prepare("select last_insert_rowid();");
        if(query.exec())
        {
            query.next();
            id=query.value(0).toInt();
            if(this->update_buchung_rechnung(buchungid, id)==false)
            {
                delete_rechnung(id);
                id=-2;              
                qDebug() << "add_rechnung - update_buchung_rechnung error:" << query.lastError();
                qDebug() << ", letzte DB-Abfrage: " << query.lastQuery();
            }

        } else {
            qDebug() << "add_rechnung - return id error:"<< query.lastError();
            qDebug() << ", letzte DB-Abfrage: " << query.lastQuery();
        }
    } else {
         qDebug() << "add_rechnung error:"
                  << query.lastError();
         qDebug() << ", letzte DB-Abfrage: " << query.lastQuery();
    }

    return id;
}

//löscht Rechnung zur übergebener RechnungID
bool Datenbank_verbindung::delete_rechnung(const int & rid) {
    bool success=false;

    QSqlQuery query;
    query.prepare("DELETE FROM Rechnung WHERE RechnungID=:id");

    query.bindValue(":id", rid);
    if(query.exec()) {
        success=true;
    } else {
        qDebug() << "delete_rechnung error:" << query.lastError();
        qDebug() << ", letzte DB-Abfrage: " << query.lastQuery();
    }
    return success;
}

//gibt Rechnung zur übergebener ID zurück; die Tupel sind in folgender Reihenfolge:
//RechnungID, Betrag, Kilometer, Tankstand
QSqlQuery Datenbank_verbindung::get_rechnung(const int id)
{
    QSqlQuery query;
    query.prepare("SELECT RechnungID, Betrag, Kilometer, Tankstand FROM Rechnung where RechnungID=:rid");
    query.bindValue(":rid", id);

    if(!query.exec())
    {
        qDebug() << "get_rechnung error:"
                 << query.lastError();
        qDebug() << ", letzte DB-Abfrage: " << query.lastQuery();
    }

    return query;
}

//gibt alle Rechnungen zurück; die Tupel sind in folgender Reihenfolge:
//RechnungID, Betrag, Kilometer, Tankstand
QSqlQuery Datenbank_verbindung::get_rechnung_alle()
{
    QSqlQuery query;
    query.prepare("SELECT RechnungID, Betrag, Kilometer, Tankstand FROM Rechnung");

    if(!query.exec())
    {
        qDebug() << "get_rechnung_alle error:"
                 << query.lastError();
        qDebug() << ", letzte DB-Abfrage: " << query.lastQuery();
    }

    return query;
}

//gibt alle Rechnungen zur übergebener PersonID zurück; die Tupel sind in folgender Reihenfolge:
//RechnungID, Betrag, Kilometer, Tankstand
QSqlQuery Datenbank_verbindung::get_rechnung_zu_person(const int pid) {
    QSqlQuery query;
    query.prepare("SELECT distinct r.RechnungID, r.Betrag, r.Kilometer, r.Tankstand from Rechnung r, Buchung b where r.RechnungID=b.RechnungID and (b.Mieter=:pid or b.Vermieter=:pid) ");
    query.bindValue(":pid", pid);

    if(!query.exec())
    {
        qDebug() << "get_rechnung_zu_person error:"
                 << query.lastError();
        qDebug() << ", letzte DB-Abfrage: " << query.lastQuery();
    }

    return query;
}

//erstellt neues Fahrzeug & gibt die ID zurück, bei Fehler wird -1 zurück gegeben
int Datenbank_verbindung::add_fahrzeug(const QString & kennzeichen, const QString & marke, const QString & farbe, const int & baujahr, const int & beschaedigung, const int sitzplaetze,
                                        const QString & fahrzeugart, const int & fmodell, const int & stellplatzid, const int & parkplatznr, const int & besitzerid) {
    int id=-1;

    //Abfrage mit Parameterübergabe
    QSqlQuery query;
    query.prepare("INSERT INTO Fahrzeug (FahrzeugID, Kennzeichen, Marke, Farbe, Baujahr, Beschädigungsgrad, AnzahlSitzplätze, Fahrzeugart, Fahrzeugmodell, StellplatzID, ParkplatzNr, BesitzerID) "
                  "VALUES (null, :kennzeichen, :marke, :farbe, :baujahr, :beschaedigung, :sitzplatze, :fahrzeugart, :fmodell, :stellplatz, :parkplatznr, :besitzer)");

    query.bindValue(":kennzeichen", kennzeichen);
    query.bindValue(":marke", marke);
    query.bindValue(":farbe", farbe);
    query.bindValue(":baujahr", baujahr);
    query.bindValue(":beschaedigung", beschaedigung);
    query.bindValue(":sitzplatze", sitzplaetze);
    query.bindValue(":fahrzeugart", fahrzeugart);
    query.bindValue(":fmodell", fmodell);
    query.bindValue(":stellplatz", stellplatzid);
    query.bindValue(":parkplatznr", parkplatznr);
    query.bindValue(":besitzer", besitzerid);

    //Abfrage ausführen
    if(query.exec())
    {
        //FahrzeugID speichern
        query.prepare("select last_insert_rowid();");
        if(query.exec())
        {
            query.next();
            id=query.value(0).toInt();
        } else {
            qDebug() << "add_fahrzeug - return id error:"<< query.lastError();
            qDebug() << ", letzte DB-Abfrage: " << query.lastQuery();
        }
    }
    else
    {
         qDebug() << "add_fahrzeug error:"
                  << query.lastError();
         qDebug() << ", letzte DB-Abfrage: " << query.lastQuery();
    }

    return id;
}

//löscht Fahrzeug zur übergebener FahrzeugID
bool Datenbank_verbindung::delete_fahrzeug(const int & id) {
    bool success=false;

    QSqlQuery query;
    query.prepare("DELETE FROM Fahrzeug WHERE FahrzeugID=:id");

    query.bindValue(":id", id);
    if(query.exec()) {
        success=true;
    } else {
        qDebug() << "delete_fahrzeug error:" << query.lastError();
        qDebug() << ", letzte DB-Abfrage: " << query.lastQuery();
    }
    return success;
}

//gibt alle Fahrzeuge & deren Zeiträume zu der eingegeben Suche zurück; die Tupel sind in folgender Reihenfolge:
//FahrzeugID, Kennzeichen, Marke, Farbe, Baujahr, Beschädigungsgrad, AnzahlSitzplätze, Fahrzeugart, Fahrzeugmodell, StellplatzID, ParkplatzNr, Tag, Mietbeginn, Mietende
QSqlQuery Datenbank_verbindung::get_fahrzeug_suchen(const int & sitzplatze, const QString & stadt, const int & fmodell, const int & tag, const double & mietbeginn, const double & mietende) {
    //Überprüfung nach welchen Werten gesucht
    int ueberpruefung=0; //1111: bedeutet alle Werte in der Suche sind angegeben; jede 0 bedeutet: das die Angabe in der Suche nicht gefüllt wurde
    if(sitzplatze!=-1) {ueberpruefung+=1000;}
    if(stadt!="") {ueberpruefung+=100;}
    if(fmodell!=-1) {ueberpruefung+=10;}
    if(tag!=-1) {ueberpruefung+=1;}

    QSqlQuery query;

    switch(ueberpruefung) {
    case 0:
        qDebug() <<"Es wurde keine Parameter zur Suche übergeben.";
        return get_fahrzeug_alle();
        break;
    case 1: //Zeitraum angegeben
        query.prepare("SELECT f.FahrzeugID, f.Kennzeichen, f.Marke, f.Farbe, f.Baujahr, f.Beschädigungsgrad, f.AnzahlSitzplätze, f.Fahrzeugart, f.Fahrzeugmodell, f.StellplatzID, f.ParkplatzNr "
                      "from Fahrzeug f, Zeitraum z where f.FahrzeugID=z.FahrzeugID and z.Tag=:tag and z.Mietbeginn<=:szeit and z.Mietende>=:ezeit");
        query.bindValue(":tag", tag);
        query.bindValue(":szeit", mietbeginn);
        query.bindValue(":ezeit", mietende);
        break;
    case 10: //Fahrzeugmodell angegeben
        query.prepare("SELECT f.FahrzeugID, f.Kennzeichen, f.Marke, f.Farbe, f.Baujahr, f.Beschädigungsgrad, f.AnzahlSitzplätze, f.Fahrzeugart, f.Fahrzeugmodell, f.StellplatzID, f.ParkplatzNr "
                      "from Fahrzeug f where f.Fahrzeugmodell=:fmodell");
        query.bindValue(":fmodell", fmodell);
        break;
    case 11: //Fahrzeugmodell & Zeitraum angegeben
        query.prepare("SELECT f.FahrzeugID, f.Kennzeichen, f.Marke, f.Farbe, f.Baujahr, f.Beschädigungsgrad, f.AnzahlSitzplätze, f.Fahrzeugart, f.Fahrzeugmodell, f.StellplatzID, f.ParkplatzNr "
                      "from Fahrzeug f, Zeitraum z where f.Fahrzeugmodell=:fmodell and f.FahrzeugID=z.FahrzeugID and z.Tag=:tag and z.Mietbeginn<=:szeit and z.Mietende>=:ezeit");
        query.bindValue(":fmodell", fmodell);
        query.bindValue(":tag", tag);
        query.bindValue(":szeit", mietbeginn);
        query.bindValue(":ezeit", mietende);
        break;
    case 100: //Stadt angegeben
        query.prepare("SELECT f.FahrzeugID, f.Kennzeichen, f.Marke, f.Farbe, f.Baujahr, f.Beschädigungsgrad, f.AnzahlSitzplätze, f.Fahrzeugart, f.Fahrzeugmodell, f.StellplatzID, f.ParkplatzNr "
                      "from Fahrzeug f, Stellplatz s where f.StellplatzID=s.StellplatzID and s.Stadt=:stadt");
        query.bindValue(":stadt", stadt);
        break;
    case 101: //Stadt & Zeitraum angegeben
        query.prepare("SELECT f.FahrzeugID, f.Kennzeichen, f.Marke, f.Farbe, f.Baujahr, f.Beschädigungsgrad, f.AnzahlSitzplätze, f.Fahrzeugart, f.Fahrzeugmodell, f.StellplatzID, f.ParkplatzNr "
                      "from Fahrzeug f, Stellplatz s, Zeitraum z where f.StellplatzID=s.StellplatzID and s.Stadt=:stadt and f.FahrzeugID=z.FahrzeugID "
                      "and z.Tag=:tag and z.Mietbeginn<=:szeit and z.Mietende>=:ezeit");
        query.bindValue(":stadt", stadt);
        query.bindValue(":tag", tag);
        query.bindValue(":szeit", mietbeginn);
        query.bindValue(":ezeit", mietende);
        break;
    case 110: //Stadt & Fahrzeugmodell angegeben
        query.prepare("SELECT f.FahrzeugID, f.Kennzeichen, f.Marke, f.Farbe, f.Baujahr, f.Beschädigungsgrad, f.AnzahlSitzplätze, f.Fahrzeugart, f.Fahrzeugmodell, f.StellplatzID, f.ParkplatzNr "
                      "from Fahrzeug f, Stellplatz s where f.StellplatzID=s.StellplatzID and s.Stadt=:stadt and f.Fahrzeugmodell=:fmodell");
        query.bindValue(":stadt", stadt);
        query.bindValue(":fmodell", fmodell);
        break;
    case 111: //Stadt & Fahrzeugmodell & Zeitraum angegeben
        query.prepare("SELECT f.FahrzeugID, f.Kennzeichen, f.Marke, f.Farbe, f.Baujahr, f.Beschädigungsgrad, f.AnzahlSitzplätze, f.Fahrzeugart, f.Fahrzeugmodell, f.StellplatzID, f.ParkplatzNr "
                      "from Fahrzeug f, Stellplatz s, Zeitraum z where f.StellplatzID=s.StellplatzID and s.Stadt=:stadt and f.FahrzeugID=z.FahrzeugID and "
                      "f.Fahrzeugmodell=:fmodell and z.Tag=:tag and z.Mietbeginn<=:szeit and z.Mietende>=:ezeit");
        query.bindValue(":stadt", stadt);
        query.bindValue(":tag", tag);
        query.bindValue(":szeit", mietbeginn);
        query.bindValue(":fmodell", fmodell);
        query.bindValue(":ezeit", mietende);
        break;
    case 1000: //AnzahlSitzplatze angegeben
        query.prepare("SELECT f.FahrzeugID, f.Kennzeichen, f.Marke, f.Farbe, f.Baujahr, f.Beschädigungsgrad, f.AnzahlSitzplätze, f.Fahrzeugart, f.Fahrzeugmodell, f.StellplatzID, f.ParkplatzNr "
                      "from Fahrzeug f where f.AnzahlSitzplätze>=:sitz");
        query.bindValue(":sitz", sitzplatze);
        break;
    case 1001: //AnzahlSitzplatze & Zeitraum angegeben
        query.prepare("SELECT f.FahrzeugID, f.Kennzeichen, f.Marke, f.Farbe, f.Baujahr, f.Beschädigungsgrad, f.AnzahlSitzplätze, f.Fahrzeugart, f.Fahrzeugmodell, f.StellplatzID, f.ParkplatzNr "
                      "from Fahrzeug f, Zeitraum z where f.AnzahlSitzplätze>=:sitz and f.FahrzeugID=z.FahrzeugID and z.Tag=:tag and z.Mietbeginn<=:szeit and z.Mietende>=:ezeit");
        query.bindValue(":sitz", sitzplatze);
        query.bindValue(":tag", tag);
        query.bindValue(":szeit", mietbeginn);
        query.bindValue(":ezeit", mietende);
        break;
    case 1010: //AnzahlSitzplatze & Fahrzeugmodell angegeben
        query.prepare("SELECT f.FahrzeugID, f.Kennzeichen, f.Marke, f.Farbe, f.Baujahr, f.Beschädigungsgrad, f.AnzahlSitzplätze, f.Fahrzeugart, f.Fahrzeugmodell, f.StellplatzID, f.ParkplatzNr "
                      "from Fahrzeug f where f.AnzahlSitzplätze>=:sitz and f.Fahrzeugmodell=:fmodell");
        query.bindValue(":sitz", sitzplatze);
        query.bindValue(":fmodell", fmodell);
        break;
    case 1011: //AnzahlSitzplatze & Fahrzeugmodell & Zeitraum angegeben
        query.prepare("SELECT f.FahrzeugID, f.Kennzeichen, f.Marke, f.Farbe, f.Baujahr, f.Beschädigungsgrad, f.AnzahlSitzplätze, f.Fahrzeugart, f.Fahrzeugmodell, f.StellplatzID, f.ParkplatzNr "
                      "from Fahrzeug f, Zeitraum z where f.AnzahlSitzplätze>=:sitz and f.Fahrzeugmodell=:fmodell and f.FahrzeugID=z.FahrzeugID and "
                      "z.Tag=:tag and z.Mietbeginn<=:szeit and z.Mietende>=:ezeit");
        query.bindValue(":sitz", sitzplatze);
        query.bindValue(":fmodell", fmodell);
        query.bindValue(":tag", tag);
        query.bindValue(":szeit", mietbeginn);
        query.bindValue(":ezeit", mietende);
        break;
    case 1100: //AnzahlSitzplatze & Stadt angegeben
        query.prepare("SELECT f.FahrzeugID, f.Kennzeichen, f.Marke, f.Farbe, f.Baujahr, f.Beschädigungsgrad, f.AnzahlSitzplätze, f.Fahrzeugart, f.Fahrzeugmodell, f.StellplatzID, f.ParkplatzNr "
                      "from Fahrzeug f, Stellplatz s where f.AnzahlSitzplätze>=:sitz and f.StellplatzID=s.StellplatzID and s.Stadt=:stadt");
        query.bindValue(":sitz", sitzplatze);
        query.bindValue(":stadt", stadt);
        break;
    case 1101: //AnzahlSitzplatze & Stadt & Zeitraum angegeben
        query.prepare("SELECT f.FahrzeugID, f.Kennzeichen, f.Marke, f.Farbe, f.Baujahr, f.Beschädigungsgrad, f.AnzahlSitzplätze, f.Fahrzeugart, f.Fahrzeugmodell, f.StellplatzID, f.ParkplatzNr "
                      "from Fahrzeug f, Stellplatz s, Zeitraum z where f.AnzahlSitzplätze>=:sitz and f.StellplatzID=s.StellplatzID and s.Stadt=:stadt "
                      "and f.FahrzeugID=z.FahrzeugID and z.Tag=:tag and z.Mietbeginn<=:szeit and z.Mietende>=:ezeit");
        query.bindValue(":sitz", sitzplatze);
        query.bindValue(":stadt", stadt);
        query.bindValue(":tag", tag);
        query.bindValue(":szeit", mietbeginn);
        query.bindValue(":ezeit", mietende);
        break;
    case 1110: //AnzahlSitzplatze & Stadt & Fahrzeugmodell angegeben
        query.prepare("SELECT f.FahrzeugID, f.Kennzeichen, f.Marke, f.Farbe, f.Baujahr, f.Beschädigungsgrad, f.AnzahlSitzplätze, f.Fahrzeugart, f.Fahrzeugmodell, f.StellplatzID, f.ParkplatzNr "
                      "from Fahrzeug f, Stellplatz s where f.AnzahlSitzplätze>=:sitz and f.Fahrzeugmodell=:fmodell and f.StellplatzID=s.StellplatzID and s.Stadt=:stadt");
        query.bindValue(":sitz", sitzplatze);
        query.bindValue(":stadt", stadt);
        query.bindValue(":fmodell", fmodell);
        break;
    case 1111: //AnzahlSitzplatze & Stadt & Fahrzeugmodell & Zeitraum angegeben
        query.prepare("SELECT f.FahrzeugID, f.Kennzeichen, f.Marke, f.Farbe, f.Baujahr, f.Beschädigungsgrad, f.AnzahlSitzplätze, f.Fahrzeugart, f.Fahrzeugmodell, f.StellplatzID, f.ParkplatzNr "
                      "from Fahrzeug f, Stellplatz s, Zeitraum z where f.StellplatzID=s.StellplatzID and f.AnzahlSitzplätze>=:sitz and f.Fahrzeugmodell =:fmodell and "
                      "s.Stadt=:stadt and f.FahrzeugID=z.FahrzeugID and z.Tag=:tag and z.Mietbeginn<=:szeit and z.Mietende>=:ezeit");
        query.bindValue(":sitz", sitzplatze);
        query.bindValue(":stadt", stadt);
        query.bindValue(":fmodell", fmodell);
        query.bindValue(":tag", tag);
        query.bindValue(":szeit", mietbeginn);
        query.bindValue(":ezeit", mietende);
        break;
    default:
        qDebug()<<"get_fahrzeug_suche error: in switch-case";
    }

    if(!query.exec())
    {
        qDebug() << "get_fahrzeug_suche error:"
                 << query.lastError();
        qDebug() << ", letzte DB-Abfrage: " << query.lastQuery();
    }

    return query;
}

//gibt alle Fahrzeuge zu der PersonID zurück; die Tupel sind in folgender Reihenfolge:
//FahrzeugID, Kennzeichen, Marke, Farbe, Baujahr, Beschädigungsgrad, AnzahlSitzplätze, Fahrzeugart, Fahrzeugmodell, StellplatzID, ParkplatzNr
QSqlQuery Datenbank_verbindung::get_fahrzeug_zu_person(const int & pid) {
    QSqlQuery query;
    query.prepare("SELECT FahrzeugID, Kennzeichen, Marke, Farbe, Baujahr, Beschädigungsgrad, AnzahlSitzplätze, Fahrzeugart, Fahrzeugmodell, StellplatzID, ParkplatzNr "
                  "from Fahrzeug where BesitzerID=:pid");
    query.bindValue(":pid", pid);

    if(!query.exec())
    {
        qDebug() << "get_fahrzeug_zu_person error:"
                 << query.lastError();
        qDebug() << ", letzte DB-Abfrage: " << query.lastQuery();
    }

    return query;
}

//gibt Fahrzeug zu der übergebenen FahrzeugID zurück; die Tupel sind in folgender Reihenfolge:
//FahrzeugID, Kennzeichen, Marke, Farbe, Baujahr, Beschädigungsgrad, AnzahlSitzplätze, Fahrzeugart, Fahrzeugmodell, StellplatzID, ParkplatzNr, BesitzerID
QSqlQuery Datenbank_verbindung::get_fahrzeug(const int & id) {
    QSqlQuery query;
    query.prepare("SELECT FahrzeugID, Kennzeichen, Marke, Farbe, Baujahr, Beschädigungsgrad, AnzahlSitzplätze, Fahrzeugart, Fahrzeugmodell, StellplatzID, ParkplatzNr "
                  "from Fahrzeug where FahrzeugID=:fid");
    query.bindValue(":fid", id);

    if(!query.exec())
    {
        qDebug() << "get_fahrzeug error:"
                 << query.lastError();
        qDebug() << ", letzte DB-Abfrage: " << query.lastQuery();
    }

    return query;
}

//gibt alle Fahrzeuge zurück; die Tupel sind in folgender Reihenfolge:
//FahrzeugID, Kennzeichen, Marke, Farbe, Baujahr, Beschädigungsgrad, AnzahlSitzplätze, Fahrzeugart, Fahrzeugmodell, StellplatzID, ParkplatzNr
QSqlQuery Datenbank_verbindung::get_fahrzeug_alle() {
    QSqlQuery query;
    query.prepare("SELECT FahrzeugID, Kennzeichen, Marke, Farbe, Baujahr, Beschädigungsgrad, AnzahlSitzplätze, Fahrzeugart, Fahrzeugmodell, StellplatzID, ParkplatzNr "
                  "from Fahrzeug");

    if(!query.exec())
    {
        qDebug() << "get_fahrzeug_alle error:"
                 << query.lastError();
        qDebug() << ", letzte DB-Abfrage: " << query.lastQuery();
    }

    return query;
}

//gibt alle Fahrzeuge & ihre Zeiträume zurück, die in der Zeit frei haben; die Tupel sind in folgender Reihenfolge:
//FahrzeugID, Kennzeichen, Marke, Farbe, Baujahr, Beschädigungsgrad, AnzahlSitzplätze, Fahrzeugart, Fahrzeugmodell, StellplatzID, ParkplatzNr, Tag, Mietbeginn, Mietende
QSqlQuery Datenbank_verbindung::get_fahrzeug_zeitraum_nach_zeitraum(const int & tag, const double & mietbeginn, const double & mietende) {
    QSqlQuery query;
    query.prepare("SELECT f.FahrzeugID, f.Kennzeichen, f.Marke, f.Farbe, f.Baujahr, f.Beschädigungsgrad, f.AnzahlSitzplätze, f.Fahrzeugart, f.Fahrzeugmodell, f.StellplatzID, f.ParkplatzNr,"
                  "z.Tag, z.Mietbeginn, z.Mietende from Fahrzeug f, Zeitraum z where f.FahrzeugID=z.FahrzeugID and z.Mietbeginn<=:mbeginn and z.Mietende>=z.mende");
    query.bindValue(":mbeginn", mietbeginn);
    query.bindValue(":mende", mietende);

    if(!query.exec())
    {
        qDebug() << "get_fahrzeug_zeitraum_nach_zeitraum error:"
                 << query.lastError();
        qDebug() << ", letzte DB-Abfrage: " << query.lastQuery();
    }

    return query;
}

//gibt alle Fahrzeuge zurück, die als Stellplatz die übergebene StandortID haben; die Tupel sind in folgender Reihenfolge:
//FahrzeugID, Kennzeichen, Marke, Farbe, Baujahr, Beschädigungsgrad, AnzahlSitzplätze, Fahrzeugart, Fahrzeugmodell, StellplatzID, ParkplatzNr
QSqlQuery Datenbank_verbindung::get_fahrzeug_zu_stellplatz(const int sid) {
    QSqlQuery query;
    query.prepare("SELECT f.FahrzeugID, f.Kennzeichen, f.Marke, f.Farbe, f.Baujahr, f.Beschädigungsgrad, f.AnzahlSitzplätze, f.Fahrzeugart, f.Fahrzeugmodell, f.StellplatzID, f.ParkplatzNr "
                  "from Fahrzeug f where f.StellplatzID=:sid");
    query.bindValue(":sid", sid);

    if(!query.exec())
    {
        qDebug() << "get_fahrzeug_zu_stellplatz error:"
                 << query.lastError();
        qDebug() << ", letzte DB-Abfrage: " << query.lastQuery();
    }

    return query;
}

//gibt FahrzeugID zu den übergebenen Werten zurück
int Datenbank_verbindung::get_fahrzeug_zu_werten(const QString & kennzeichen, const QString & marke, const QString & farbe, const int & baujahr, const int & beschaedigung, const int sitzplaetze,
                                                 const QString & fahrzeugart, const int & fmodell, const int & besitzerid) {
    int id=-1;

    QSqlQuery query;
    query.prepare("SELECT FahrzeugID from Fahrzeug where Kennzeichen=:kenn and Marke=:marke and Farbe=:farbe and Baujahr=:baujahr and Beschädigungsgrad=:bgrad and "
                  "AnzahlSitzplätze=:sitzplaetze and Fahrzeugart=:fart and Fahrzeugmodell=:fmodell and BesitzerID=:pid");
    query.bindValue(":kenn", kennzeichen);
    query.bindValue(":marke", marke);
    query.bindValue(":farbe", farbe);
    query.bindValue(":baujahr", baujahr);
    query.bindValue(":bgrad", beschaedigung);
    query.bindValue(":sitzplaetze", sitzplaetze);
    query.bindValue(":fart", fahrzeugart);
    query.bindValue(":fmodell", fmodell);
    query.bindValue(":pid", besitzerid);

    if(query.exec())
    {
        if(query.next()) {
            id=query.value(0).toInt();
        }
    } else {
        qDebug() << "get_fahrzeug_zu_werten error:"
                 << query.lastError();
        qDebug() << ", letzte DB-Abfrage: " << query.lastQuery();
    }

    return id;
}




//erstellt neuen Zeitraum & gibt die ID zurück, bei Fehler wird -1 zurück gegeben
int Datenbank_verbindung::add_zeitraum(const int & fahrzeugid, const int & tag, const double & mietbeginn, const double & mietende) {
    int id=-1;

    //Abfrage mit Parameterübergabe
    QSqlQuery query;
    query.prepare("INSERT INTO Zeitraum (FahrzeugID, Tag, Mietbeginn, Mietende) VALUES (:fid, :tag, :mbeginn, :mende)");

    query.bindValue(":fid", fahrzeugid);
    query.bindValue(":tag", tag);
    query.bindValue(":mbeginn", mietbeginn);
    query.bindValue(":mende", mietende);

    //Abfrage ausführen
    if(query.exec())
    {
        //PersonID speichern
        query.prepare("select last_insert_rowid();");
        if(query.exec())
        {
            query.next();
            id=query.value(0).toInt();
        } else {
            qDebug() << "add_zeitraum - return id error:"<< query.lastError();
            qDebug() << ", letzte DB-Abfrage: " << query.lastQuery();
        }
    }
    else
    {
         qDebug() << "add_zeitraum error:"
                  << query.lastError();
         qDebug() << ", letzte DB-Abfrage: " << query.lastQuery();
    }

    return id;
}

//gibt alle Zeiträume zur angegebener FahrzeugID zurück; die Tupel sind in folgender Reihenfolge:
//FahrzeugID, Tag, Mietbeginn, Mietende
QSqlQuery Datenbank_verbindung::get_zeitraum_zu_fahrzeug(const int & fid) {
    QSqlQuery query;
    query.prepare("SELECT FahrzeugID, Tag, Mietbeginn, Mietende from Zeitraum where FahrzeugID=:fid");
    query.bindValue(":fid", fid);
    if(!query.exec())
    {
        qDebug() << "get_zeitraum_zu_fahrzeug error:"
                 << query.lastError();
        qDebug() << ", letzte DB-Abfrage: " << query.lastQuery();
    }

    return query;
}

//erstellt neuen Stellplatz & gibt die ID zurück, bei Fehler wird -1 zurück gegeben; wenn für Parkplatznr -1 angegeben, zählt Datenbank automatisch hoch
int Datenbank_verbindung::add_stellplatz(const QString & stadt, const QString & plz, const QString & strasse, const QString & hausnr) {
    int id=-1;

    //Abfrage mit Parameterübergabe
    QSqlQuery query;

    query.prepare("INSERT INTO Stellplatz (StellplatzID, Stadt, PLZ, Straße, HausNr) VALUES (null, :stadt, :plz, :str, :hausnr)");

    query.bindValue(":stadt", stadt);
    query.bindValue(":plz", plz);
    query.bindValue(":str", strasse);
    query.bindValue(":hausnr", hausnr);

    //Abfrage ausführen
    if(query.exec())
    {
        //StellplatzID speichern
        query.prepare("select last_insert_rowid();");
        if(query.exec())
        {
            query.next();
            id=query.value(0).toInt();
        } else {
            qDebug() << "add_stellplatz - return id error:"<< query.lastError();
            qDebug() << ", letzte DB-Abfrage: " << query.lastQuery();
        }
    }
    else
    {
         qDebug() << "add_stellplatz error:"
                  << query.lastError();
         qDebug() << ", letzte DB-Abfrage: " << query.lastQuery();
    }

    return id;
}

//löscht Stellplatz zur übergebener StellplatzID
bool Datenbank_verbindung::delete_stellplatz(const int & id) {
    bool success=false;

    QSqlQuery query;
    query.prepare("DELETE FROM Stellplatz WHERE StellplatzID=:id");

    query.bindValue(":id", id);
    if(query.exec()) {
        success=true;
    } else {
        qDebug() << "delete_stellplatz error:" << query.lastError();
        qDebug() << ", letzte DB-Abfrage: " << query.lastQuery();
    }
    return success;
}

//gibt Stellplatz zu der übergebenen StellplatzID zurück; die Tupel sind in folgender Reihenfolge:
//StellplatzID, ParkplatzNr, Stadt, PLZ, Straße, HausNr
QSqlQuery Datenbank_verbindung::get_stellplatz(const int & id) {
    QSqlQuery query;
    query.prepare("SELECT StellplatzID, Stadt, PLZ, Straße, HausNr from Stellplatz where StellplatzID=:sid");
    query.bindValue(":sid", id);

    if(!query.exec())
    {
        qDebug() << "get_stellplatz error:"
                 << query.lastError();
        qDebug() << ", letzte DB-Abfrage: " << query.lastQuery();
    }

    return query;
}

//gibt alle Stellplätze zurück; die Tupel sind in folgender Reihenfolge:
//StellplatzID, ParkplatzNr, Stadt, PLZ, Straße, HausNr
QSqlQuery Datenbank_verbindung::get_stellplatz_alle() {
    QSqlQuery query;
    query.prepare("SELECT StellplatzID, Stadt, PLZ, Straße, HausNr from Stellplatz");

    if(!query.exec())
    {
        qDebug() << "get_stellplatz_alle error:"
                 << query.lastError();
        qDebug() << ", letzte DB-Abfrage: " << query.lastQuery();
    }

    return query;
}

//gibt StellplatzID zu der übergebenen Adresse zurück
int Datenbank_verbindung::get_stellplatz_zu_adresse(const QString &stadt, const QString &plz, const QString &strasse, const QString &hausnr) {
    int id=-1;

    QSqlQuery query;
    query.prepare("SELECT StellplatzID from Stellplatz where Stadt=:stadt and PLZ=:plz and Straße=:strasse and HausNr=:hausnr");
    query.bindValue(":stadt", stadt);
    query.bindValue(":plz", plz);
    query.bindValue(":strasse", strasse);
    query.bindValue(":hausnr", hausnr);


    if(query.exec())
    {
        if(query.next()) {
            id=query.value(0).toInt();
        }
    } else {
        qDebug() << "get_stellplatz_zu_adresse error:"
                 << query.lastError();
        qDebug() << ", letzte DB-Abfrage: " << query.lastQuery();

    }

    return id;
}


//erstellt neue Buchung & gibt die ID zurück, bei Fehler wird -1 zurück gegeben; status wird auf 0 gesetzt & Buchungszeit wird in utc Zeit angegeben (in Deutschland Winterzeit: UTC+1, Sommerzeit: UTC+2)
int Datenbank_verbindung::add_buchung(const QDateTime & ausleihzeit, const QDateTime & rueckgabezeit, const int & fahrzeugid, const int & mieterid, const int & vermieterid) {
    int id=-1;

    //Parameter zu funktionierenden Parametern für db umwandeln
    //ausleihzeit als 2 QStrings
    QString adatum=ausleihzeit.toString("dd.MM.yyyy");
    QString azeit=ausleihzeit.toString("hh:mm:ss");
    //rückgabezeit als 2 QStrings
    QString rdatum=rueckgabezeit.toString("dd.MM.yyyy");
    QString rzeit=rueckgabezeit.toString("hh:mm:ss");
    //aktuelle Zeit für Buchungszeit
    QDateTime now = QDateTime::currentDateTime();

    QString nowdatum=now.toString("dd.MM.yyyy");
    QString nowzeit=now.toString("hh:mm:ss");

    qDebug() << "nowdate: "<< nowdatum <<", nowtime: "<<nowzeit;



    //Abfrage mit Parameterübergabe
    QSqlQuery query;
    query.prepare("INSERT INTO Buchung (BuchungID, Buchung_datum, Buchung_zeit, Ausleihe_datum, Ausleihe_zeit, Rückgabe_datum, Rückgabe_zeit, Status, Fahrzeug, Mieter, Vermieter, VerleihID, RechnungID, "
                  "ZahlungID) VALUES (null, :nowdatum, :nowzeit, :adatum, :azeit, :rdatum, :rzeit, 0, :fid, :mieterid, :vermieterid, null, null, null)");

    query.bindValue(":adatum", adatum);
    query.bindValue(":azeit", azeit);
    query.bindValue(":rdatum", rdatum);
    query.bindValue(":rzeit", rzeit);
    query.bindValue(":fid", fahrzeugid);
    query.bindValue(":mieterid", mieterid);
    query.bindValue(":vermieterid", vermieterid);
    query.bindValue(":nowdatum", nowdatum);
    query.bindValue(":nowzeit", nowzeit);

    //Abfrage ausführen
    if(query.exec())
    {
        //BuchungID speichern
        query.prepare("select last_insert_rowid();");
        if(query.exec())
        {
            query.next();
            id=query.value(0).toInt();
        } else {
            qDebug() << "add_buchung - return id error:"<< query.lastError();
            qDebug() << ", letzte DB-Abfrage: " << query.lastQuery();
        }
    }
    else
    {
         qDebug() << "add_buchung error:"
                  << query.lastError();
         qDebug() << ", letzte DB-Abfrage: " << query.lastQuery();
    }

    return id;
}

//löscht die Buchung zu der übergebenen ID
bool Datenbank_verbindung::delete_buchung(const int & id) {
    bool success=false;

    QSqlQuery query;
    query.prepare("DELETE FROM Buchung WHERE BuchungID=:bid");

    query.bindValue(":bid", id);
    if(query.exec()) {
        success=true;
    } else {
        qDebug() << "delete_buchung error:"
                 << query.lastError();
        qDebug() << ", letzte DB-Abfrage: " << query.lastQuery();
    }
    return success;
}

//gibt die Buchung zu der übergebenen BuchungID zurück; die Tupel sind in folgender Reihenfolge:
//BuchungID, Buchung_datum, Buchung_zeit, Ausleihe_datum, Ausleihe_zeit, Rückgabe_datum, Rückgabe_zeit, Status, Fahrzeug, Mieter, Vermieter, VerleihID, RechnungID, ZahlungID
QSqlQuery Datenbank_verbindung::get_buchung(const int & id) {
    QSqlQuery query;
    query.prepare("SELECT BuchungID, Buchung_datum, Buchung_zeit, Ausleihe_datum, Ausleihe_zeit, Rückgabe_datum, Rückgabe_zeit, Status, Fahrzeug, Mieter, Vermieter, VerleihID, RechnungID, ZahlungID "
                  " from Buchung where BuchungID=:bid");
    query.bindValue(":bid", id);

    if(!query.exec())
    {
        qDebug() << "get_buchung error:"
                 << query.lastError();
        qDebug() << ", letzte DB-Abfrage: " << query.lastQuery();
    }

    return query;
}

//gibt alle Buchungen zurück; die Tupel sind in folgender Reihenfolge:
//BuchungID, Buchung_datum, Buchung_zeit, Ausleihe_datum, Ausleihe_zeit, Rückgabe_datum, Rückgabe_zeit, Status, Fahrzeug, Mieter, Vermieter, VerleihID, RechnungID, ZahlungID
QSqlQuery Datenbank_verbindung::get_buchung_alle() {
    QSqlQuery query;
    query.prepare("SELECT BuchungID, Buchung_datum, Buchung_zeit, Ausleihe_datum, Ausleihe_zeit, Rückgabe_datum, Rückgabe_zeit, Status, Fahrzeug, Mieter, Vermieter, VerleihID, RechnungID, ZahlungID "
                  " from Buchung");

    if(!query.exec())
    {
        qDebug() << "get_buchung_alle error:"
                 << query.lastError();
        qDebug() << ", letzte DB-Abfrage: " << query.lastQuery();
    }

    return query;
}

//gibt Buchung zu der übergebenen PersonID zurück; die Tupel sind in folgender Reihenfolge:
//BuchungID, Buchung_datum, Buchung_zeit, Ausleihe_datum, Ausleihe_zeit, Rückgabe_datum, Rückgabe_zeit, Status, Fahrzeug, Mieter, Vermieter, VerleihID, RechnungID, ZahlungID
QSqlQuery Datenbank_verbindung::get_buchung_zu_person(const int & pid) {
    QSqlQuery query;
    query.prepare("SELECT BuchungID, Buchung_datum, Buchung_zeit, Ausleihe_datum, Ausleihe_zeit, Rückgabe_datum, Rückgabe_zeit, Status, Fahrzeug, Mieter, Vermieter, VerleihID, RechnungID, ZahlungID "
                  " from Buchung where (Mieter=:pid or Vermieter=:pid)");
    query.bindValue(":pid", pid);

    if(!query.exec())
    {
        qDebug() << "get_buchung_zu_person error:"
                 << query.lastError();
        qDebug() << ", letzte DB-Abfrage: " << query.lastQuery();
    }

    return query;
}

//gibt Buchung zu der übergebenen FahrzeugID zurück; die Tupel sind in folgender Reihenfolge:
//BuchungID, Buchung_datum, Buchung_zeit, Ausleihe_datum, Ausleihe_zeit, Rückgabe_datum, Rückgabe_zeit, Status, Fahrzeug, Mieter, Vermieter, VerleihID, RechnungID, ZahlungID
QSqlQuery Datenbank_verbindung::get_buchung_zu_fahrzeug(const int & fid) {
    QSqlQuery query;
    query.prepare("SELECT BuchungID, Buchung_datum, Buchung_zeit, Ausleihe_datum, Ausleihe_zeit, Rückgabe_datum, Rückgabe_zeit, Status, Fahrzeug, Mieter, Vermieter, VerleihID, RechnungID, ZahlungID "
                  "from Buchung where Fahrzeug=:fid");
    query.bindValue(":fid", fid);

    if(!query.exec())
    {
        qDebug() << "get_buchung_zu_fahrzeug error:"
                 << query.lastError();
        qDebug() << ", letzte DB-Abfrage: " << query.lastQuery();
    }

    return query;
}

//weist der Buchung mit der übergebenen BuchungID die übergebene RechnungID zu
bool Datenbank_verbindung::update_buchung_rechnung(const int & bid, const int & rid) {
    bool success=false;
    QSqlQuery query;

    query=get_buchung(bid);
    if(query.next()) {  //BuchungID existiert
        query=get_rechnung(rid);
        if(query.next()) {  //RechnungID existiert
            query.prepare("UPDATE Buchung SET RechnungID=:rid where BuchungID=:bid");

            query.bindValue(":rid", rid);
            query.bindValue(":bid", bid);

            //Abfrage ausführen
            if(query.exec()) {
                success = true;
            } else {
                 qDebug() << "update_buchung_rechnung error:"
                          << query.lastError();
                 qDebug() << ", letzte DB-Abfrage: " << query.lastQuery();
            }
        } else {
            qDebug() << "update_buchung_rechnung error - Rechnung existiert nicht:"
                     << query.lastError();
            qDebug() << ", letzte DB-Abfrage: " << query.lastQuery();
        }
    } else {
        qDebug() << "update_buchung_rechnung error - Buchung existiert nicht:"
                 << query.lastError();
        qDebug() << ", letzte DB-Abfrage: " << query.lastQuery();
    }

    return success;
}

//weist der Buchung mit der übergebenen BuchungID die übergebene ZahlungID zu
bool Datenbank_verbindung::update_buchung_zahlung(const int & bid, const int & zid) {
    bool success=false;
    QSqlQuery query;

    query=get_buchung(bid);
    if(query.next()) {  //BuchungID existiert
        query=get_zahlung(zid);
        if(query.next()) {  //ZahlungID existiert
            query.prepare("UPDATE Buchung SET ZahlungID=:zid where BuchungID=:bid");

            query.bindValue(":zid", zid);
            query.bindValue(":bid", bid);

            //Abfrage ausführen
            if(query.exec()) {
                success = true;
            } else {
                 qDebug() << "update_buchung_zahlung error:"
                          << query.lastError();
                 qDebug() << ", letzte DB-Abfrage: " << query.lastQuery();
            }
        } else {
            qDebug() << "update_buchung_rechnung error - Zahlung existiert nicht:"
                     << query.lastError();
            qDebug() << ", letzte DB-Abfrage: " << query.lastQuery();
        }
    } else {
        qDebug() << "update_buchung_rechnung error - Buchung existiert nicht:"
                 << query.lastError();
        qDebug() << ", letzte DB-Abfrage: " << query.lastQuery();
    }

    return success;
}

//weist der Buchung mit der übergebenen BuchungID den übergebenen Status zu
bool Datenbank_verbindung::update_buchung_status(const int & bid, const int & status) {
    bool success=false;
    QSqlQuery query;

    query=get_buchung(bid);
    if(query.next()) {  //BuchungsID existiert

        query.prepare("UPDATE Buchung SET Status=:st where BuchungID=:bid");

        query.bindValue(":st", status);
        query.bindValue(":bid", bid);

        //Abfrage ausführen
        if(query.exec()) {
            success = true;
        } else {
             qDebug() << "update_buchung_status error:"
                      << query.lastError();
             qDebug() << ", letzte DB-Abfrage: " << query.lastQuery();
        }
    }

    return success;
}

//weist der Buchung mit der übergebenen BuchungID die übergebene VerleihID zu
bool Datenbank_verbindung::update_buchung_verleih(const int & bid, const int & vid) {
    bool success=false;
    QSqlQuery query;

    query=get_buchung(bid);
    if(query.next()) {  //BuchungID existiert
        query=get_verleih(vid);
        if(query.next()) {  //VerleihID existiert

            query.prepare("UPDATE Buchung SET VerleihID=:vid where BuchungID=:bid");

            query.bindValue(":vid", vid);
            query.bindValue(":bid", bid);

            //Abfrage ausführen
            if(query.exec()) {
                success = true;
            } else {
                 qDebug() << "update_buchung_zahlung error:"
                          << query.lastError();
                 qDebug() << ", letzte DB-Abfrage: " << query.lastQuery();
            }
        } else {
            qDebug() << "update_buchung_rechnung error - Verleih existiert nicht:"
                     << query.lastError();
            qDebug() << ", letzte DB-Abfrage: " << query.lastQuery();
        }
    } else {
        qDebug() << "update_buchung_rechnung error - Buchung existiert nicht:"
                 << query.lastError();
        qDebug() << ", letzte DB-Abfrage: " << query.lastQuery();
    }

    return success;
}

//erstellt neuen Verleih & gibt die ID zurück, bei Fehler wird -1 zurück gegeben & weist sie der übergebener Buchung zu; bei erfolgreicher Erstellung, aber Fehler beim Hinzufügen zur Buchung wird -2
int Datenbank_verbindung::add_verleih(const int & buchungid, const QDateTime & abholzeit, const QDateTime & rueckgabezeit) {
    int id=-1;

    //Parameter zu funktionierenden Parametern für db umwandeln
    //ausleihzeit als 2 QStrings
    QString adatum=abholzeit.toString("dd.MM.yyyy");
    QString azeit=abholzeit.toString("hh:mm:ss");
    //rückgabezeit als 2 QStrings
    QString rdatum=rueckgabezeit.toString("dd.MM.yyyy");
    QString rzeit=rueckgabezeit.toString("hh:mm:ss");

    //Abfrage mit Parameterübergabe
    QSqlQuery query;
    query.prepare("INSERT INTO Verleih (VerleihID, Abhol_datum, Abhol_zeit, Rückgabe_datum, Rückgabe_zeit) VALUES (null, :adatum, :azeit, :rdatum, :rzeit)");

    query.bindValue(":adatum", adatum);
    query.bindValue(":azeit", azeit);
    query.bindValue(":rdatum", rdatum);
    query.bindValue(":rzeit", rzeit);

    //Abfrage ausführen
    if(query.exec())
    {
        //VerleihID speichern
        query.prepare("select last_insert_rowid();");
        if(query.exec())
        {
            query.next();
            id=query.value(0).toInt();
            if(!this->update_buchung_verleih(buchungid, id))
            {
                id=-2;
                qDebug() << "add_verleih bei update_buchung_verleih error:"
                         << query.lastError();
                qDebug() << ", letzte DB-Abfrage: " << query.lastQuery();
            }
        } else {
            qDebug() << "add_verleih - return id error:"<< query.lastError();
            qDebug() << ", letzte DB-Abfrage: " << query.lastQuery();
        }
    } else {
         qDebug() << "add_verleih error:"
                  << query.lastError();
         qDebug() << ", letzte DB-Abfrage: " << query.lastQuery();
    }

    return id;
}

//löscht Verleih zur übergebener VerleihID
bool Datenbank_verbindung::delete_verleih(const int & id) {
    bool success=false;

    QSqlQuery query;
    query.prepare("DELETE FROM Verleih WHERE VerleihID=:id");

    query.bindValue(":id", id);
    if(query.exec()) {
        success=true;
    } else {
        qDebug() << "delete_verleih error:" << query.lastError();
        qDebug() << ", letzte DB-Abfrage: " << query.lastQuery();
    }
    return success;
}


//gibt Verleih zu der übergebenen VerleihID zurück; die Tupel sind in folgender Reihenfolge:
//VerleihID, Abhol_datum, Abhol_zeit, Rückgabe_datum, Rückgabe_zeit
QSqlQuery Datenbank_verbindung::get_verleih(const int & id) {
    QSqlQuery query;
    query.prepare("SELECT VerleihID, Abhol_datum, Abhol_zeit, Rückgabe_datum, Rückgabe_zeit from Verleih where VerleihID=:vid");
    query.bindValue(":vid", id);

    if(!query.exec())
    {
        qDebug() << "get_verleih error:"
                 << query.lastError();
        qDebug() << ", letzte DB-Abfrage: " << query.lastQuery();
    }

    return query;
}

//gibt alle Verleihe zurück; die Tupel sind in folgender Reihenfolge:
//VerleihID, Abhol_datum, Abhol_zeit, Rückgabe_datum, Rückgabe_zeit
QSqlQuery Datenbank_verbindung::get_verleih_alle() {
    QSqlQuery query;
    query.prepare("SELECT VerleihID, Abhol_datum, Abhol_zeit, Rückgabe_datum, Rückgabe_zeit from Verleih");

    if(!query.exec())
    {
        qDebug() << "get_verleih_alle error:"
                 << query.lastError();
        qDebug() << ", letzte DB-Abfrage: " << query.lastQuery();
    }

    return query;
}

//gibt alle Verleihe zu der angegebenen PersonID zurück; die Tupel sind in folgender Reihenfolge:
//VerleihID, Abhol_datum, Abhol_zeit, Rückgabe_datum, Rückgabe_zeit
QSqlQuery Datenbank_verbindung::get_verleih_zu_person(const int & pid) {
    QSqlQuery query;
    query.prepare("SELECT VerleihID, Abhol_datum, Abhol_zeit, Rückgabe_datum, Rückgabe_zeit from Verleih, Buchung where Buchung.VerleihID=Verleih.VerleihID and "
                  "(Buchung.Mieter=:pid or Buchung.Vermieter=:pid");

    query.bindValue(":pid", pid);

    if(!query.exec())
    {
        qDebug() << "get_verleih_zu_person error:"
                 << query.lastError();
        qDebug() << ", letzte DB-Abfrage: " << query.lastQuery();
    }

    return query;
}

//erstellt neue Zahlung & gibt die ID zurück, bei Fehler wird -1 zurück gegeben & weist sie der Buchung zurück; Zahlungszeit wird in utc Zeit angegeben (in Deutschland Winterzeit: UTC+1, Sommerzeit: UTC+2);
//bei erfolgreicher Erstellung, aber Fehler beim Hinzufügen zur Buchung wird -2
int Datenbank_verbindung::add_zahlung(const int & bid, const double & betrag) {
    int id=-1;

    //Parameter zu funktionierenden Parametern für db umwandeln
    //derzeitige Zeit speichern
    QDateTime now;
    now.currentDateTimeUtc();
    QString nowdatum=now.toString("dd.mm.yyyy");
    QString nowzeit=now.toString("hh:mm:ss");

    //Abfrage mit Parameterübergabe
    QSqlQuery query;
    query.prepare("INSERT INTO Zahlung (ZahlungID, Datum, Uhrzeit, Betrag, Status) VALUES (null, :datum, :zeit, :betrag, 0)");

    query.bindValue(":datum", nowdatum);
    query.bindValue(":zeit", nowzeit);
    query.bindValue(":betrag", betrag);

    //Abfrage ausführen
    if(query.exec())
    {
        //ZahlungID speichern
        query.prepare("select last_insert_rowid();");
        if(query.exec())
        {
            query.next();
            id=query.value(0).toInt();
            if(!this->update_buchung_zahlung(bid, id))
            {
                id=-2;
                qDebug() << "add_zahlung bei update_buchung_zahlung error:" << query.lastError();
                qDebug() << ", letzte DB-Abfrage: " << query.lastQuery();
            }
        } else {
            qDebug() << "add_zahlung - return id error:"<< query.lastError();
            qDebug() << ", letzte DB-Abfrage: " << query.lastQuery();
        }
    } else {
         qDebug() << "add_zahlung error:"
                  << query.lastError();
         qDebug() << ", letzte DB-Abfrage: " << query.lastQuery();
    }

    return id;
}

//gibt die Zahlung zu der übergebenen ZahlungID zurück; die Tupel sind in folgender Reihenfolge:
//ZahlungID, Datum, Uhrzeit, Betrag, Status
QSqlQuery Datenbank_verbindung::get_zahlung(const int & id) {
    QSqlQuery query;
    query.prepare("SELECT ZahlungID, Datum, Uhrzeit, Betrag, Status from Zahlung where ZahlungID=:zid");
    query.bindValue(":zid", id);

    if(!query.exec())
    {
        qDebug() << "get_zahlung error:"
                 << query.lastError();
        qDebug() << ", letzte DB-Abfrage: " << query.lastQuery();
    }

    return query;
}

//gibt alle Zahlungen zurück; die Tupel sind in folgender Reihenfolge:
//ZahlungID, Datum, Uhrzeit, Betrag, Status
QSqlQuery Datenbank_verbindung::get_zahlung_alle() {
    QSqlQuery query;
    query.prepare("SELECT ZahlungID, Datum, Uhrzeit, Betrag, Status from Zahlung");

    if(!query.exec())
    {
        qDebug() << "get_zahlung_alle error:"
                 << query.lastError();
        qDebug() << ", letzte DB-Abfrage: " << query.lastQuery();
    }

    return query;
}

//gibt alle Zahlungen zu der angegebenen PersonID zurück; die Tupel sind in folgender Reihenfolge:
//ZahlungID, Datum, Uhrzeit, Betrag, Status
QSqlQuery Datenbank_verbindung::get_zahlung_zu_person(const int & pid) {
    QSqlQuery query;
    query.prepare("SELECT ZahlungID, Datum, Uhrzeit, Betrag, Status from Zahlung, Buchung where Zahlung.ZahlungID=Buchung.BuchungID and (Buchung.Mieter=:pid and Buchung.Vermieter=:pid");
    query.bindValue(":pid", pid);

    if(!query.exec())
    {
        qDebug() << "get_zahlung_zu_person error:"
                 << query.lastError();
        qDebug() << ", letzte DB-Abfrage: " << query.lastQuery();
    }

    return query;
}

//gibt alle Zahlungen zu der angegebenen BuchungID zurück; die Tupel sind in folgender Reihenfolge:
//ZahlungID, Datum, Uhrzeit, Betrag, Status
QSqlQuery Datenbank_verbindung::get_zahlung_zu_buchung(const int & bid) {
    QSqlQuery query;
    query.prepare("SELECT ZahlungID, Datum, Uhrzeit, Betrag, Status from Zahlung, Buchung where Zahlung.ZahlungID=Buchung.BuchungID and (Buchung.BuchungID=:bid");
    query.bindValue(":bid", bid);

    if(!query.exec())
    {
        qDebug() << "get_zahlung_zu_buchung error:"
                 << query.lastError();
        qDebug() << ", letzte DB-Abfrage: " << query.lastQuery();
    }

    return query;
}

//weist der Zahlung mit der übergebenen ZahlungID den übergebenen Status zu
bool Datenbank_verbindung::update_zahlung_status(const int & id, const int & status) {
        bool success=false;

        QSqlQuery query;
        query.prepare("UPDATE Zahlung SET Status=:st where ZahlungID=:zid");

        query.bindValue(":zid", id);
        query.bindValue(":st", status);

        //Abfrage ausführen
        if(query.exec())
        {
            success = true;
        }
        else
        {
             qDebug() << "update_zahlung_status error:"
                      << query.lastError();
             qDebug() << ", letzte DB-Abfrage: " << query.lastQuery();
        }

        return success;
}
