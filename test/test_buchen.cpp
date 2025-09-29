 #include "gtest/gtest.h"
#include "../buchungsverwaltung.h"

#include <QDateTime>

struct TestBuchung: public ::testing::Test {
    int fahrzeug_id = 10;    //gültiger Eintrag in Datenbank
    int vermieter_id = 11;   //Vermieter zu Fahrzeug mit ID 10
    int mieter_id = 10;      //gültiger Eintrag in Datenbank
    int buchung_id = 21;     //Buchung zu Mieter mit ID 10 und Vermieter mit ID 11

    //gültige Uhrzeit wird bereits bei der Suche überprüft, kann hier also beliebig sein
    QDateTime beginn = QDateTime::fromString("21.06.2023 14:00:00", "dd.MM.yyyy hh:mm:ss");
    QDateTime ende = QDateTime::fromString("21.06.2023 20:00:00", "dd.MM.yyyy hh:mm:ss");

    Buchungsverwaltung *verwaltung = new Buchungsverwaltung();
    Datenbank_verbindung *db = db->get_instanz();
};

TEST_F(TestBuchung, TestBuchungAnlegenRichtig) {
    bool file_result = false;
    QString filename;
    filename.setNum(vermieter_id);
    filename.append(".txt");
    QFile file(filename);
    if(file.exists()) {
        QFile::remove(filename);
    }

    bool result = verwaltung->fahrzeug_buchen(fahrzeug_id, mieter_id, beginn, ende);
    EXPECT_TRUE(result);

    if(file.exists()) {
        file_result = true;
        QFile::remove(filename);
    }
    EXPECT_TRUE(file_result);
}

TEST_F(TestBuchung, TestBuchungAnlegenFahrzeugFalsch) {
    fahrzeug_id = -1;
    bool result = verwaltung->fahrzeug_buchen(fahrzeug_id, mieter_id, beginn, ende);
    EXPECT_FALSE(result);
}

TEST_F(TestBuchung, TestBuchungAnlegenMieterFalsch) {
    mieter_id = -1;
    bool result = verwaltung->fahrzeug_buchen(fahrzeug_id, mieter_id, beginn, ende);
    EXPECT_FALSE(result);
}

TEST_F(TestBuchung, TestStatusAendernBestaetigenIDRichtig) {
    bool file_result = false;
    QString filename;
    filename.setNum(mieter_id);
    filename.append(".txt");
    QFile file(filename);
    if(file.exists()) {
        QFile::remove(filename);
    }

    bool result = verwaltung->buchung_status_aendern(buchung_id, Buchungsstatus::bestaetigt);
    EXPECT_TRUE(result);

    if(file.exists()) {
        file_result = true;
        QFile::remove(filename);
    }
    EXPECT_TRUE(file_result);

    db->update_buchung_status(buchung_id, 0);
}

TEST_F(TestBuchung, TestStatusAendernBestaetigenIDFalsch) {
    buchung_id = -1;
    bool result = verwaltung->buchung_status_aendern(buchung_id, Buchungsstatus::bestaetigt);
    EXPECT_FALSE(result);
}

TEST_F(TestBuchung, TestStatusAendernAblehnenIDRichtig) {
    bool file_result = false;
    QString filename;
    filename.setNum(mieter_id);
    filename.append(".txt");
    QFile file(filename);
    if(file.exists()) {
        QFile::remove(filename);
    }

    bool result = verwaltung->buchung_status_aendern(buchung_id, Buchungsstatus::abgelehnt);
    EXPECT_TRUE(result);

    if(file.exists()) {
        file_result = true;
        QFile::remove(filename);
    }
    EXPECT_TRUE(file_result);

    db->update_buchung_status(buchung_id, 0);
}

TEST_F(TestBuchung, TestStatusAendernAblehnenIDFalsch) {
    buchung_id = -1;
    bool result = verwaltung->buchung_status_aendern(buchung_id, Buchungsstatus::abgelehnt);
    EXPECT_FALSE(result);

    db->update_buchung_status(buchung_id, 0);
}


