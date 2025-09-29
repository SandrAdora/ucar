#include "vermieter.h"


Vermieter::Vermieter() : Person( ){}



Vermieter::Vermieter( QString vn , QString nn ,QDate dat, Berechtigung berechtigung, Geschlecht geschlecht,
                      QString str, QString hn, QString plz, QString wohnort,QString email, QString tel, QString pw)
    : Person( vn, nn ,dat,berechtigung, geschlecht, str, hn, plz, wohnort, email, tel, pw)

{
    this->fuehrerscheinklasse = "B";

}

Vermieter::Vermieter(int id, QString vn , QString nn ,QDate dat, Berechtigung berechtigung, Geschlecht geschlecht,
                      QString str, QString hn, QString plz, QString wohnort,QString email, QString tel, QString pw)
    : Person(id, vn, nn ,dat,berechtigung, geschlecht, str, hn, plz, wohnort, email, tel, pw)
{
    this->fuehrerscheinklasse = "B";

}

Vermieter::Vermieter(int id)
{
    //Anwendung bei der suche einer bestimmen person in der verwaltungsklasse
    person_id = id;

}

//Destructor
Vermieter::~Vermieter(){}


QString Vermieter::print_person() const {

    QDate date = get_geb();
    QString date_tostring = date.toString("dd.MM.yyyy");

    QString person_info = "Vermieter:\n\nName: "+ get_vname() + " "+
            get_nname() + "\nGeburtsdatum: " + date_tostring + "\nGeschlecht: " + get_geschlecht() +
            "\nAdresse: " + get_strasse() + " " + get_hausnummer()
            +", "+ get_plz() + " " + get_wohnort() +
            "\nTelefon: " + get_telnr() + "\nEmail: " + get_email();
    return person_info;
}

QString Vermieter::get_fueherscheinklasse() const{
    return fuehrerscheinklasse;
}


void Vermieter::set_passwort(QString pw )
{

    bool is_up = false;
    //Prüft die länge des Passworts
    if (pw.length() < 6)
    {
        std::cerr<<"Das Passwort muss mindestens 6 zeichen lang sein!!";
        return;
    }
    for (int i = 0; i < pw.length(); i++)
    {
        //prüft ob das Passwort mind. einen Großbuchstaben hat
        //der cast unsigned char gibt die zeichen als char zurück
        if(pw[i] >= 'A' || pw[i] <= 'Z')
        {
            //is_up auf true gesetzt wenn ein grossbuchstabe gefunden wurde
            is_up = true;
            //bricht die schleife ab
            break;
        }
    }

    //Prüft ob das Passwort einen Großbuchstaben hat
    if (!is_up)
    {
        //Error signal wenn das Passwort aus kleinbuchstaben besteht
        std::cerr<<"Das Passwort muss mindestens einen Grossbuchstaben besitzen." << std::endl;
        //beendet die Funktion
        return;
    }
    //eine Zusweisung des passwortes wenn alle bedingungen erfüllt sind
    passwort = pw;



}
QString Vermieter::get_passwort() const {
    return passwort;
}



