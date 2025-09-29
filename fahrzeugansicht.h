#ifndef FAHRZEUGANSICHT_H
#define FAHRZEUGANSICHT_H

#include <QWidget>
#include <QListWidget>
#include <vector>
#include "fahrzeug.h"
#include "fahrzeugverwaltung.h"
#include "person.h"

namespace Ui {
class FahrzeugAnsicht;
}

class FahrzeugAnsicht : public QWidget
{
    Q_OBJECT

public:
    explicit FahrzeugAnsicht(Person *,QWidget *parent = nullptr);
    ~FahrzeugAnsicht();
    void aktualisieren();

private:
    Ui::FahrzeugAnsicht *ui;
    Person *person;
    std::vector<Fahrzeug *> fahrzeuge;
    Fahrzeugverwaltung *verwaltung;

private slots:
    void pushButton_neu_clicked();
    void listWidget_fahrzeuge_itemClicked(QListWidgetItem *);
};

#endif // FAHRZEUGANSICHT_H
