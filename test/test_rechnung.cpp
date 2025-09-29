#include "gtest/gtest.h"
#include "../buchungsverwaltung.h"
#include <QDateTime>

struct TestRechnung : public ::testing::Test {
    int rechnung_id = 1;  // Gültige Rechnung ID
    int buchung_id = 1; // Gültige Buchungs-ID
    Buchungsverwaltung *verwaltung = new Buchungsverwaltung();
    Verleih *verleih = new Verleih();  // Erstelle einen Verleih-Objekt mit gültigen Werten
    Buchung *buchung = new Buchung();  // Erstelle ein Buchungs-Objekt
    Fahrzeug *fahrzeug = new Fahrzeug();  // Erstelle ein Fahrzeug-Objekt
    Mieter *mieter = new Mieter();  // Erstelle einen Mieter-Objekt
};

TEST_F(TestRechnung, TestRechnungZuBuchungGültigeID) {
    bool result = verwaltung->rechnung_zu_buchung(rechnung_id);
    EXPECT_TRUE(result);
}

TEST_F(TestRechnung, TestRechnungZuBuchungUngültigeID) {
    rechnung_id = -1;
    bool result = verwaltung->rechnung_zu_buchung(rechnung_id);
    EXPECT_FALSE(result);
}

TEST_F(TestRechnung, TestRechnungErstellenMitVerleih) {
    verleih->set_km(100.0);
    verleih->set_tank(10.0);
    buchung->set_akt_fahrzeug(fahrzeug); // Setze das Fahrzeug-Objekt in der Buchung
    buchung->set_verleih(verleih);
    double rechnungsbetrag = verwaltung->rechnung_erstellen(verleih, buchung);
    EXPECT_GT(rechnungsbetrag, 0.0);
}

TEST_F(TestRechnung, TestBuchungAbschliessen) {
    // Erstelle einen Verleih mit gültigen Werten
    QDateTime abholdatum = QDateTime::currentDateTime();
    QDateTime rueckgabedatum = abholdatum.addDays(7);
    verleih->set_abholdatum(abholdatum);
    verleih->set_rueckgabedatum(rueckgabedatum);
    bool result = verwaltung->buchung_abschliessen(verleih, buchung, mieter);

    // Überprüfe das Ergebnis
    EXPECT_TRUE(result);
    EXPECT_EQ(buchung->get_status(), Buchungsstatus::abgeschlossen);
}
