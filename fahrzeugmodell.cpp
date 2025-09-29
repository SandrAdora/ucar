#include "fahrzeugmodell.h"

Fahrzeugmodell::Fahrzeugmodell()
{

}

Fahrzeugmodell::Fahrzeugmodell(enum typ typ, QString art) {
    fahrzeug_typ = typ;
    fahrzeug_art = art;
}

Fahrzeugmodell::~Fahrzeugmodell() {

}

Fahrzeugmodell & Fahrzeugmodell::operator=(const Fahrzeugmodell &right) {
    if(this != &right) {
        fahrzeug_typ = right.fahrzeug_typ;
        fahrzeug_art = right.fahrzeug_art;
    }
    return *this;
}

enum typ Fahrzeugmodell::get_fahrzeug_typ() {
    return fahrzeug_typ;
}

void Fahrzeugmodell::set_fahrzeug_typ(enum typ t) {
    fahrzeug_typ = t;
}

QString Fahrzeugmodell::get_fahrzeug_art() {
    return fahrzeug_art;
}

void Fahrzeugmodell::set_fahrzeug_art(QString s) {
    fahrzeug_art = s;
}

int typ_toInt(QString t) {
    int ret = -1;
    if(t == "Cabrio" || t=="CABRIO") {
        ret = 0;
    } else if(t == "Kleinwagen" || t=="KLEINWAGEN") {
        ret = 1;
    } else if (t == "Limousine" || t== "LIMOUSINE"){
        ret = 2;
    } else if(t == "Kombi" || t=="KOMBI") {
        ret = 3;
    } else if(t == "Minivan" || t=="MINIVAN") {
        ret = 4;
    } else if(t == "SUV") {
        ret = 5;
    }
    return ret;
}

enum typ int_toTyp(int i) {
    enum typ ret;
    switch(i) {
    case 0:
        ret = CABRIO;
        break;
    case 1:
        ret = KLEINWAGEN;
        break;
    case 2:
        ret = LIMOUSINE;
        break;
    case 3:
        ret = KOMBI;
        break;
    case 4:
        ret = MINIVAN;
        break;
    case 5:
        ret = SUV;
        break;
    default:
        ret = KLEINWAGEN;
        break;
    }
    return ret;
}

QString typ_toString(enum typ t) {
    QString ret;
    switch(t) {
    case CABRIO:
        ret = "Cabrio";
        break;
    case KLEINWAGEN:
        ret = "Kleinwagen";
        break;
    case LIMOUSINE:
        ret = "Limousine";
        break;
    case KOMBI:
        ret = "Kombi";
        break;
    case MINIVAN:
        ret = "Minivan";
        break;
    case SUV:
        ret = "SUV";
        break;
    default:
        ret = "Kleinwagen";
        break;
    }
    return ret;
}

int Fahrzeugmodell::fahrzeugmodell_string_zu_int(QString fahrzeugtyp) {
    //Umwandeln von String Fahrzeugtyp zu int
    fahrzeugtyp=fahrzeugtyp.toUpper();
    int fmodell=-1;
    if(fahrzeugtyp=="CABRIO") {
        fmodell=0;
    }else { if(fahrzeugtyp=="KLEINWAGEN") {
            fmodell=1;
        }else { if(fahrzeugtyp=="LIMOUSINE") {
                fmodell=2;
            }else { if(fahrzeugtyp=="KOMBI") {
                    fmodell=3;
                }else { if(fahrzeugtyp=="MINIVAN") {
                        fmodell=4;
                    }else { if(fahrzeugtyp=="SUV") {
                            fmodell=5;
                        }
                    }
                }
            }
        }
    }
    return fmodell;
}

