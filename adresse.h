#ifndef ADRESSE_H
#define ADRESSE_H

#include <QObject>
#include <QString>

class Adresse : public QObject {
public:
    //Konstructs

    Adresse() = default;
    Adresse(QString, QString , QString , QString );
    //Methods
    QString get_strasse() const;
    void set_strasse(QString);
    QString get_hausnummer() const;
    void set_hausnummer(QString);
    QString get_plz() const;
    void set_plz(QString);
    QString get_wohnort() const;
    void set_wohnort(QString);

    QString print_adresse();

private:
    QString strasse ="";
    QString hausnummer ="";
    QString plz ="";
    QString wohnort ="";
};
#endif // ADRESSE_H
