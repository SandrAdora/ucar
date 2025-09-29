#include "fahrzeugreg.h"
#include "ui_fahrzeugreg.h"

FahrzeugReg::FahrzeugReg(Person *p, Fahrzeugverwaltung *v, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FahrzeugReg),
    person(p),
    verwaltung(v)
{
    ui->setupUi(this);
    setWindowTitle("Neues Fahrzeug");
    ui->spinBox_sitze->setMinimum(2);
}

FahrzeugReg::~FahrzeugReg()
{
    delete ui;
}

void FahrzeugReg::pushButton_absenden_clicked() {
    //Werte aus der UI Anisch holen
    QString marke = ui->lineEdit_marke->text();
    QString art = ui->lineEdit_art->text();
    QString kennzeichen = ui->lineEdit_kennzeichen->text();
    QString farbe = ui->lineEdit_farbe->text();
    int baujahr=ui->lineEdit_baujahr->text().toInt();
    int sitzplaetze = ui->spinBox_sitze->value();
    QString fahrzeugtyp = ui->comboBox_fahrzeugtyp->currentText();
    int beschaedigung = ui->lineEdit_beschaedigung->text().toInt();
    QString stadt = ui->lineEdit_ort->text();
    QString plz = ui->lineEdit_plz->text();
    QString strasse = ui->lineEdit_strasse->text();
    QString hausnr = ui->lineEdit_hausnr->text();
    int parkplatznr = ui->lineEdit_parkplatznr->text().toInt();
    QTime mo_von = ui->timeEdit_mo_von->time();
    QTime mo_bis = ui->timeEdit_mo_bis->time();
    QTime di_von = ui->timeEdit_di_von->time();
    QTime di_bis = ui->timeEdit_di_bis->time();
    QTime mi_von = ui->timeEdit_mi_von->time();
    QTime mi_bis = ui->timeEdit_mi_bis->time();
    QTime do_von = ui->timeEdit_do_von->time();
    QTime do_bis = ui->timeEdit_do_bis->time();
    QTime fr_von = ui->timeEdit_fr_von->time();
    QTime fr_bis = ui->timeEdit_fr_bis->time();
    QTime sa_von = ui->timeEdit_sa_von->time();
    QTime sa_bis = ui->timeEdit_sa_bis->time();
    QTime so_von = ui->timeEdit_so_von->time();
    QTime so_bis = ui->timeEdit_so_bis->time();
    int pid=person->get_person_id();

    //Aufruf der Verwaltungsklasse
    int error=verwaltung->fahrzeug_registrieren(pid, kennzeichen, marke, art, farbe, baujahr, sitzplaetze, fahrzeugtyp, beschaedigung, stadt, plz, strasse, hausnr, parkplatznr, mo_von, mo_bis, di_von, di_bis, mi_von, mi_bis, do_von, do_bis,
                                      fr_von, fr_bis, sa_von, sa_bis, so_von, so_bis);

    if(error!=0)
    //Wenn Zeit am Ende: als Erroranzeige ausgeben
    qDebug()<<"Error in Fahrzeug_registrieren: Errornummer "<<error;


    close();
}
