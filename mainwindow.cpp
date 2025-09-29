#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "loginansicht.h"
#include "suchansicht.h"
#include "buchungsansicht.h"
#include "fahrzeugansicht.h"
#include "profilansicht.h"
#include "person.h"
#include "mieter.h"
#include "vermieter.h"

MainWindow::MainWindow(Person *p, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , person(p)
{
    ui->setupUi(this);
    setWindowTitle("U-Car");

    QString str_konto = p->get_berechtigung();
    if(QString::compare(str_konto, "Mieter", Qt::CaseInsensitive) == 0) {
        berechtigung = Berechtigung::MIETER;
    } else if(QString::compare(str_konto, "Vermieter", Qt::CaseInsensitive) == 0) {
        berechtigung = Berechtigung::VERMIETER;
    }

    s_ansicht = new SuchAnsicht(person);
    b_ansicht = new BuchungsAnsicht(person);
    f_ansicht = new FahrzeugAnsicht(person);
    p_ansicht = new ProfilAnsicht(person);

    tabWidget = new QTabWidget(this);
    tabWidget->setFixedSize(width(), height());

    if(berechtigung == Berechtigung::MIETER) {
        tabWidget->addTab(s_ansicht, "Suche");
        tabWidget->addTab(b_ansicht, "Buchungen");
        tabWidget->addTab(p_ansicht, "Profil");
    } else if (berechtigung == Berechtigung::VERMIETER) {
        tabWidget->addTab(f_ansicht, "Fahrzeuge");
        tabWidget->addTab(b_ansicht, "Buchungen");
        tabWidget->addTab(p_ansicht, "Profil");
    }

    connect(tabWidget, SIGNAL(tabBarClicked(int)), this, SLOT(tabWidget_clicked(int)));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete tabWidget;
    delete s_ansicht;
    delete b_ansicht;
    delete f_ansicht;
    delete p_ansicht;
    //delete person;
}

void MainWindow::tabWidget_clicked(int index) {
    if(index == 0 && berechtigung == Berechtigung::VERMIETER) {
        f_ansicht->aktualisieren();
    } else if(index == 1) {
        b_ansicht->aktualisieren();
    }
}

