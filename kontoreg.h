#ifndef KONTOREG_H
#define KONTOREG_H

#include <QDialog>
#include <QMessageBox>
#include "mainwindow.h"
#include "person.h"
#include "mieterverwaltung.h"
#include "vermieterverwaltung.h"

namespace Ui {
class KontoReg;
}

class KontoReg : public QDialog
{
    Q_OBJECT

public:
    explicit KontoReg(QWidget *parent = nullptr, Mieterverwaltung *m = nullptr, Vermieterverwaltung* v = nullptr);


    ~KontoReg();

    private:
    Ui::KontoReg *ui;
    Mieterverwaltung *m_verwaltung;
    Vermieterverwaltung *v_verwaltung;

    QString konto_art;
    QString nachname;
    QString vorname;
    QDate geburtsdatum ;
    QString geschlecht ;
    QString email ;
    QString telnr ;
    QString wohnort ;
    QString plz  ;
    QString strasse ;
    QString hausnummer;
    QString fklasse;
    QString pw ;




private slots:
    void pushButton_absenden_clicked();
};

#endif // KONTOREG_H
