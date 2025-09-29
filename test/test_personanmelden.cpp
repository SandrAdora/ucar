/*
#include "../mieterverwaltung.h"
#include "../vermieterverwaltung.h"
#include "gtest/gtest.h"

struct TestVermieterAnmelden : public::testing::Test
{
    Vermieterverwaltung* v_an = new Vermieterverwaltung();

    QString email_v;
    QString pw_v;

    TestVermieterReg* v_ptr;

    TestVermieterAnmelden()
    {
        email_v = v_ptr->email;
        pw_v = v_ptr->pwv;
    }

};
struct TestMieterAnmelden : public::testing::Test
{
    Mieterverwaltung* m_an = new Mieterverwaltung();

    QString email_m;
    QString pw_m;

    TestMieterReg* m_ptr;

    TestMieterAnmelden()
    {
        email_m = m_ptr->email;
        pw_m = m_ptr->pwm;

    }
};

TEST_F(TestVermieterAnmelden, TestVermieterAnmeldenWahr)
{
    EXPECT_TRUE(v_an->get_vermieterverwaltung()->vermieter_anmelden(email_v, pw_v));
}

TEST_F(TestVermieterAnmelden, TestVermieterAnmeldenEmailFalsch)
{
    email_v = v_ptr->email+"s";
    EXPECT_FALSE(v_an->get_vermieterverwaltung()->vermieter_anmelden(email_v, pw_v));
}

TEST_F(TestVermieterAnmelden, TestVermieterAnmeldenPWFalsch)
{
    pw_v = v_ptr->pwv + "3";
    EXPECT_FALSE(v_an->get_vermieterverwaltung()->vermieter_anmelden(email_v, pw_v));
}

TEST_F(TestVermieterAnmelden, TestVermieterAbrufenWahr)
{
    std::vector<Vermieter*> vec_v = v_an->get_vermieter(email_v, pw_v);
    bool vec_not_empty = true;

    if(vec_v.empty())
    {
        vec_not_empty = false;

    }

    EXPECT_TRUE(vec_not_empty);
}

TEST_F(TestVermieterAnmelden, TestVermieterAbrufenFalsch)
{
    email_v = "@test_example.de";
    std::vector<Vermieter*> vec_v = v_an->get_vermieter(email_v, pw_v);
    bool vec_not_empty = false;

    if(!vec_v.empty())
    {
        vec_not_empty= true;
    }

    EXPECT_FALSE(vec_not_empty);
}


TEST_F(TestMieterAnmelden, TestmieterAnmeldenWahr)
{
    EXPECT_TRUE(m_an->get_mieterverwaltung()->mieter_anmelden(email_m, pw_m));
}

TEST_F(TestMieterAnmelden, TestmieterAnmeldenEmailFalsch)
{
    email_m = m_ptr->email+"s";
    EXPECT_FALSE(m_an->get_mieterverwaltung()->mieter_anmelden(email_m, pw_m));
}

TEST_F(TestMieterAnmelden, TestmieterAnmeldenPWFalsch)
{
    pw_m = m_ptr->pwm + "3";
    EXPECT_FALSE(m_an->get_mieterverwaltung()->mieter_anmelden(email_m, pw_m));
}

TEST_F(TestMieterAnmelden, TestMieterAbrufenWahr)
{
    std::vector<Mieter*> vec_m = m_an->get_mieter(email_m, pw_m);
    bool vec_not_empty = true;

    if(vec_m.empty())
    {
        vec_not_empty = false;

    }

    EXPECT_TRUE(vec_not_empty);
}

TEST_F(TestMieterAnmelden, TestmieterAbrufenFalsch)
{
    email_m = "@test_example.de";
    std::vector<Mieter*> vec_m = m_an->get_mieter(email_m, pw_m);
    bool vec_not_empty = false;

    if(!vec_m.empty())
    {
        vec_not_empty= true;
    }

    EXPECT_FALSE(vec_not_empty);
}
*/
