#include "fahrzeugansicht.h"
#include "ui_fahrzeugansicht.h"
#include "fahrzeugreg.h"
#include "fahrzeugdetail.h"

FahrzeugAnsicht::FahrzeugAnsicht(Person *p, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FahrzeugAnsicht),
    person(p)
{
    ui->setupUi(this);
    verwaltung = new Fahrzeugverwaltung();
    aktualisieren();
}

FahrzeugAnsicht::~FahrzeugAnsicht()
{
    delete ui;
    for(auto item : fahrzeuge) {
        delete item;
    }
    fahrzeuge.clear();
    delete verwaltung;
}

void FahrzeugAnsicht::pushButton_neu_clicked() {
    FahrzeugReg *reg_ansicht = new FahrzeugReg(person, verwaltung);
    reg_ansicht->exec();
    aktualisieren();
}

void FahrzeugAnsicht::listWidget_fahrzeuge_itemClicked(QListWidgetItem *item) {
    int index = ui->listWidget_fahrzeuge->row(item);
    Fahrzeug *f = fahrzeuge.at(index);
    FahrzeugDetail *dialog = new FahrzeugDetail(f, verwaltung);
    dialog->open();
}

//Methode zum Aktualisieren der angezeigten Fahrzeuge
void FahrzeugAnsicht::aktualisieren() {
    //Vector und ListWidget leeren
    if(!fahrzeuge.empty()) {
        for(auto item : fahrzeuge) {
            delete item;
        }
        fahrzeuge.clear();
    }
    ui->listWidget_fahrzeuge->clear();

    //Vector von der DB anfragen und ListWidget füllen
    fahrzeuge = verwaltung->fahrzeuge_zu_person(person->get_person_id());
    for(auto item : fahrzeuge) {
        QListWidgetItem *lwi = new QListWidgetItem();
        QString marke = item->get_fahrzeug_marke();
        QString art = item->get_fahrzeugmodell()->get_fahrzeug_art();
        lwi->setText(marke + " " + art);
        ui->listWidget_fahrzeuge->addItem(lwi);
    }
}

