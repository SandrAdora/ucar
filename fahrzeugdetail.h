#ifndef FAHRZEUGDETAIL_H
#define FAHRZEUGDETAIL_H

#include <QDialog>
#include "fahrzeugverwaltung.h"

namespace Ui {
class FahrzeugDetail;
}

class FahrzeugDetail : public QDialog
{
    Q_OBJECT

public:
    explicit FahrzeugDetail(Fahrzeug *, Fahrzeugverwaltung *, QWidget *parent = nullptr);
    ~FahrzeugDetail();

private:
    Ui::FahrzeugDetail *ui;
    Fahrzeug *akt_fahrzeug;
    Fahrzeugverwaltung *verwaltung;

private slots:
    void pushButton_bearbeiten_clicked();
    void pushButton_loeschen_clicked();
};

#endif // FAHRZEUGDETAIL_H
