
#ifndef STELLPLATZ_H
#define STELLPLATZ_H

#include <QObject>
#include "adresse.h"
#include <QString>


class Stellplatz {
public:
    Stellplatz();
    Stellplatz(Adresse *standort, QString stellplatz, bool verfuegbar);
    Adresse * get_standort() const;
    void set_standort(Adresse *);
    QString get_stellplatz() const;
    void set_stellplatz(QString);
    bool is_verfuegbar() const;
    void set_verfuegbar(bool);
    /*void fahrzeug_einstellen(Fahrzeug *);
    void fahrzeug_entfernen(Fahrzeug *);
    QList<Fahrzeug*> get_parkende_fahrzeuge() const;*/

private:
    Adresse *standort;
    QString stellplatz;
    bool verfuegbar;
    //QList<Fahrzeug *> parkende_fahrzeuge;
};

#endif // STELLPLATZ_H
