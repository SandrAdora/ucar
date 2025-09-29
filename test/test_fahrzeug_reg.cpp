#include "gtest/gtest.h"
#include "../fahrzeugverwaltung.h"


struct TestFahrzeugReg: public ::testing::Test {
    //Var definieren
    Fahrzeugverwaltung * v = new Fahrzeugverwaltung();
    Zeitraum * z= new Zeitraum();

    QString kennzeichen= "M-AB431";
    QString marke = "Mercedes";
    QString fart = "Benz";
    QString farbe = "weiß";
    QString ftyp = "CABRIO";
    QString s ="München";
    QString plz= "95321";
    QString str = "Albertstr.";
    QString hnr= "13";
    int baujahr=2002;
    int plaetze=4;
    int beschaedigung=0;
    int parknr=3;
    QTime mo_st=QTime::fromString("10:00", "hh:mm");
    QTime mo_et = QTime::fromString("12:00", "hh:mm");
    QTime di_st= QTime::fromString("10:00", "hh:mm");
    QTime di_et = QTime::fromString("10:00", "hh:mm");
    QTime mi_st= QTime::fromString("0:00", "hh:mm");
    QTime mi_et = QTime::fromString("0:00", "hh:mm");
    QTime do_st= QTime::fromString("13:00", "hh:mm");
    QTime do_et = QTime::fromString("19:00", "hh:mm");
    QTime fr_st= QTime::fromString("10:00", "hh:mm");
    QTime fr_et =  QTime::fromString("08:00", "hh:mm");
    QTime sa_st= QTime::fromString("10:00", "hh:mm");
    QTime sa_et = QTime::fromString("17:00", "hh:mm");
    QTime so_st= QTime::fromString("10:00", "hh:mm");
    QTime so_et = QTime::fromString("10:00", "hh:mm");

    QTime startzeit = QTime::fromString("10:00", "hh:mm");
    QTime endzeit = QTime::fromString("18:00", "hh:mm");

};



TEST_F(TestFahrzeugReg, TestFahrzeugRegistrierenIDRichtig) {
    int fid=v->fahrzeug_registrieren(1, kennzeichen, marke, fart, farbe, baujahr, plaetze, ftyp, beschaedigung, s, plz, str, hnr, baujahr, mo_st, mo_et, di_st, di_et, mi_st, mi_et, do_st, do_et, fr_st, fr_et, sa_st, sa_et, so_st, so_et);
    EXPECT_EQ(fid, 0);
}

TEST_F(TestFahrzeugReg, TestFahrzeugRegistrierenFModellFalsch) {
    ftyp="-1";
    int fid=v->fahrzeug_registrieren(2, kennzeichen, marke, fart, farbe, baujahr, plaetze, ftyp, beschaedigung, s, plz, str, hnr, baujahr, mo_st, mo_et, di_st, di_et, mi_st, mi_et, do_st, do_et, fr_st, fr_et, sa_st, sa_et, so_st, so_et);
    EXPECT_EQ(fid, 1);
}

TEST_F(TestFahrzeugReg, TestFahrzeugRegistrierenFahrzeugExistiertBereits) {
    int fid=v->fahrzeug_registrieren(1, kennzeichen, marke, fart, farbe, baujahr, plaetze, ftyp, beschaedigung, s, plz, str, hnr, baujahr, mo_st, mo_et, di_st, di_et, mi_st, mi_et, do_st, do_et, fr_st, fr_et, sa_st, sa_et, so_st, so_et);
    EXPECT_EQ(fid, 2);
}

TEST_F(TestFahrzeugReg, TestFahrzeugRegistrierenPersonIDFalsch) {
    int fid=v->fahrzeug_registrieren(-1, kennzeichen, marke, fart, farbe, baujahr, plaetze, ftyp, beschaedigung, s, plz, str, hnr, baujahr, mo_st, mo_et, di_st, di_et, mi_st, mi_et, do_st, do_et, fr_st, fr_et, sa_st, sa_et, so_st, so_et);
    EXPECT_EQ(fid, 4);
}

TEST_F(TestFahrzeugReg, TestFahrzeugRegistrierenKeinZeitraumErstellt) {
    s="Düsseldorf";
    ftyp="Limousine";
    mo_et = QTime::fromString("02:00", "hh:mm");
    do_et = QTime::fromString("10:00", "hh:mm");
    fr_et =  QTime::fromString("10:00", "hh:mm");
    sa_et = QTime::fromString("10:00", "hh:mm");
    int fid=v->fahrzeug_registrieren(1, kennzeichen, marke, fart, farbe, baujahr, plaetze, ftyp, beschaedigung, s, plz, str, hnr, baujahr, mo_st, mo_et, di_st, di_et, mi_st, mi_et, do_st, do_et, fr_st, fr_et, sa_st, sa_et, so_st, so_et);
    EXPECT_EQ(fid, 7);
}


TEST_F(TestFahrzeugReg, TestZeitraumPruefenIDRichtig) {
    EXPECT_GT(v->zeitraum_ueberpruefen(1, 4, startzeit, endzeit), 0);
}

TEST_F(TestFahrzeugReg, TestZeitraumPruefenIDFalsch) {
    endzeit = QTime::fromString("10:00", "hh:mm");
    EXPECT_EQ(v->zeitraum_ueberpruefen(1, 4, startzeit, endzeit), 0);
}

TEST_F(TestFahrzeugReg, TestStellplatzRegistrierenIDRichtig) {
    str = "Erdingerstraße";
    EXPECT_GT(v->stellplatz_registrieren(s, plz, str, hnr, parknr), 0);
}

TEST_F(TestFahrzeugReg, TestStellplatzRegistrierenIDVorhanden) {
    s= "Regensburg";
    str="Seybothstraße";
    plz="93053";
    hnr="2";
    parknr=5;
    EXPECT_EQ(v->stellplatz_registrieren(s, plz, str, hnr, parknr), 1);
}

TEST_F(TestFahrzeugReg, TestStellplatzRegistrierenIDUndParkplatzVorhanden) {
    Fahrzeugverwaltung * v= new Fahrzeugverwaltung();
    s= "Regensburg";
    str="Seybothstraße";
    plz="93053";
    hnr="2";
    parknr=1;
    EXPECT_EQ(v->stellplatz_registrieren(s, plz, str, hnr, parknr), -2);
}
