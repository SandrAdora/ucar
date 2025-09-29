#include "fahrzeugdetail.h"
#include "ui_fahrzeugdetail.h"

FahrzeugDetail::FahrzeugDetail(Fahrzeug *f, Fahrzeugverwaltung *v, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FahrzeugDetail),
    akt_fahrzeug(f),
    verwaltung(v)
{
    ui->setupUi(this);
    setWindowTitle(akt_fahrzeug->get_fahrzeug_marke() + " " + akt_fahrzeug->get_fahrzeugmodell()->get_fahrzeug_art());

    QString text = akt_fahrzeug->print_vermieter_daten();
    ui->label_info->setText(text);
}

FahrzeugDetail::~FahrzeugDetail()
{
    delete ui;
}

void FahrzeugDetail::pushButton_bearbeiten_clicked() {

}

void FahrzeugDetail::pushButton_loeschen_clicked() {

}

