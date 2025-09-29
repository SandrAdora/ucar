#include <QRegularExpression>
#include <QValidator>
#include <QRegularExpressionValidator>
#include "loginansicht.h"
#include <QMessageBox>
#include "kontoreg.h"
#include "datenbank_verbindung.h"
#include "ui_loginansicht.h"
#include "ui_kontoreg.h"





LoginAnsicht::LoginAnsicht(QWidget *parent, Vermieterverwaltung* v, Mieterverwaltung* m ) :
    QDialog(parent),
    v_verwaltung(v),
    m_verwaltung(m),
    ui(new Ui::LoginAnsicht)
{
    ui->setupUi(this);

    setWindowTitle("Anmelden");
}

LoginAnsicht::~LoginAnsicht()
{
   delete ui;
   delete m_verwaltung;
   delete v_verwaltung;

}

void LoginAnsicht::pushButton_anmelden_clicked()
{
    QString nutzername = ui->lineEdit_nutzername->text();
    QString passwort = ui->lineEdit_passwort->text();
    QString konto_art = ui->comboBox_art->currentText();



 std::vector<Vermieter*> vec;
    if (konto_art == "Vermieter")
    {
        bool vermieter_anmeldung = v_verwaltung->get_vermieterverwaltung()->vermieter_anmelden(nutzername, passwort);
        if (vermieter_anmeldung)
        {
             std::vector<Vermieter*> vec;
             Vermieter* v_ = nullptr;
             Berechtigung konto_nr = Berechtigung::VERMIETER;

            vec = v_verwaltung->get_vermieterverwaltung()->get_vermieter(nutzername, passwort);

            for(auto item : vec)
            {
                v_ = new Vermieter(item->get_person_id());
                v_->set_berechtigung(konto_nr);
                v_->set_nname(item->get_nname());
                v_->set_vname(item->get_vname());
                v_->set_geb(item->get_geb());
                v_->set_geschlecht(item->get_geschlecht_enum());
                v_->set_strasse(item->get_strasse());
                v_->set_hausnummer(item->get_hausnummer());
                v_->set_plz(item->get_plz());
                v_->set_wohnort(item->get_wohnort());
                v_->set_telnr(item->get_telnr());
                v_->set_email(item->get_email());


            }
            MainWindow* mw = new MainWindow(v_);
            mw->show();
            close();
        }
        else
        {
            QMessageBox::warning(this, "Anmeldung", "Passwort oder E-Mail ist falsch");
        }
    }
    else if (konto_art == "Mieter")
    {
        bool mieter_anmeldung = m_verwaltung->get_mieterverwaltung()->mieter_anmelden(nutzername, passwort);
        if (mieter_anmeldung)
        {
             std::vector<Mieter*> vec;
             Mieter* m_ = nullptr;
             Berechtigung konto_nr = Berechtigung::MIETER;
             vec = m_verwaltung->get_mieterverwaltung()->get_mieter(nutzername, passwort);
             for(auto item : vec)
             {
                 m_ = new Mieter(item->get_person_id());
                 m_->set_berechtigung(konto_nr);
                 m_->set_nname(item->get_nname());
                 m_->set_vname(item->get_vname());
                 m_->set_geb(item->get_geb());
                 m_->set_geschlecht(item->get_geschlecht_enum());
                 m_->set_strasse(item->get_strasse());
                 m_->set_hausnummer(item->get_hausnummer());
                 m_->set_plz(item->get_plz());
                 m_->set_wohnort(item->get_wohnort());
                 m_->set_telnr(item->get_telnr());
                 m_->set_email(item->get_email());
                 m_->set_fuehrerschein_klasse(item->get_fuehrerschein_klasse());

             }
            MainWindow* mw = new MainWindow(m_);
            mw->show();
            close();
        }
        else
        {
            QMessageBox::warning(this, "Anmeldung", "Passwort oder E-Mail ist falsch");
        }
    }
}



void LoginAnsicht::pushButton_registrieren_clicked(){
    KontoReg *reg_ansicht = new KontoReg();
    reg_ansicht->open();
}
