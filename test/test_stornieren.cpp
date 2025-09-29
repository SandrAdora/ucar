#include "gtest/gtest.h"
#include "../buchungsverwaltung.h"

struct TestStorno: public ::testing::Test {
    int fahrzeug_id = 1;    //gültiger Eintrag in Datenbank
    int vermieter_id = 1;   //Vermieter zu Fahrzeug mit ID 1
    int mieter_id = 2;      //gültiger Eintrag in Datenbank
    int buchung_id = 3;  //gültiger Eintrag in Datenbank

    //gültige Uhrzeit wird bereits bei der Suche überprüft, kann hier also beliebig sein
    QDateTime beginn = QDateTime::fromString("23.05.2023 14:00:00", "dd.MM.yyyy hh:mm:ss");
    QDateTime ende = QDateTime::fromString("23.05.2023 20:00:00", "dd.MM.yyyy hh:mm:ss");

    Buchungsverwaltung *verwaltung = new Buchungsverwaltung();
    Datenbank_verbindung * db;

};

TEST_F(TestStorno, TestBuchungStornierenIDRichtig) {
    bool result = verwaltung->buchung_stornieren(buchung_id);
    EXPECT_TRUE(result);
}

TEST_F(TestStorno, TestBuchungStornierenIDFalsch) {
    buchung_id= -1;
    bool result = verwaltung->buchung_stornieren(buchung_id);
    EXPECT_FALSE(result);
}
