#include "gtest/gtest.h"
#include "../fahrzeugverwaltung.h"
#include "../buchung.h"

struct TestSuche : public ::testing::Test {
    Fahrzeugverwaltung *verwaltung = new Fahrzeugverwaltung();
    Datenbank_verbindung *db = db->get_instanz();
    std::vector<Fahrzeug *> vec;

    //gültige Werte aus Datenbank zu Fahrzeug mit ID 10
    int fahrzeug_id = 10;
    int sitze = 4;
    int typ = 1;
    QString stadt = "Regensburg";

    //freies Zeitfenster
    QDate mittwoch = QDate::fromString("14.06.2023", "dd.MM.yyyy");
    QTime beginn = QTime::fromString("14:00:00", "hh:mm:ss");
    QTime ende = QTime::fromString("20:00:00", "hh:mm:ss");

    //Default-Werte für Datum und Zeit (sind immer gesetzt)
    QDate d_def= QDate::currentDate();
    int hour = (QTime::currentTime()).hour();
    QTime b_def = QTime(hour + 1, 0);
    QTime e_def = QTime(hour + 2, 0);

    bool ergebnis_pruefen(std::vector<Fahrzeug *> vec);
};

bool TestSuche::ergebnis_pruefen(std::vector<Fahrzeug *> vec) {
    bool result = false;
    for(auto item : vec) {
        if(item->get_fahrzeug_id() == fahrzeug_id) {
            result = true;
            break;
        }
    }
    return result;
}

TEST_F(TestSuche, TestSucheDefault) {
    vec = verwaltung->fahrzeug_suchen(2, "", -1, d_def, b_def, e_def);
    bool result = ergebnis_pruefen(vec);
    EXPECT_FALSE(result);
}

TEST_F(TestSuche, TestSucheAlleWerte) {
    vec = verwaltung->fahrzeug_suchen(sitze, stadt, typ, mittwoch, beginn, ende);
    bool result = ergebnis_pruefen(vec);
    EXPECT_TRUE(result);
}

TEST_F(TestSuche, TestSucheNurDatumZeit) {
    vec = verwaltung->fahrzeug_suchen(2, "", -1, mittwoch, beginn, ende);
    bool result = ergebnis_pruefen(vec);
    EXPECT_TRUE(result);
}

TEST_F(TestSuche, TestSucheDatumFalsch) {
    QDate montag = QDate::fromString("12.06.2023", "dd.MM.yyyy");
    vec = verwaltung->fahrzeug_suchen(sitze, stadt, typ, montag, beginn, ende);
    bool result = ergebnis_pruefen(vec);
    EXPECT_FALSE(result);
}

TEST_F(TestSuche, TestSucheZeitFalsch) {
    QTime b = QTime::fromString("08:00:00", "hh:mm:ss");
    QTime e = QTime::fromString("12:00:00", "hh:mm:ss");
    vec = verwaltung->fahrzeug_suchen(sitze, stadt, typ, mittwoch, b, e);
    bool result = ergebnis_pruefen(vec);
    EXPECT_FALSE(result);
}

TEST_F(TestSuche, TestSucheZeitGebucht) {
    //bereits gebuchtes Zeitfenster
    QDate freitag = QDate::fromString("16.06.2023", "dd.MM.yyyy");
    QTime b = QTime::fromString("09:00:00", "hh:mm:ss");
    QTime e = QTime::fromString("12:00:00", "hh:mm:ss");
    vec = verwaltung->fahrzeug_suchen(sitze, stadt, typ, freitag, b, e);
    bool result = ergebnis_pruefen(vec);
    EXPECT_FALSE(result);
}

TEST_F(TestSuche, TestSucheDefaultNurTyp) {
    vec = verwaltung->fahrzeug_suchen(2, "", typ, d_def, b_def, e_def);
    bool result = ergebnis_pruefen(vec);
    EXPECT_FALSE(result);
}

TEST_F(TestSuche, TestSucheTypFalsch) {
    vec = verwaltung->fahrzeug_suchen(sitze, stadt, CABRIO, mittwoch, beginn, ende);
    bool result = ergebnis_pruefen(vec);
    EXPECT_FALSE(result);
}

TEST_F(TestSuche, TestSucheDefaultNurStadt) {
    vec = verwaltung->fahrzeug_suchen(2, stadt, -1, d_def, b_def, e_def);
    bool result = ergebnis_pruefen(vec);
    EXPECT_FALSE(result);
}

TEST_F(TestSuche, TestSucheStadtFalsch) {
    vec = verwaltung->fahrzeug_suchen(sitze, "München", typ, mittwoch, beginn, ende);
    bool result = ergebnis_pruefen(vec);
    EXPECT_FALSE(result);
}

TEST_F(TestSuche, TestSucheDefaultNurSitze) {
    vec = verwaltung->fahrzeug_suchen(4, "", -1, d_def, b_def, e_def);
    bool result = ergebnis_pruefen(vec);
    EXPECT_FALSE(result);
}

TEST_F(TestSuche, TestSucheSitzeFalsch) {
    vec = verwaltung->fahrzeug_suchen(8, stadt, typ, mittwoch, beginn, ende);
    bool result = ergebnis_pruefen(vec);
    EXPECT_FALSE(result);
}
