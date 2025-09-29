#ifndef LOGINANSICHT_H
#define LOGINANSICHT_H

#include <QDialog>
#include <QString>
#include "mainwindow.h"
#include "person.h"
#include "profilansicht.h"
#include "mieterverwaltung.h"
#include "vermieterverwaltung.h"



namespace Ui {
class LoginAnsicht;
}

class LoginAnsicht : public QDialog
{
    Q_OBJECT

public:
    explicit LoginAnsicht(QWidget *parent = nullptr, Vermieterverwaltung* v = nullptr, Mieterverwaltung* m = nullptr);
    ~LoginAnsicht();

private:
    Ui::LoginAnsicht *ui;
    QString nutzername;
    QString passwort;
    Mieterverwaltung *m_verwaltung;
    Vermieterverwaltung *v_verwaltung;



private slots:
    void pushButton_anmelden_clicked();
    void pushButton_registrieren_clicked();
};

#endif // LOGINANSICHT_H
