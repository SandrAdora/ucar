
#include "zahlung.h"

Zahlung::Zahlung(){}

Zahlung::Zahlung(double betrag, QDate time, bool status)
{
    m_betrag = betrag;
    m_time = time;
    m_status = status;
    m_buchung = nullptr;
}

void Zahlung::set_betrag(double betrag)
{
    m_betrag = betrag;
}

void Zahlung::set_time(QDate time)
{
    m_time = time;
}

void Zahlung::set_status(bool status)
{
    m_status = status;
}

void Zahlung::set_buchung(Buchung* buchung)
{
    m_buchung = buchung;
}

double Zahlung::get_betrag() const
{
    return m_betrag;
}

QDate Zahlung::get_time() const
{
    return m_time;
}

bool Zahlung::get_status() const
{
    return m_status;
}

Buchung* Zahlung::get_buchung() const
{
    return m_buchung;
}

