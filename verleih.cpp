
#include "verleih.h"



Verleih::Verleih(){
}

Verleih::Verleih(QDateTime abholDatum, QDateTime rueckgabeDatum, Person *mieter, double km, double tank)
    : m_abholdatum(abholDatum), m_rueckgabeDatum(rueckgabeDatum), mieter(mieter), m_km(km), m_tank(tank) {}

Verleih::Verleih(QDateTime abholDatum, QDateTime rueckgabeDatum, int id)
    : m_abholdatum(abholDatum), m_rueckgabeDatum(rueckgabeDatum), m_id(id) {}

QString Verleih::print_daten() {
    QString abholung_str = m_abholdatum.toString();
    QString rueckgabe_str = m_rueckgabeDatum.toString();
    QString text = "Gefahrener Zeitraum:\n" + abholung_str + " bis " + rueckgabe_str;
    return text;
}

void Verleih::set_verleihdatum(QDateTime datum)
{
    m_verleihDatum = datum;
}

/*void Verleih::set_buchungsdatum(Buchung *buchung)
{
    m_buchungsDatum = buchung;
}*/

void Verleih::set_rueckgabedatum(QDateTime datum)
{
    m_rueckgabeDatum = datum;
}

void Verleih::set_abholdatum(QDateTime datum)
{
    m_abholdatum = datum;
}

void Verleih::set_mieter(Person *m)
{
    mieter = m;
}

void Verleih::set_km(double km)
{
    m_km = km;
}

void Verleih::set_tank(double tank)
{
    m_tank = tank;
}

QDateTime Verleih::get_verleihdatum() const
{
    return m_verleihDatum;
}

/*Buchung * Verleih::get_buchungsdatum() const
{
    return m_buchungsDatum;
}*/

QDateTime Verleih::get_abholdatum() const
{
    return m_abholdatum;
}

QDateTime Verleih::get_rueckgabedatum() const
{
    return m_rueckgabeDatum;
}

Person * Verleih::get_mieter() const
{
    return mieter;
}

double Verleih::get_km()
{
    return m_km;
}

double Verleih::get_tank()
{
    return m_tank;
}





