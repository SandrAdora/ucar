#include "suchansicht.h"
#include "ui_suchansicht.h"
#include "buchungreg.h"

SuchAnsicht::SuchAnsicht(Person *p, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SuchAnsicht),
    person(p)
{
    ui->setupUi(this);
    ui->spinBox_sitze->setMinimum(2);
    ui->dateEdit_datum->setMinimumDate(QDate::currentDate());
    QTime b = QTime::currentTime();
    int b_int = b.hour();
    b = QTime(b_int + 1, 0);
    QTime e = QTime(b_int + 2, 0);
    ui->timeEdit_beginn->setTime(b);
    ui->timeEdit_ende->setTime(e);
    verwaltung = new Fahrzeugverwaltung();
}

SuchAnsicht::~SuchAnsicht()
{
    delete ui;
    for(auto item : ergebnisse) {
        delete item;
    }
    ergebnisse.clear();
    delete verwaltung;
}



void SuchAnsicht::pushButton_suchen_clicked() {
    int sitze = ui->spinBox_sitze->value();
    QString stadt = ui->lineEdit_stadt->text();
    QString typ_str = ui->comboBox_typ->currentText();
    int typ;
    if(typ_str == "") {
        typ = -1;
    } else {
        typ = typ_toInt(typ_str);
    }
    QDate datum = ui->dateEdit_datum->date();
    QTime beginn = ui->timeEdit_beginn->time();
    QTime ende = ui->timeEdit_ende->time();

    //Vector und ListWidget leeren, falls noch alte Ergebnisse vorhanden
    if(!ergebnisse.empty()) {
        for(auto item : ergebnisse) {
            delete item;
        }
        ergebnisse.clear();
    }
    ui->listWidget_ergebnisse->clear();

    //alle passenden Fahrzeuge aus der DB abfragen
    ergebnisse = verwaltung->fahrzeug_suchen(sitze, stadt, typ, datum, beginn, ende);

    for(auto item : ergebnisse) {
        QListWidgetItem *lwi = new QListWidgetItem();
        QString marke = item->get_fahrzeug_marke();
        QString art = item->get_fahrzeugmodell()->get_fahrzeug_art();
        lwi->setText(marke + " " + art);
        ui->listWidget_ergebnisse->addItem(lwi);
    }

}

void SuchAnsicht::listWidget_ergebnisse_itemClicked(QListWidgetItem *item) {
    //Könnten so nachträglich noch verändert werden (= nicht dieselben wie bei der Suche)
    QDate datum = ui->dateEdit_datum->date();
    QTime beginn = ui->timeEdit_beginn->time();
    QTime ende = ui->timeEdit_ende->time();

    int index = ui->listWidget_ergebnisse->row(item);
    Fahrzeug *f = ergebnisse.at(index);
    BuchungReg *dialog = new BuchungReg(person, f, datum, beginn, ende);
    dialog->exec();
    pushButton_suchen_clicked();
}



