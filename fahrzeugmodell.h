#ifndef FAHRZEUGMODELL_H
#define FAHRZEUGMODELL_H

#include <QString>

enum typ {
    CABRIO,
    KLEINWAGEN,
    LIMOUSINE,
    KOMBI,
    MINIVAN,
    SUV
};

class Fahrzeugmodell
{
    enum typ fahrzeug_typ;
    QString fahrzeug_art = "";

public:
    Fahrzeugmodell();
    Fahrzeugmodell(enum typ, QString);
    ~Fahrzeugmodell();
    enum typ get_fahrzeug_typ();
    void set_fahrzeug_typ(enum typ);
    QString get_fahrzeug_art();
    void set_fahrzeug_art(QString);

    Fahrzeugmodell & operator=(const Fahrzeugmodell &);
    int fahrzeugmodell_string_zu_int(QString fahrzeugtyp);
};

int typ_toInt(QString);
enum typ int_toTyp(int);
QString typ_toString(enum typ);

#endif // FAHRZEUGMODELL_H
