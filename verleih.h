
#ifndef VERLEIH_H
#define VERLEIH_H


#include <QObject>
#include <vector>
#include <QDateTime>
#include <QSqlQuery>
//#include "buchung.h"
#include "fahrzeug.h"
#include "mieter.h"
#include "datenbank_verbindung.h"


class Verleih {
public:
    Verleih();
    Verleih(QDateTime abholDatum, QDateTime rueckgabeDatum, Person *mieter, double km, double tank);
    Verleih(QDateTime abholdatum, QDateTime rueckgabeDatum, int id);
    bool fahrzeug_abholen(std::vector<Verleih>&, const std::string&, Fahrzeug&, const QDateTime&, int, const Person&, const QDateTime&);
    bool fahrzeug_zurueckbringen(std::vector<Verleih>&, const std::string&, Fahrzeug&, const QDateTime&, int, const Person&, const QDateTime&);
    void set_verleihdatum(QDateTime);
    //void set_buchungsdatum(Buchung *);
    void set_rueckgabedatum(QDateTime);
    void set_mieter(Person *);
    void set_km(double);
    void set_tank(double);
    QDateTime get_verleihdatum() const;
    //Buchung * get_buchungsdatum() const;
    QDateTime get_rueckgabedatum() const;
    Person * get_mieter() const;
    void set_abholdatum(QDateTime datum);
    QDateTime get_abholdatum() const;
    double get_km();
    double get_tank();
    QString print_daten();

    std::vector<Verleih* > verleih_abfragen(QSqlQuery );

private:
    QDateTime m_verleihDatum;
    //Buchung *m_buchungsDatum;
    QDateTime m_rueckgabeDatum;
    QDateTime m_abholdatum;
    Person *mieter;
    double m_km;
    double m_tank;
    int m_id;

};



#endif // VERLEIH_H
