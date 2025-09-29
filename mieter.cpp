#include "mieter.h"




//konstruktor definition
Mieter ::Mieter() : Person(){}

Mieter::Mieter( QString vn , QString nn ,QDate dat, Berechtigung berechtigung, Geschlecht geschlecht, QString str, QString hn, QString plz,
               QString wohnort,QString email, QString tel, QString pw , QString fueherschein_klasse) :
    Person( vn, nn, dat, berechtigung, geschlecht, str, hn, plz, wohnort, email, tel, pw)
{
    this->fuehrerschein_klasse =  fueherschein_klasse;

}
Mieter::Mieter( int id, QString vn , QString nn ,QDate dat, Berechtigung berechtigung, Geschlecht geschlecht, QString str, QString hn, QString plz,
               QString wohnort,QString email, QString tel, QString pw , QString fueherschein_klasse) :
    Person( id, vn, nn, dat, berechtigung, geschlecht, str, hn, plz, wohnort, email, tel, pw)
{
    this->fuehrerschein_klasse =  fueherschein_klasse;

}


Mieter::Mieter(int id )
{
    //Anwendung: Suche nach einer bestimmten Mieter
    person_id = id;
}

QString Mieter::print_person() const {

    QDate date = get_geb();
    QString date_tostring = date.toString("dd.MM.yyyy");

    QString person_info = "Mieter:\n\nName: "+ get_vname() + " "+
            get_nname() + "\nGeburtsdatum: " + date_tostring + "\nGeschlecht: " + get_geschlecht() +
            "\nAdresse: " + get_strasse() + " " + get_hausnummer()
            +", "+ get_plz() + " " + get_wohnort() +
            "\nTelefon: " + get_telnr() + "\nEmail: " + get_email();

    return person_info;
}

 void Mieter::set_passwort(QString pw){

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
        if(pw[i] <= 'Z')
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

        return;
    }

    passwort = pw;

 }

 QString Mieter::get_passwort() const {
    return passwort;
}

 //setter und getter definitionen
 QString Mieter::get_fuehrerschein_klasse() const{
     return fuehrerschein_klasse;
 }
 void Mieter::set_fuehrerschein_klasse(QString fuehrerschein_klasse){
     this->fuehrerschein_klasse = fuehrerschein_klasse;
 }



