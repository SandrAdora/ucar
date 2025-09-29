#include "profilansicht.h"
#include "ui_profilansicht.h"

ProfilAnsicht::ProfilAnsicht(Person * p, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ProfilAnsicht),
    person(p)
{
    ui->setupUi(this);
    setWindowTitle("Profil");
    Berechtigung b_ = Berechtigung::SONSTIGES;
    if(person->get_berechtigung() == "vermieter")
    {
        b_ = Berechtigung::VERMIETER;
    }
    else if(person->get_berechtigung() == "mieter")
    {
        b_ = Berechtigung::MIETER;
    }
    ui->label_info->setText(personendaten_anzeigen(b_));

}


ProfilAnsicht::~ProfilAnsicht()
{
    delete ui;

}
QString ProfilAnsicht::personendaten_anzeigen(Berechtigung& b_) const
{

    QString person_info ;
    if (b_ == Berechtigung::VERMIETER)
    {
        //vermieter
        person_info = person->print_person();
    }
    else if(b_ == Berechtigung::MIETER)
    {
        person_info = person->print_person();
    }


    return person_info;


}
void ProfilAnsicht::pushButton_bearbeiten_clicked() {

}

void ProfilAnsicht::pushButton_loeschen_clicked() {

}
