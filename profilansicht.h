#ifndef PROFILANSICHT_H
#define PROFILANSICHT_H

#include <QWidget>
#include "person.h"
#include "mieterverwaltung.h"
#include "vermieterverwaltung.h"

namespace Ui {
class ProfilAnsicht;
}

class ProfilAnsicht : public QWidget
{
    Q_OBJECT

public:
public:
    explicit ProfilAnsicht(Person*,  QWidget *parent = nullptr);
    ~ProfilAnsicht();
    QString personendaten_anzeigen(Berechtigung& )const;

private:
    Ui::ProfilAnsicht *ui;
    Person *person;
    Vermieterverwaltung* v_verwaltung;
    Mieterverwaltung* m_verwaltung;


private slots:
    void pushButton_bearbeiten_clicked();
    void pushButton_loeschen_clicked();
};

#endif // PROFILANSICHT_H
