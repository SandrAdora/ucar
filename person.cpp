
#include "person.h"





//konstruktor
Person::Person(){}


Person::Person( QString vn , QString nn ,QDate dat,Berechtigung berechtigung,Geschlecht geschlecht,
               QString str, QString hn, QString plz, QString wohnort,QString email, QString tel, QString pw)

{


    this->vorname = vn;
    this->nachname = nn;
    this->geburtsdatum = dat;
    this->person = berechtigung;
    this->geschlecht =geschlecht;
    adresse.set_strasse(str) ;
    adresse.set_hausnummer(hn );
    adresse.set_plz(plz);
    adresse.set_wohnort(wohnort);
    this->email = email;
    this->telnr = tel;
    this->passwort = pw;


}
Person::Person( int id, QString vn , QString nn ,QDate dat,Berechtigung berechtigung,Geschlecht geschlecht,
               QString str, QString hn, QString plz, QString wohnort,QString email, QString tel, QString pw)

{

    this->person_id = id;
    this->vorname = vn;
    this->nachname = nn;
    this->geburtsdatum = dat;
    this->person = berechtigung;
    this->geschlecht =geschlecht;
    adresse.set_strasse(str) ;
    adresse.set_hausnummer(hn );
    adresse.set_plz(plz);
    adresse.set_wohnort(wohnort);
    this->email = email;
    this->telnr = tel;
    this->passwort = pw;


}

//destructor
Person::~Person(){}

int Person::get_person_id()const
{
    return person_id;
}

//Personen relevante Daten
void Person::set_geb(QDate geb)
{

    if(!geb.isValid()) //prüft ob die eingabe richtig war
    {
        std::cerr<<"Das Geburtsdatum ist nicht gueltig!"<<std::endl;

    }
    int current_year = QDate::currentDate().year();
    //prüft ob die person über 18 ist
    if ((current_year - geb.year())< 18)
    {
        std::cerr<<"Sie muessen mindestens 18 Jahre alt sein, um ein Konto erstellen zu koennen."<< std::endl;
        return;
    }

    this->geburtsdatum = geb;
}

QString Person::get_vname() const
{
    return this->vorname;

}
void Person::set_vname(QString vn)
{
    this->vorname = vn;
}

QString Person::get_nname() const
{
    return this->nachname;

}
void Person::set_nname(QString nn)
{
    this->nachname = nn;
}
QDate Person::get_geb() const{
    return geburtsdatum; //Datum in leserlicher form
}

QString Person::get_geschlecht() const{

    if(this->geschlecht == Geschlecht::WEIBLICH)
        return "weiblich";
    else if(this->geschlecht == Geschlecht::MAENNLICH)
        return "maennlich";
    else if(this->geschlecht == Geschlecht::DIVERS)
        return "divers";
    else
        return "unbekannt";
}

Geschlecht Person::get_geschlecht_enum() const{
    return geschlecht;
}

void Person::set_geschlecht(Geschlecht geschlecht){
    //die funktion liefert einen wert zurück der das entsprechende Geschlecht wiederspiegelt
    this->geschlecht = geschlecht;
}


//Die Kontaktdaten der person

QString Person::get_telnr() const {return telnr;}
void Person::set_telnr(QString tel){
    this->telnr = tel;
}
QString Person::get_email() const {
    return email;
}
void Person::set_email(QString email){
    this->email = email;
}

//konvertiert strings in int werte
int toInt(QString word)
{
    if (word == "weiblich" )
    {
        return 0;
    }
    else if (word == "maennlich" )
    {
        return 1;
    }

    return 2;
}
//Konto bezogene Daten

QString Person::get_berechtigung() const {
    if (this->person == Berechtigung::MIETER)
    {
        return "mieter";
    }
    else if( this->person == Berechtigung::VERMIETER)
    {
        return "vermieter";
    }
    return "sonstiges";
}
void Person::set_berechtigung(Berechtigung art ){
    //wandelt den String in einer zahl um die die entsprechende Berechtigung darstellt
    this->person = art;
}
void Person::set_anschrift(QString str, QString hh, QString plz, QString wohnort){
    adresse.set_strasse(str);
    adresse.set_hausnummer(hh);
    adresse.set_plz(plz);
    adresse.set_wohnort(wohnort);
}
QString Person::get_anschrift() const{
    return adresse.get_strasse() + " "+ adresse.get_hausnummer() + "\n"
           + adresse.get_plz() + "," + adresse.get_wohnort();
}
