#include "gtest/gtest.h"
#include "../datenbank_verbindung.h"
#include "QtSql/QSqlQuery"
#include "QVariant"
#include "QDebug"


struct TestDatenbankverbindung: public ::testing::Test {
    //Var definieren
    Datenbank_verbindung * db;


    QString nname= "Meier";
    QString vname = "Margit";
    QDate geb = QDate::fromString("24.05.1998","dd.MM.yyyy");
    QString pw = "12345678";
    QString email = "mmeier@gmail.com";
    QString telnr ="01419831201";
    QString stadt="München";
    QString plz= "95321";
    QString str = "Münchenerstraße";
    QString hnr= "13";
    QString fklasse="B";
    int geschlecht=1;
    int berechtigung= 0;
    int buchungid=4;
    double betrag = 20.7;
    double km= 86;
    double tankstand = 0.5;
    int rechnungid=1;
    int pid=1;

    void SetUp() override {
        db=db->get_instanz();
    }

};



//TEST_F(TestFahrzeugReg, TestFahrzeugRegistrierenIDRichtig) {

//get_instanz:
TEST_F(TestDatenbankverbindung, TestGetInstanz) {
    EXPECT_NE(db, nullptr);
}


//addPerson:
TEST_F(TestDatenbankverbindung, TestAddPersonIDRichtig) {
    pid=db-> add_person (nname, vname, geb, geschlecht, pw,  email, telnr, stadt, plz, str, hnr, fklasse, berechtigung);
    EXPECT_GT(pid, 0);
}

TEST_F(TestDatenbankverbindung, TestAddPersonIDFalsch) {
    berechtigung=5;
    pid=db-> add_person (nname, vname, geb, geschlecht, pw,  email, telnr, stadt, plz, str, hnr, fklasse, berechtigung);
    EXPECT_EQ(pid, -1);
}


//get_person:
TEST_F(TestDatenbankverbindung, TestGetPersonIDExistiert) {
    QSqlQuery q=db->get_person(pid);
    if(q.next()) {
        EXPECT_EQ(q.value("PersonID").toInt(), 1) << "pid = " << testing::PrintToString(pid);
        EXPECT_EQ(q.value("Nachname").toString(), "Mustermann");
        EXPECT_EQ(q.value("Vorname").toString(), "Max");
        EXPECT_EQ(q.value("Geburtsdatum").toString(), "2000-05-03");
        EXPECT_EQ(q.value("Geschlecht").toInt(), 0);
        EXPECT_EQ(q.value("Passwort").toString(), "password1234");
        EXPECT_EQ(q.value("Email").toString(), "mustermannmax@gmail.com");
        EXPECT_EQ(q.value("TelefonNr").toString(), "32576256");
        EXPECT_EQ(q.value("Stadt").toString(), "Regensburg");
        EXPECT_EQ(q.value("PLZ").toString(), "93053");
        EXPECT_EQ(q.value("Straße").toString(), "Straße1");
        EXPECT_EQ(q.value("HausNr").toString(), "45");
        EXPECT_EQ(q.value("Führerscheinklasse").toString(), "B");
        EXPECT_EQ(q.value("Berechtigung").toInt(), 0);
    } else {
        ADD_FAILURE();
    }

}

TEST_F(TestDatenbankverbindung, TestGetPersonIDExistiertNicht) {
    pid=-1;
    QSqlQuery q=db->get_person(pid);
    EXPECT_FALSE(q.next());
}


//get_person_zu_fahrzeug
TEST_F(TestDatenbankverbindung, TestGetPersonZuFahrzeugIDExistiert) {
    pid=5;
    QSqlQuery q=db->get_person_zu_fahrzeug(pid);
    if(q.next()) {
        EXPECT_EQ(q.value("PersonID").toInt(), 4);
    } else {
        ADD_FAILURE();
    }
}

TEST_F(TestDatenbankverbindung, TestGetPersonZuFahrzeugIDExistiertNicht) {
    pid=-1;
    QSqlQuery q=db->get_fahrzeug_zu_person(-1);
    EXPECT_FALSE(q.next());
}


//get_mieter_email_mit_passwort:
TEST_F(TestDatenbankverbindung, TestGetMieterEmailMItPasswortIDExistiert) {
    email= "manni@master.de";
    pw= "pw1234";
    QSqlQuery q=db->get_mieter_email_mit_passwort(email, pw);
    if(q.next()) {
        EXPECT_EQ(q.value("PersonID").toInt(), 4);
    } else {
        ADD_FAILURE();
    }
}

TEST_F(TestDatenbankverbindung, TestGetMieterEmailMItPasswortIDExistiertNicht) {
    email= "-1";
    pw= "-1";
    QSqlQuery q=db->get_mieter_email_mit_passwort(email, pw);
    EXPECT_FALSE(q.next());
}


//add_rechnung:
TEST_F(TestDatenbankverbindung, TestAddRechnungIDRichtig) {
    rechnungid=db-> add_rechnung (buchungid, betrag, km, tankstand);
    EXPECT_GT(rechnungid, 0);
}

TEST_F(TestDatenbankverbindung, TestAddRechnungIDFalsch) {
    km=-1;
    int rid=db-> add_rechnung (buchungid, betrag, km, tankstand);
    EXPECT_EQ(rid, -1);
}

TEST_F(TestDatenbankverbindung, TestAddRechnungBuchungIDFalsch) {
    buchungid=-1;
    int rid=db-> add_rechnung (buchungid, betrag, km, tankstand);
    EXPECT_EQ(rid, -2)<< "rid = " << rid;
}


//buchung_update:
TEST_F(TestDatenbankverbindung, TestUpdateBuchungRechnungIDRichtig) {
    bool success=db->update_buchung_rechnung(buchungid, rechnungid);
    EXPECT_TRUE(success);
}

TEST_F(TestDatenbankverbindung, TestUpdateBuchungRechnungBuchungIDFalsch) {
    buchungid=-1;
    bool success=db->update_buchung_rechnung(buchungid, rechnungid);
    EXPECT_FALSE(success);
}

TEST_F(TestDatenbankverbindung, TestUpdateBuchungRechnungRechnungIDFalsch) {
    rechnungid=-1;
    bool success=db->update_buchung_rechnung(buchungid, rechnungid);
    EXPECT_FALSE(success);
}
