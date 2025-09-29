#include "buchungsverwaltung.h"
#include <QDebug>

Buchungsverwaltung::Buchungsverwaltung() {
    db = db->get_instanz();
}

Buchungsverwaltung::~Buchungsverwaltung() {
    delete db;
}

std::vector<Buchung>& Buchungsverwaltung::get_buchungsverwaltung()
{
    return buchungsverwaltung;
}

std::vector<Buchung> Buchungsverwaltung::get_buchung_gesamt(QDateTime abholdatum, QDateTime rueckgabedatum, Buchungsstatus stat, int buchung_id)
{
    std::vector<Buchung> result;
    for (const auto& buchung : buchungsverwaltung) {
        if ((buchung_id == -1 || buchung.get_buchung_id() == buchung_id) &&
            (stat == Buchungsstatus::offen || buchung.get_status() == stat) &&
            (abholdatum.isNull() || buchung.get_abholdatum() >= abholdatum) &&
            (rueckgabedatum.isNull() || buchung.get_rueckgabedatum() <= rueckgabedatum))
        {
            result.push_back(buchung);
        }
    }
    return result;
}

void Buchungsverwaltung::set_neue_buchung_einfuegen(QDateTime abholdatum, QDateTime rueckgabedatum, Buchungsstatus stat, int buchung_id)
{
    Buchung neue_buchung(QDateTime::currentDateTime(), abholdatum, rueckgabedatum, stat, buchung_id);
    buchungsverwaltung.push_back(neue_buchung);
}

void Buchungsverwaltung::buchung_bearbeiten(QDateTime abholdatum, QDateTime rueckgabedatum, Buchungsstatus stat, int buchung_id)
{
    // Suchen der Buchung anhand der ID
    auto it = std::find_if(buchungsverwaltung.begin(), buchungsverwaltung.end(), [&](const Buchung& buchung) {
        return buchung.get_buchung_id() == buchung_id;
    });

    // Wenn die Buchung gefunden wurde, ändere die Daten
    if (it != buchungsverwaltung.end()) {
        it->set_abholdatum(abholdatum);
        it->set_rueckgabedatum(rueckgabedatum);
        it->set_status(stat);
        std::cout << "Buchung erfolgreich bearbeitet." << std::endl;
    } else {
        std::cout << "Fehler: Buchung mit ID " << buchung_id << " nicht gefunden." << std::endl;
    }
}

std::vector<Buchung> Buchungsverwaltung::pruefe_buchung_daten(QDateTime abholdatum, QDateTime rueckgabedatum, Buchungsstatus stat, int buchung_id)
{
    std::vector<Buchung> result;

    for (auto& buchung : buchungsverwaltung) {
        // Prüfe, ob die Buchung den übergebenen Filterkriterien entspricht
        if (stat == Buchungsstatus::offen || buchung.get_status() == stat) {
            if (buchung_id == -1 || buchung.get_buchung_id() == buchung_id) {
                if (buchung.get_abholdatum() <= abholdatum && rueckgabedatum <= buchung.get_rueckgabedatum()) {
                    result.push_back(buchung);
                }
            }
        }
    }

    return result;
}




//Methoden zum Anfragen einer neuen Buchung
bool Buchungsverwaltung::fahrzeug_buchen(int fahrzeug_id, int mieter_id, QDateTime start, QDateTime ende) {
    bool ok = false;
    QSqlQuery q = db->get_person(mieter_id);
    if(!q.next()) {
        qDebug() << "Mieter existiert nicht!\n";
    } else {
        QSqlQuery q = db->get_person_zu_fahrzeug(fahrzeug_id);
        if(!q.next()) {
            qDebug() << "Vermieter konnte nicht ermittelt werden oder Fahrzeug existiert nicht!\n";
        } else {
            int vermieter_id = (q.value("PersonID")).toInt(&ok);
            if(ok) {
                //Hinzufügen der Buchung zur DB
                int success = db->add_buchung(start, ende, fahrzeug_id, mieter_id, vermieter_id);
                if(success == -1) {
                    ok = false;
                    qDebug() << "Buchung konnte nicht angefragt werden!\n";
                } else {
                    ok = true;
                    //Benachrichtigung des Vermieters
                    QString text = "Du hast eine neue Buchung erhalten! Bitte bestaetige sie oder lehne sie ab.\n";
                    datei_schreiben(vermieter_id, text);
                }
            }
        }
    }
    return ok;
}

//Methode zum Bestätigen/Ablehnen durch den Vermieter
bool Buchungsverwaltung::buchung_status_aendern(int buchung_id, Buchungsstatus status) {
    QSqlQuery q = db->get_buchung(buchung_id);
    bool ok = false;
    if(!q.next()) {
        qDebug() << "Buchung konnte nicht gefunden werden!\n";
    } else {
        QString status_str = status_toString(status);
        int status_int = status_toInt(status);
        ok = db->update_buchung_status(buchung_id, status_int);
        if(!ok) {
            qDebug() << "Buchung konnte nicht " << status_str << " werden!\n";
        } else {
            QSqlQuery q = db->get_mieter_zu_buchung(buchung_id);
            if(!q.next()) {
                qDebug() << "Mieter konnte nicht ermittelt werden!\n";
            } else {
                int mieter_id = (q.value("PersonID")).toInt(&ok);
                if(ok) {
                    //Benachrichtigung des Mieters
                    QString id_str;
                    id_str.setNum(buchung_id);
                    QString text = "Buchung Nr. " + id_str + " wurde " + status_str + "! Oeffne U-Car, um dir die Details anzusehen.\n";
                    datei_schreiben(mieter_id, text);
                }
            }
        }
    }
    return ok;
}

//Methode zum Stornieren durch den Mieter
bool Buchungsverwaltung::buchung_stornieren(int buchung_id) {
    QSqlQuery q = db->get_buchung(buchung_id);
    bool ok = false;
    if(!q.next()) {
        qDebug() << "Buchung konnte nicht gefunden werden!\n";
    } else {
        QSqlQuery q = db->get_vermieter_zu_buchung(buchung_id);
        if(!q.next()) {
            qDebug() << "Vermieter konnte nicht ermittelt werden!\n";
        } else {
            int vermieter_id = (q.value("PersonID")).toInt(&ok);
            if(ok) {
                ok = db->delete_buchung(buchung_id);
                if(!ok) {
                    qDebug() << "Buchung konnte nicht gelöscht werden!\n";
                } else {
                    //Benachrichtigung des Vermieters
                    QString id_str;
                    id_str.setNum(buchung_id);
                    QString text = "Buchung Nr. " + id_str + " wurde storniert!\n";
                    datei_schreiben(vermieter_id, text);
                }
            }
        }
    }
    return ok;
}


//Methode zur Benachrichtigung der Nutzer über eine Datei
void Buchungsverwaltung::datei_schreiben(int id, QString text) {
    QString filename;
    filename.setNum(id);
    filename.append(".txt");
    QFile file(filename);
    if(file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        out << text;
    }
    file.close();
}

//Methode zur Anzeige der Buchungen
std::vector<Buchung *> Buchungsverwaltung::buchungen_zu_person(int person_id) {
    std::vector<Buchung *> vec;
    QSqlQuery q = db->get_buchung_zu_person(person_id);
    if(!q.isActive()) {
        qDebug() << "Buchungen konnten nicht ermittelt werden!\n";
    } else {
        while(q.next()) {
            //Vector mit allen passenden Buchungen füllen
            int id = (q.value("BuchungID")).toInt();

            QString bdat_str = (q.value("Buchung_datum")).toString();
            QString bzeit_str = (q.value("Buchung_zeit")).toString();
            QDate bdat = QDate::fromString(bdat_str, "dd.MM.yyyy");
            QTime bzeit = QTime::fromString(bzeit_str, "hh:mm:ss");
            QDateTime buchungseingang = QDateTime(bdat, bzeit);

            QString adat_str = (q.value("Ausleihe_datum")).toString();
            QString azeit_str = (q.value("Ausleihe_zeit")).toString();
            QDate adat = QDate::fromString(adat_str, "dd.MM.yyyy");
            QTime azeit = QTime::fromString(azeit_str, "hh:mm:ss");
            QDateTime ausleihe = QDateTime(adat, azeit);

            QString rdat_str = (q.value("Rückgabe_datum")).toString();
            QString rzeit_str = (q.value("Rückgabe_zeit")).toString();
            QDate rdat = QDate::fromString(rdat_str, "dd.MM.yyyy");
            QTime rzeit = QTime::fromString(rzeit_str, "hh:mm:ss");
            QDateTime rueckgabe = QDateTime(rdat, rzeit);

            int status_int = (q.value("Status")).toInt();
            Buchungsstatus status = int_toStatus(status_int);

            int fahrzeug_id = (q.value("Fahrzeug")).toInt();
            Fahrzeug *f = fahrzeug_zu_buchung(fahrzeug_id);

            Buchung *neu = new Buchung(buchungseingang, ausleihe, rueckgabe, status, id, f);

            if(status == Buchungsstatus::abgeschlossen) {
                int verleih_id = (q.value("VerleihID")).toInt();
                Verleih *v = verleih_zu_buchung(verleih_id);
                neu->set_verleih(v);

                int rechnung_id = (q.value("RechnungID")).toInt();
                Rechnung *r = rechnung_zu_buchung(rechnung_id);
                neu->set_rechnung(r);
            }

            vec.push_back(neu);
        }
    }
    return vec;
}

Verleih * Buchungsverwaltung::verleih_zu_buchung(int verleih_id) {
    Verleih *v = nullptr;
    QSqlQuery q= db->get_verleih(verleih_id);
    if(q.next()) {
        QString adat_str = (q.value("Abhol_datum")).toString();
        QString azeit_str = (q.value("Abhol_zeit")).toString();
        QDate adat = QDate::fromString(adat_str, "dd.MM.yyyy");
        QTime azeit = QTime::fromString(azeit_str, "hh:mm:ss");
        QDateTime abholung = QDateTime(adat, azeit);

        QString rdat_str = (q.value("Rückgabe_datum")).toString();
        QString rzeit_str = (q.value("Rückgabe_zeit")).toString();
        QDate rdat = QDate::fromString(rdat_str, "dd.MM.yyyy");
        QTime rzeit = QTime::fromString(rzeit_str, "hh:mm:ss");
        QDateTime rueckgabe = QDateTime(rdat, rzeit);

        v = new Verleih(abholung, rueckgabe, verleih_id);
    } else {
        qDebug() << "Verleih zu Buchung konnte nicht ermittelt werden!\n";
    }
    return v;
}

Rechnung * Buchungsverwaltung::rechnung_zu_buchung(int rechnung_id) {
    Rechnung *r = nullptr;
    QSqlQuery q= db->get_rechnung(rechnung_id);
    if(q.next()) {
        double betrag = (q.value("Betrag")).toDouble();
        double km = (q.value("Kilometer")).toDouble();
        double tank = (q.value("Tankstand")).toDouble();

        r = new Rechnung(betrag, km, tank, rechnung_id);
    } else {
        qDebug() << "Rechnung zu Buchung konnte nicht ermittelt werden!\n";
    }
    return r;
}

Fahrzeug * Buchungsverwaltung::fahrzeug_zu_buchung(int fahrzeug_id) {
    Fahrzeug *f = nullptr;
    QSqlQuery q = db->get_fahrzeug(fahrzeug_id);
    if(q.next()) {
        QString marke = (q.value("Marke")).toString();
        int typ_int = (q.value("Fahrzeugmodell")).toInt();
        enum typ typ_db = int_toTyp(typ_int);
        QString art = (q.value("Fahrzeugart")).toString();
        QString kennzeichen = (q.value("Kennzeichen")).toString();
        QString farbe = (q.value("Farbe")).toString();
        int baujahr = (q.value("Baujahr")).toInt();
        int schaden_int = (q.value("Beschädigungsgrad")).toInt();
        enum schaden beschaedigung = int_toSchaden(schaden_int);

        int stellplatz_id = (q.value("StellplatzID")).toInt();
        QSqlQuery q_adr = db->get_stellplatz(stellplatz_id);
        Adresse *adr = nullptr;
        if(q_adr.next()) {
            QString ort = (q_adr.value("Stadt")).toString();
            QString plz = (q_adr.value("PLZ")).toString();
            QString strasse = (q_adr.value("Straße")).toString();
            QString hausnr = (q_adr.value("HausNr")).toString();
            adr = new Adresse(strasse, hausnr, plz, ort);
        } else {
            qDebug() << "Adresse zu Fahrzeug konnte nicht ermittelt werden!\n";
        }

        QString stellplatz_nr = (q.value("ParkplatzNr")).toString();
        int sitze_db = (q.value("AnzahlSitzplätze")).toInt();

        f = new Fahrzeug(fahrzeug_id, marke, typ_db, art, kennzeichen, farbe, baujahr, beschaedigung, adr, stellplatz_nr, sitze_db);
    } else {
        qDebug() << "Fahrzeug zu Buchung konnte nicht ermittelt werden!\n";
    }
    return f;
}

bool Buchungsverwaltung::buchung_abschliessen(Verleih *verleih, Buchung *buchung, Person *mieter)
{
    bool ok = false;
    int verleih_id = db->add_verleih(buchung->get_buchung_id(), verleih->get_abholdatum(), verleih->get_rueckgabedatum());
    if(verleih_id == -1) {
        qDebug() << "Verleih existiert nicht.\n";
    } else {
        int status = status_toInt(Buchungsstatus::abgeschlossen);
        ok = db->update_buchung_status(buchung->get_buchung_id(), status);
        if(!ok) {
            qDebug() << "Status nicht verändert.\n";
        } else {
            buchung->set_status(Buchungsstatus::abgeschlossen);
        }
    }
    return ok;
}

// Rechnung ist ergestellt nach der Rückgabe des Autos
bool Buchungsverwaltung::rechnung_erstellen(Verleih *verleih, Buchung *buchung)
{
    bool ok = false;
    double rechnungsbetrag = 0.0;

    if(verleih->get_tank() != 0)
    {
         rechnungsbetrag += TANK_KOSTEN;
    }

    double preis = verleih->get_km() * KM_PREIS;
    rechnungsbetrag += preis;



    int rechnung_id = db->add_rechnung(buchung->get_buchung_id(), rechnungsbetrag, verleih->get_km(), verleih->get_tank());
    if(rechnung_id == -1) {
        qDebug() << "Rechnung nicht erstellt.\n";
    } else {
        Rechnung *rechnung = new Rechnung(rechnungsbetrag, verleih->get_km(), verleih->get_tank(), rechnung_id);
        buchung->set_rechnung(rechnung);
        ok = true;
    }

    return ok;
}


