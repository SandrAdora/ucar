
#include "rechnung.h"
#include "verleih.h"
#include <iostream>
#include <QString>

Rechnung::Rechnung(double bet, double kil,  double tank, int rech_id):
    betrag{bet},kilometer{kil},tankstand{tank}, rechnung_id{rech_id}
{

}


Rechnung::~Rechnung() {}

/*Buchung * Rechnung::get_akt_buchung() {
    return akt_buchung;
}*/

QString Rechnung::print_daten() {
    QString km_str;
    km_str.setNum(kilometer, 'f', 2);
    QString tank_str;
    tank_str.setNum(tankstand, 'f', 2);
    QString betrag_str;
    betrag_str.setNum(betrag, 'f', 2);
    QString text = "Kilometer gefahren: " + km_str + "\nTankfüllung verbraucht: " + tank_str
                 + "\nBetrag: " + betrag_str;
    return text;
}

 double Rechnung::get_kilometer() const {
    return this->kilometer;
 }

double Rechnung::get_tankstand() const {
    return this->tankstand;
}

double Rechnung::get_betrag() const {
    return this->betrag;
}

int Rechnung::get_rechnung_id() const {
    return this->rechnung_id;
}

/*void Rechnung::set_akt_buchung(Buchung *b) {
    akt_buchung= b;
}*/

/*void Rechnung::set_akt_buchung(Buchung *b) {
    akt_buchung= b;
}*/


 void Rechnung::set_kilometer(double kil) {
    if (kil < this->kilometer) {
            std::cerr << "Der Kilometerstand darf nicht kleiner als der bisherige Stand sein!" << std::endl;
            return;
    }
    this->kilometer = kil;
 }

// Wenn der Tank voll ist, werden keine zusätzlichen Kosten berechnet. Wenn es nicht der Fall ist, werden pauschal 100 euro mehr berechnen.
void Rechnung::set_betrag(double bet) {
    betrag = bet;
}



    void Rechnung::set_tankstand(double tank)
    {

    if ((tank = false))
    {
        std::cerr << "Der Tank ist leer" << std::endl;
    }
    else{

        std::cerr << " Der Tank ist voll" << std::endl;

    }

}
    void Rechnung::printRechnungsdaten() const
    {
        std::cout << "Rechnungsdaten:" << std::endl;
        std::cout << "tankstand: " << get_tankstand()<< std::endl;

        std::cout << std::endl;
        //std::cout <<"Rechnung_ID: " << rechnung_id << std::endl;
    }



