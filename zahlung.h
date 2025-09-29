
#ifndef ZAHLUNG_H
#define ZAHLUNG_H


#include <QObject>
#include <buchung.h>
#include <QDate>

class Zahlung : public QObject
{
    Q_OBJECT
public:
    Zahlung();
    Zahlung(double betrag, QDate time, bool status);
    void set_betrag(double betrag);
    void set_time(QDate time);
    void set_status(bool status);
    void set_buchung(Buchung* buchung);
    double get_betrag() const;
    QDate get_time() const;
    bool get_status() const;
    Buchung* get_buchung() const;

private:
    double m_betrag;
    QDate m_time;
    bool m_status;
    Buchung* m_buchung;
};



#endif // ZAHLUNG_H
