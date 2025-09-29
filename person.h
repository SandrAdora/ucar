#ifndef PERSON_H
#define PERSON_H


#include <QMainWindow>
#include <QObject>
#include <QString>
#include <QDate>
#include <iostream>
#include <cctype>
#include "adresse.h"



//enumerations
enum class Geschlecht{
    MAENNLICH, WEIBLICH, DIVERS, UNBEKANNT
};
enum class Berechtigung{
    MIETER, VERMIETER, SONSTIGES
};

class Person
{
public:

    Person() ; //default entfernt
    Person(QString vn , QString nn ,QDate dat, Berechtigung berechtigung, Geschlecht geschlecht,
           QString str, QString hn, QString plz, QString wohnort,QString email, QString tel, QString pw );

    Person(int id, QString vn , QString nn ,QDate dat, Berechtigung berechtigung, Geschlecht geschlecht,
           QString str, QString hn, QString plz, QString wohnort,QString email, QString tel, QString pw);

    //destructor
    ~Person();

    //virtuelle Methoden


    virtual QString print_person() const = 0;
    virtual void set_passwort(QString pw) = 0;
    virtual QString get_passwort() const = 0;



    //Methoden der klasse
    int get_person_id()const ;
    QString get_berechtigung() const;
    void set_berechtigung(Berechtigung);
    QString get_vname() const;
    void set_vname(QString vn) ;
    QString get_nname() const ;
    void set_nname(QString nn) ;
    QDate get_geb() const ;
    void set_geb(QDate geb) ;
    QString get_geschlecht()const;
    Geschlecht get_geschlecht_enum() const;
    void set_geschlecht(Geschlecht );
    QString get_email() const ;
    void set_email(QString email);
    void set_anschrift(QString str, QString hh, QString plz, QString wohnort);
    QString get_anschrift() const;
    QString get_telnr() const;
    void set_telnr(QString tel);

    //Hilfsfunktion
    //konvertiert strings in int werte
    int toInt(QString);





signals:

protected:
    int person_id;
    //die Berechtigung ob die person ein vermieter oder mieter ist
    Berechtigung person;
    QString vorname;
    QString nachname;
    QDate geburtsdatum;
    Geschlecht geschlecht ;
    QString email;
    QString telnr;
    QString passwort;


    Adresse adresse;


};


#endif // PERSON_H
