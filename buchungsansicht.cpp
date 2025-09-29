#include "buchungsansicht.h"
#include "ui_buchungsansicht.h"
#include "buchungdialogmieter.h"
#include "buchungdialogvermieter.h"
#include <QDebug>

BuchungsAnsicht::BuchungsAnsicht(Person *p, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BuchungsAnsicht),
    person(p)
{
    ui->setupUi(this);
    verwaltung = new Buchungsverwaltung();
    aktualisieren();
}

BuchungsAnsicht::~BuchungsAnsicht()
{
    delete ui;
    for(auto item : buchungen) {
        delete item;
    }
    buchungen.clear();
    delete verwaltung;
}

void BuchungsAnsicht::listWidget_buchungen_itemClicked(QListWidgetItem *item) {
    int index = ui->listWidget_buchungen->row(item);
    Buchung *b = buchungen.at(index);
    if(person->get_berechtigung() == "mieter") {
        BuchungDialogMieter *dialog = new BuchungDialogMieter(person, b, verwaltung);
        dialog->exec();
        aktualisieren();
    } else if(person->get_berechtigung() == "vermieter") {
        BuchungDialogVermieter *dialog = new BuchungDialogVermieter(person, b, verwaltung);
        dialog->exec();
        aktualisieren();
    }
}

//Methode zum Aktualisieren der angezeigten Buchungen
void BuchungsAnsicht::aktualisieren() {
    //Vector und ListWidget leeren
    if(!buchungen.empty()) {
        for(auto item : buchungen) {
            delete item;
        }
        buchungen.clear();
    }
    ui->listWidget_buchungen->clear();

    //Vector von der DB anfragen und ListWidget füllen
    buchungen = verwaltung->buchungen_zu_person(person->get_person_id());
    for(auto item : buchungen) {
        QListWidgetItem *lwi = new QListWidgetItem();
        QString abholung = (item->get_abholdatum()).toString();
        QString rueckgabe = (item->get_rueckgabedatum()).toString();
        lwi->setText(abholung + " bis " + rueckgabe);
        ui->listWidget_buchungen->addItem(lwi);
    }
}

