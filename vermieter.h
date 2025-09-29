#ifndef VERMIETER_H
#define VERMIETER_H

#include "person.h"
#include <vector>
#include <QDebug>
#include "fahrzeug.h"
#include "datenbank_verbindung.h"

class Vermieter : public Person, public Adresse
{

public:
    Vermieter();
    Vermieter( QString vn , QString nn ,QDate dat, Berechtigung berechtigung, Geschlecht geschlecht, QString str, QString hn, QString plz,
               QString wohnort,QString email, QString tel, QString pw);
    Vermieter( int id, QString vn , QString nn ,QDate dat, Berechtigung berechtigung, Geschlecht geschlecht, QString str, QString hn, QString plz,
               QString wohnort,QString email, QString tel, QString pw);
    Vermieter(int);
    ~Vermieter();

    //virtuelle Methoden
    QString print_person() const  override;
    void set_passwort(QString pw) override;
    QString get_passwort() const override;

    //Setter und Getter Methoden
    QString get_fueherscheinklasse() const;

    //Methoden der Klasse
   std::vector<Fahrzeug> fahrzeug_registrieren( int, QString, enum typ, QString, QString, QString, QString,enum schaden, std::array<Zeitraum *, 7>, int);
   


protected:
    QString fuehrerscheinklasse;
    std::vector<Fahrzeug *> fahrzeug_liste{};

};
#endif // VERMIETER_H
