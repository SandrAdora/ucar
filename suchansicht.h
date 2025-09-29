#ifndef SUCHANSICHT_H
#define SUCHANSICHT_H

#include <QWidget>
#include <QListWidget>
#include <vector>
#include "fahrzeug.h"
#include "fahrzeugverwaltung.h"
#include "person.h"

namespace Ui {
class SuchAnsicht;
}

class SuchAnsicht : public QWidget
{
    Q_OBJECT

public:
    explicit SuchAnsicht(Person *, QWidget *parent = nullptr);
    ~SuchAnsicht();

private:
    Ui::SuchAnsicht *ui;
    Person *person;
    std::vector<Fahrzeug *> ergebnisse;
    Fahrzeugverwaltung *verwaltung;

private slots:
    void pushButton_suchen_clicked();
    void listWidget_ergebnisse_itemClicked(QListWidgetItem *);
};

#endif // SUCHANSICHT_H
