#ifndef BUCHUNGSANSICHT_H
#define BUCHUNGSANSICHT_H

#include <QWidget>
#include <QListWidget>
#include <vector>
#include "buchung.h"
#include "buchungsverwaltung.h"
#include "person.h"

namespace Ui {
class BuchungsAnsicht;
}

class BuchungsAnsicht : public QWidget
{
    Q_OBJECT

public:
    explicit BuchungsAnsicht(Person *, QWidget *parent = nullptr);
    ~BuchungsAnsicht();
    void aktualisieren();

private:
    Ui::BuchungsAnsicht *ui;
    Person *person;
    std::vector<Buchung *> buchungen;
    Buchungsverwaltung *verwaltung;

private slots:
    void listWidget_buchungen_itemClicked(QListWidgetItem *);
};

#endif // BUCHUNGSANSICHT_H
