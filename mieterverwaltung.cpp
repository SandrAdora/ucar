#include "mieterverwaltung.h"

Mieter* Mieterverwaltung::mieter_instanz = nullptr;
Mieterverwaltung* Mieterverwaltung::m_instanz = nullptr;
Mieterverwaltung::Mieterverwaltung()
{
    db = db->get_instanz();
}

Mieterverwaltung* Mieterverwaltung::get_mieterverwaltung()
{
    if (m_instanz == nullptr)
    {
        try {
            m_instanz = new Mieterverwaltung();
            {

            }
        }  catch (const std::exception& e) {
            qDebug() <<e.what();
        }
    }
    return m_instanz;

}


std::vector<Mieter*> Mieterverwaltung::get_mieter(const QString email, const QString pw)
{
    QSqlQuery q = db->get_mieter_email_mit_passwort(email, pw);
    return (_sql(q)) ;


}
//Destruktor
Mieterverwaltung::~Mieterverwaltung() {
    if(this->mieter_instanz != nullptr)
    {
        delete mieter_instanz;
    }
    if (this-> db != nullptr)
    {
        delete db;
    }

}


bool Mieterverwaltung::mieter_anmelden(QString email, QString pw)
{
    ///übergibt das Obj. einen speicher
    
    QSqlQuery qr = db->get_mieter_alle();
    while(qr.next())
    {
        QString email_datenbank = qr.value("email").toString();
        QString pw_datenbank = qr.value("passwort").toString();
        if(email_datenbank == email && pw_datenbank == pw)
        {

            return true;
        }
    }

    return false;
}

QString check_name( QString& name)
{
    QString temp;

    for(auto& e: name)
    {
        if(e.isLetter())
        {
            temp += e;
        }
    }
    return temp;
}



bool Mieterverwaltung::mieter_registrierung(QString & nname,    QString & vname, QDate & gebdatum, Geschlecht geschlecht,  QString & pw,  QString & email,  QString & telnr,
                                                   QString & stadt,  QString & plz,  QString & str,  QString & hausnr,  QString & fuehrerscheinklasse, Berechtigung berechtigung)
{
    if (nname == vname)
    {
        qDebug()<<" Vorname und Zuname durfen nicht gleich sein!";
        return false;
    }
    ///prüft die namen ob sie aus buchstaben bestehen
         QString new_nname = check_name(nname);
         QString new_vname = check_name(vname);

    bool is_up = false;
    //!Prüft die länge des Passworts
    if (pw.length() < 8)
    {
        std::cerr<<"Das Passwort muss mindestens 8 zeichen lang sein!!";
        return false;
    }
    for (int i = 0; i < pw.length(); i++)
    {
        if(pw[i].isUpper())
        {
            //!is_up auf true gesetzt wenn ein grossbuchstabe gefunden wurde
            is_up = true;
            //!bricht die schleife ab
            break;
        }
    }

    if (!is_up)
    {

        std::cerr<<"Das Passwort muss mindestens einen Grossbuchstaben besitzen." << std::endl;
   
        return false;
    }

    mieter_instanz = new Mieter(new_vname,new_nname, gebdatum, berechtigung, geschlecht,str,hausnr, plz,stadt,  email, telnr,pw, fuehrerscheinklasse);

    //!prüfe ob vermieter bereits in der liste existiert
    if(mieter_ist_registriert(*mieter_instanz))
    {
        
        //!rückgabe wenn der vermieter bereits vorhanden ist
        return false;
    }


    int g_ = static_cast<int>(geschlecht);
    int b_ = static_cast<int>(berechtigung);

    int mieter_id = db->add_person(new_nname, new_vname, gebdatum, g_, pw, email, telnr, stadt, plz, str, hausnr, fuehrerscheinklasse, b_);

    if(mieter_id == -1)
    {
        qDebug()<<"Der Vermieter konnte nicht registriert werden!";


        return false;
    }

    QSqlQuery ql = db->get_mieter_alle();

    while(ql.next())
    {
        int id_ = ql.value("PersonID").toInt();
        if(id_ == mieter_id)
        {
            _sql(ql);
        }
    }


      return true;
}



std::vector<Mieter*>  Mieterverwaltung::mieter_suchen(Mieter& obj) {


    QSqlQuery qry = db->get_mieter_alle();

    while(qry.next())
    {
        QString email_aus_der_datenbank = qry.value("PersonID").toString();
        QDate geb_aus_der_datenbank = qry.value("geburtsdatum").toDate();
        QString nname = qry.value("nachname").toString();
        if (email_aus_der_datenbank == obj.get_email() && geb_aus_der_datenbank == obj.get_geb() && nname == obj.get_nname()) {
            return _sql(qry);

        }
    }
    qDebug() << "Gesuchte Mieter konnte nicht gefunden werden!" ;
    return {}; ///wenn die gesuchte person nicht gefunden werden konnte wird eine leere liste zurück geworfen
}



//Schnittstelle zur datenban
std::vector<Mieter*> Mieterverwaltung::_sql(QSqlQuery ql)  {


std::vector<Mieter*> _liste;

    while(ql.next()){

        int id = (ql.value("PersonID")).toInt();
        mieter_instanz = new Mieter(id);

        mieter_instanz->set_berechtigung(static_cast<Berechtigung>(ql.value("Berechtigung").toInt()));
        mieter_instanz->set_vname(ql.value("Vorname").toString());
        mieter_instanz->set_nname(ql.value("Nachname").toString());
        QString geb_str = ql.value("Geburtsdatum").toString();
        QDate geb = QDate::fromString(geb_str, "dd.MM.yyyy");
        mieter_instanz->set_geb(geb);
        mieter_instanz->set_geschlecht(static_cast<Geschlecht>(ql.value("Geschlecht").toInt()));
        mieter_instanz->set_strasse(ql.value("Straße").toString());
        mieter_instanz->set_hausnummer(ql.value("HausNr").toString());
        mieter_instanz->set_plz(ql.value("PLZ").toString());
        mieter_instanz->set_wohnort(ql.value("Stadt").toString());
        mieter_instanz->set_email(ql.value("Email").toString());
        mieter_instanz->set_telnr(ql.value("TelefonNr").toString());
        mieter_instanz->set_fuehrerschein_klasse(ql.value("Führerscheinklasse").toString());
        //!werte in den vektor pushen


        _liste.push_back(mieter_instanz);

    }
    //!rückgabe
    return _liste;

}


bool Mieterverwaltung::mieter_ist_registriert(Mieter &obj) const
{
    QSqlQuery qm = db->get_mieter_alle();
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

