
#ifndef RECHNUNG_H
#define RECHNUNG_H

#include <QMainWindow>
#include <QObject>
#include <QString>
#include <QDate>
//#include "buchung.h"
#include "mieterverwaltung.h"
#include "verleih.h"

class Rechnung : public QObject
{
public:
    Rechnung();
    //Rechnung(double, double , Buchung *f , bool , int );
    Rechnung(double, double , double , int );


    double get_kilometer() const;
    double get_tankstand() const;
    double get_betrag() const;
    int get_rechnung_id() const;
    //Buchung * get_akt_buchung();

    void set_kilometer(double);
    void set_betrag(double);
    void set_tankstand(double);
    //void set_akt_buchung(Buchung *);

    virtual void printRechnungsdaten() const;

    QString print_daten();

    ~Rechnung();

    double rechnung_erstellen(QTime , QTime , Mieter& ,  bool, Verleih& );

private:
    //Buchung *akt_buchung;;
    double betrag;
    double kilometer;
    double tankstand;
    int rechnung_id;
};

#endif // RECHNUNG_H
