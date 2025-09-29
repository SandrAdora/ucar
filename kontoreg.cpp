#include "kontoreg.h"
#include "ui_kontoreg.h"
#include "vermieterverwaltung.h"
#include "mieterverwaltung.h"
#include "loginansicht.h"
KontoReg::KontoReg(QWidget *parent, Mieterverwaltung* m, Vermieterverwaltung* v) :
    QDialog(parent),
    v_verwaltung(v),
    m_verwaltung(m),
    ui(new Ui::KontoReg)
{
    ui->setupUi(this);
    setWindowTitle("Registrieren");
}

KontoReg::~KontoReg()
{
    delete ui;
}


static Geschlecht g_ = Geschlecht::UNBEKANNT;
static Berechtigung b_ = Berechtigung::SONSTIGES;

void KontoReg::pushButton_absenden_clicked() {


    Vermieter* v;
    Mieter* m;
    //!Berechtigung
     konto_art = ui->comboBox_berechtigung->currentText();

     vorname = ui->lineEdit_vorname->text();
     nachname = ui->lineEdit_name->text(); 
     geburtsdatum = ui->dateEdit_geburtsdatum->date();
     geschlecht = ui->comboBox->currentText();
     strasse = ui->lineEdit_strasse->text();
     hausnummer = ui->lineEdit_hausnummer->text();
     wohnort = ui->lineEdit_ort->text();
     plz = ui->lineEdit_plz->text();
     telnr = ui->lineEdit_mobil->text();
     fklasse = ui->lineEdit_fklasse->text();
     email = ui->lineEdit_email->text();
     pw = ui->lineEdit_passwort->text();



    ///prüft das Geschlecht

    if(geschlecht  == "männlich")
    {
     g_ = Geschlecht::MAENNLICH;
    }
    else if (geschlecht == "weiblich")
    {
     g_ = Geschlecht::WEIBLICH;
    }
    else if (geschlecht == "divers")
    {
     g_ = Geschlecht::DIVERS;
    }




///Prüft die berechtigung
    if(konto_art == "Vermieter")
    {

         b_ = Berechtigung::VERMIETER;

        bool registrierung = v_verwaltung->get_vermieterverwaltung()->vermieter_registrierung(vorname, nachname, geburtsdatum, g_,pw, email, telnr, wohnort,plz, strasse, hausnummer,fklasse, b_);
        if(registrierung)
        {
            QMessageBox::information(this, "Registrierung", "Registrierung erfolgreich");
            close();
        }
        else{

            QMessageBox::warning(this, "Registrierung", "Registrierung nicht erfolgreich");

            }
    }
    else if(konto_art == "Mieter")
    {
        b_ = Berechtigung::MIETER;

        bool registrierung = m_verwaltung->get_mieterverwaltung()->mieter_registrierung(nachname, vorname, geburtsdatum, g_,pw, email, telnr, wohnort,plz, strasse, hausnummer,  konto_art ,b_);
        if(registrierung)
        {
            QMessageBox msg;
                msg.information(this, "Registrierung", "Registrierung war erfolgreich");
                close();

        }
        else{
            QMessageBox::warning(this, "Registrierung", "Registrierung war nicht erfolgreich");
        }
    }
}
