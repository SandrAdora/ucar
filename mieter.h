
#ifndef MIETER_H
#define MIETER_H
#include "person.h"
#include "fahrzeug.h"
#include <QDebug>

class Mieter : public Person, public Adresse
{
public:

    Mieter();
    Mieter( QString vn , QString nn ,QDate dat, Berechtigung berechtigung, Geschlecht geschlecht, QString str, QString hn, QString plz,
           QString wohnort,QString email, QString tel, QString pw, QString fueherschein_klasse);
    Mieter( int id, QString vn , QString nn ,QDate dat, Berechtigung berechtigung, Geschlecht geschlecht, QString str, QString hn, QString plz,
           QString wohnort,QString email, QString tel, QString pw, QString fueherschein_klasse);
    Mieter(int);


    //setter und getter methoden
    QString get_fuehrerschein_klasse() const;
    void set_fuehrerschein_klasse(QString fuehrerschein_klasse);


    //virtuelle Methoden
    QString print_person() const  override;
    void set_passwort(QString pw) override;
    QString get_passwort() const override;

protected:
    QString fuehrerschein_klasse ;
};

#endif // MIETER_H
