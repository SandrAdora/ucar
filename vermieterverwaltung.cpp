#include "vermieterverwaltung.h"
#include "datenbank_verbindung.h"

#include <cctype>




Vermieterverwaltung* Vermieterverwaltung::v_instanz = nullptr;
//definition des konstruktors
Vermieterverwaltung::Vermieterverwaltung(){

    db = db->get_instanz();
}


Vermieterverwaltung* Vermieterverwaltung::get_vermieterverwaltung()
{
    if (this->v_instanz == nullptr)
    {
        try {
            this->v_instanz = new Vermieterverwaltung();
            {

            }
        }  catch (const std::exception& e) {
            qDebug() <<e.what();
        }
    }
    return v_instanz;
}


std::vector<Vermieter*> Vermieterverwaltung::get_vermieter( const QString email, const QString pw)
{


    QSqlQuery qry = db->get_vermieter_email_mit_passwort(email, pw);


    return _sql(qry);

}

//Destruktor
Vermieterverwaltung::~Vermieterverwaltung(){

    if(vermieter_instanz != nullptr)
    {
        delete vermieter_instanz;
        vermieter_instanz = nullptr;

    }
    if(v_instanz != nullptr)
    {

        v_instanz = nullptr;
    }

}


//!Hilfsfunktionen
QString change_to_valid_name(QString& name)
{
    QString tmp;
    for (int i = 0; i < name.length(); i++)
    {
        if(name[i].isLetter())
        {
            tmp += name[i];
        }

    }
    return tmp;
}
bool check_names(QString& vn, QString nn)
{
   if(vn == nn)
   {
       return false;
   }
   return true;
}
bool Vermieterverwaltung::vermieter_registrierung(QString & nname, QString & vname,  QDate & gebdatum,  Geschlecht &geschlecht,  QString & pw,  QString & email,  QString & telnr,
                                                        QString & stadt, QString & plz,  QString & str,  QString & hausnr,  QString & fuehrerscheinklasse,  Berechtigung& berechtigung)

{

    bool is_up = false;
    if(!check_names(vname, nname))
    {
        qDebug()<<" Vorname und Zuname duerfen nicht gleich sein";
        return false;
    }
    const QString new_nname = change_to_valid_name(nname);
    const QString new_vname = change_to_valid_name(vname);




    //!Prüft die länge des Passworts
    if (pw.length() < 8)
    {
        std::cerr<<"Das Passwort muss mindestens 8 zeichen lang sein!!";
        return false;
    }
    for (int i = 0; i < pw.length(); i++)
    {
        //!prüft ob das Passwort mind. einen Großbuchstaben hat
        if(pw[i].isUpper())
        {

            is_up = true;

            break;
        }
    }

    if (!is_up)
    {
        std::cerr<<"Das Passwort muss mindestens einen Grossbuchstaben besitzen." << std::endl;

        return false;
    }

   vermieter_instanz = new Vermieter(new_vname, new_nname, gebdatum, berechtigung, geschlecht,str,hausnr, plz,stadt,  email, telnr,pw);


    if(vermieter_ist_registriert(*vermieter_instanz))
    {

        return false;
    }

    int g_ = static_cast<int>(geschlecht);
    int b_ = static_cast<int>(berechtigung);

    int vermieter_id = db->add_person(new_nname,new_vname, gebdatum, g_, pw, email, telnr, stadt, plz, str, hausnr, fuehrerscheinklasse, b_);

    if(vermieter_id == -1)
    {
        qDebug()<<"Der Vermieter konnte nicht registriert werden!";
        return false;
    }

//ob der Vermieter in die datenbank eingetragen worden ist
    QSqlQuery ql = db->get_vermieter_alle();

    while(ql.next())
    {
        int id_ = ql.value("PersonID").toInt();
        if(id_ == vermieter_id)
        {
            _sql(ql);
        }
    }

    //!Rückgabe wenn erfolgreich eingetragen

    return true;
}

bool Vermieterverwaltung::vermieter_anmelden(QString em, QString pw){
///sucht alle vermieter die in der datenbank sind raus
    QSqlQuery qry = db->get_vermieter_alle();


    try
    {
         vermieter_instanz = new Vermieter();
    } catch (const std::exception& e) {
        qDebug() <<e.what();
    }

    while(qry.next())
    {
        QString nutzer = qry.value("email").toString();
        QString passwort = qry.value("passwort").toString();
        if (nutzer == em && passwort == pw){

            return true; ///wenn das gesuchte Obj gefunden wurde
        }
    }
    qDebug() << "Die gesuchte Person konnte nicht gefunden werden!";
    return false;

}


//!diese funktion soll die daten aus der datenbank in die liste eintrage;
std::vector<Vermieter*>Vermieterverwaltung::_sql(QSqlQuery ql) {

    std::vector<Vermieter*> _liste;

    while (ql.next()) {

        int id = (ql.value("PersonID")).toInt();
        vermieter_instanz = new Vermieter(id);


        vermieter_instanz->set_berechtigung(static_cast<Berechtigung>(ql.value("Berechtigung").toInt()));
        vermieter_instanz->set_vname(ql.value("Vorname").toString());
        vermieter_instanz->set_nname(ql.value("Nachname").toString());
        QString geb_str = ql.value("Geburtsdatum").toString();
        QDate geb = QDate::fromString(geb_str, "dd.MM.yyyy");
        vermieter_instanz->set_geb(geb);
        vermieter_instanz->set_geschlecht(static_cast<Geschlecht>(ql.value("Geschlecht").toInt()));
        vermieter_instanz->set_strasse(ql.value("Straße").toString());
        vermieter_instanz->set_hausnummer(ql.value("Hausnr").toString());
        vermieter_instanz->set_plz(ql.value("PLZ").toString());
        vermieter_instanz->set_wohnort(ql.value("Stadt").toString());
        vermieter_instanz->set_email(ql.value("Email").toString());
        vermieter_instanz->set_telnr(ql.value("TelefonNr").toString());


        _liste.push_back(vermieter_instanz);

    }

    return _liste;
}

/*
bool Vermieterverwaltung::vermieter_bearbeiten(Vermieter& obj, QString what_to_change , QString change)
{
    //prüfe, vermieter existiert über die datenbank
    if(!vermieter_ist_registriert(&obj)) return false; //vermieter nicht vorhanden
    //! Prüfe, welche Eigenschaft geändert werden soll
    if (what_to_change == "vorname") {
        qDebug()<< "ALt: " << get_vname() << "\nNeu:" << change;
        //!Sollte dirket in der datenbank geändert werden
        //! alle obj.set... werden bei der endversion ausgearbeitet
        obj.set_vname(change);
    } else if (what_to_change == "nachname") {
        qDebug()<< "ALt: " << get_nname() << "\nNeu:" << change;
        obj.set_nname(change);
    } else if (what_to_change == "geburtsdatum") {
        qDebug()<< "ALt: " << get_geb() << "\nNeu:" << change;
        QDate date;
        obj.set_geb(date);
    } else if (what_to_change == "geschlecht") {
        //output
        qDebug()<< "ALt: " << get_geschlecht() << "\nNeu:" << change;
        switch (obj.toInt(change)){
        case 0: obj.set_geschlecht(Geschlecht::WEIBLICH); break;
        case 1: obj.set_geschlecht(Geschlecht::MAENNLICH);break;
        case 2: obj.set_geschlecht(Geschlecht::DIVERS);break;
        default: std::cerr<< "Invalid input"; break;
        }
    } else if (what_to_change == "strasse") {
        qDebug()<< "ALt: " << get_strasse() << "\nNeu:" << change;
        obj.set_strasse(change);
    } else if (what_to_change == "hausnummer") {
        qDebug()<< "ALt: " << get_anschrift() << "\nNeu:" << change;
        obj.set_hausnummer(change);

    } else if (what_to_change == "plz") {
        qDebug()<< "ALt: " << get_hausnummer() << "\nNeu:" << change;

        obj.set_plz(change);
    } else if (what_to_change == "wohnort") {
        qDebug()<< "ALt: " << get_wohnort() << "\nNeu:" << change;

        obj.set_wohnort(change);
    } else if (what_to_change == "email") {
        qDebug()<< "ALt: " << get_email() << "\nNeu:" << change;

        obj.set_email(change);
    } else if (what_to_change == "tel") {
        qDebug()<< "ALt: " << get_anschrift() << "\nNeu:" << change;
        obj.set_telnr(change);
    } else {
        // Ungültige Eigenschaft
        return false;
    }
    //datenbank aktualisieren
    // Db_verbindung::get_Detail()->vermieter_bearbeiten(obj);
    std::cout<<"Erfolgreiche aenderung";
    return true;
}
*/

///Personen Ausgabe


 ///Liefert die gesuchte Person zurück
std::vector<Vermieter*>  Vermieterverwaltung::vermieter_suche(Vermieter& obj) {


        QSqlQuery qy = db->get_vermieter_alle(); //!die datenbank verbindung hergestellt

        while(qy.next()){

                QString email_aus_der_datenbank = qy.value("Email").toString();
                QDate geb_aus_der_datenbank = qy.value("Geburtsdatum").toDate();
                QString nname = qy.value("Nachname").toString();
                if (email_aus_der_datenbank == obj.get_email() && geb_aus_der_datenbank == obj.get_geb() && nname == obj.get_nname()) {
                    return _sql(qy);
                }
           }


        return {};
    }
 /*
bool Vermieterverwaltung::vermieter_loeschen(int id, QString vn, QString nn, QDate geburtsdateum){
    //ToDo}
*/

bool Vermieterverwaltung::vermieter_ist_registriert(Vermieter &obj)
{
    QSqlQuery qm = db->get_vermieter_alle();
    while(qm.next())
    {
        QString email = qm.value("Email").toString();
        QString vn = qm.value("Vorname").toString();
        QString nn = qm.value("Nachname").toString();
        QDate geb = qm.value("Geburtsdatum").toDate();
        if(email == obj.get_email() && vn == obj.get_vname() && nn == obj.get_nname() && geb == obj.get_geb())
        {
            return true;
        }
    }
    return false;
}



