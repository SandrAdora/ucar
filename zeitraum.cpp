#include "zeitraum.h"

Zeitraum::Zeitraum()
{

}

Zeitraum::Zeitraum(QTime b, QTime e) {
    beginn = b;
    ende = e;
}

Zeitraum::~Zeitraum() {

}

Zeitraum & Zeitraum::operator=(const Zeitraum &right) {
    if(this != &right) {
        beginn = right.beginn;
        ende = right.ende;
    }
    return *this;
}

QTime Zeitraum::get_beginn() {
    return beginn;
}

void Zeitraum::set_beginn(QTime t) {
    beginn = t;
}

QTime Zeitraum::get_ende() {
    return ende;
}

void Zeitraum::set_ende(QTime t) {
    ende = t;
}

QString int_toTag(int i) {
    QString ret = "Fehler";
    switch(i) {
    case 0:
        ret = "Montag";
        break;
    case 1:
        ret = "Dienstag";
        break;
    case 2:
        ret = "Mittwoch";
        break;
    case 3:
        ret = "Donnerstag";
        break;
    case 4:
        ret = "Freitag";
        break;
    case 5:
        ret = "Samstag";
        break;
    case 6:
        ret = "Sonntag";
        break;
    default:
        break;
    }
    return ret;
}
