#include "../vermieterverwaltung.h"
#include "../mieterverwaltung.h"
#include "gtest/gtest.h"


#include <QDate>

struct TestVermieterReg: public::testing::Test{

    Vermieterverwaltung* v_obj =  new Vermieterverwaltung();

    int tag = 15 ; int monat = 12; int jahr = 1990;

    QString vname {"Frank Test"};
    QString nname {"Sinatra"};
    QDate geb;
    QString strasse {"Münchnerstr."};
    QString hausnr{"2A"};
    QString plz{"93067"};
    QString stadt{"Regensburg"};
    QString email{"test.sinatra@exp.com"};
    QString tel{"+4917433267474"};
    QString pwv{"A2testll234"};
    QString f_klasse{"B"};

    Berechtigung b_ver = Berechtigung::VERMIETER;
    Geschlecht g_ver = Geschlecht::DIVERS;

    TestVermieterReg()
    {

        geb.setDate(jahr, monat, tag);
    }



};


struct TestMieterReg: public::testing::Test
{
    ///TODO: Test
    Mieterverwaltung* m_obj = new Mieterverwaltung();

    int jahr = 1996; int monat = 06; int tag = 19;

    QString vname{"Mario"};
    QString nname{"Kart"};
    QDate geb;
    QString str{"Simpstr."};
    QString hnr{"2"};
    QString plz{"94032"};
    QString stadt{"Passau"};
    QString email{"test.mario@example.de"};
    QString tel{"+4927533169426"};
    QString pwm{"A2retestxl"};
    QString f_klasse{"B"};
    Berechtigung b_mie = Berechtigung::MIETER;
    Geschlecht g_mie = Geschlecht::DIVERS;

    TestMieterReg()
    {
        geb.setDate(jahr, monat, tag);
    }

};

TEST_F(TestVermieterReg, TestVermieterRegWahr)
{
   EXPECT_TRUE(v_obj->get_vermieterverwaltung()->vermieter_registrierung(nname, vname, geb, g_ver, pwv, email, tel, stadt, plz, strasse, hausnr, f_klasse, b_ver));
}


TEST_F(TestVermieterReg, TestVermieterFalsch)
{
     pwv = "avheu";
     nname = "Etheford";
     vname = "Bridgeton";
     g_ver = Geschlecht::WEIBLICH;
     bool v_id = v_obj->get_vermieterverwaltung()->vermieter_registrierung(nname, vname, geb, g_ver, pwv, email, tel, stadt, plz, strasse, hausnr, f_klasse, b_ver);

    EXPECT_FALSE(v_id);

}

TEST_F(TestVermieterReg, TestVermieterRegVornameNachnameGleichFalsch)
{
    vname = "Mario";
    nname = vname;
    g_ver = Geschlecht::MAENNLICH;

    bool v_id = v_obj->get_vermieterverwaltung()->vermieter_registrierung(nname, vname, geb, g_ver, pwv, email, tel, stadt, plz, strasse, hausnr, f_klasse, b_ver);

    EXPECT_EQ(v_id, 0);

}

TEST_F(TestVermieterReg, TestVermieterRegEmailExistiertBereitsFalsch)
{
    vname = "Naomi";
    nname = "Cavali";
    email = "test.sinatra@exp.com";
    g_ver = Geschlecht::WEIBLICH;
    f_klasse = "C";
    strasse = "clemont";
    hausnr = "3B";
    bool v_id = v_obj->get_vermieterverwaltung()->vermieter_registrierung(nname, vname, geb, g_ver, pwv, email, tel, stadt, plz, strasse, hausnr, f_klasse, b_ver);

    EXPECT_FALSE(v_id);

}


TEST_F(TestMieterReg, TestMieterRegWahr)
{
    EXPECT_TRUE(m_obj->get_mieterverwaltung()->mieter_registrierung(nname, vname, geb, g_mie, pwm, email, tel, stadt, plz, str, hnr, f_klasse, b_mie));
}


TEST_F(TestMieterReg, TestMieterRegUngueltigesPWFalsch)
{
     pwm = "abcdefgh";
     nname = "Ruth";
     vname = "Schuber";
     g_mie = Geschlecht::WEIBLICH;
     bool m_id = m_obj->get_mieterverwaltung()->mieter_registrierung(nname, vname, geb, g_mie, pwm, email, tel, stadt, plz, str, hnr, f_klasse, b_mie);

    EXPECT_FALSE(m_id);

}

TEST_F(TestMieterReg, TestMieterRegVornameNachnameGleichFalsch)
{
    vname = "Mario";
    nname = vname;
    g_mie = Geschlecht::MAENNLICH;
    bool m_id = m_obj->get_mieterverwaltung()->mieter_registrierung(nname, vname, geb, g_mie, pwm, email, tel, stadt, plz, str, hnr, f_klasse, b_mie);

    EXPECT_FALSE(m_id);

}

TEST_F(TestMieterReg, TestMieterRegEmailExistiertBreitsFalsch)
{
    vname = "David";
    nname = "Füller";
    email = "test.mario@example.de";
    g_mie = Geschlecht::MAENNLICH;
    f_klasse = "E";
    str= "clemont";
    hnr = "3B";
    bool m_id = m_obj->get_mieterverwaltung()->mieter_registrierung(nname, vname, geb, g_mie, pwm, email, tel, stadt, plz, str, hnr, f_klasse, b_mie);

    EXPECT_FALSE(m_id);

}

