#include "fahrzeugverwaltung.h"
#include <QSqlQuery>
#include <QVariant>
#include <vector>
#include <QDebug>

Fahrzeugverwaltung::Fahrzeugverwaltung()
{
    db = db->get_instanz();
}

Fahrzeugverwaltung::~Fahrzeugverwaltung() {
    delete db;
}

//Methoden: zum Fahrzeug registrieren:

//Rückgabe errorwert: =1: Fehler bei Fahrzeugmodell, =2: Fehler, Fahrzeug existiert bereits, =3: Fehler bei Stellplatzerstellung, =4: Fehler, gleicher Standort & ParkplatzNr existiert
//=5: Fehler bei Fahrzeugerstellung, =6: Fehler bei Zeitraumerstellung, =7: Fehler bei Zeitraumerstellung; kein Zeitraum erstellt
int Fahrzeugverwaltung::fahrzeug_registrieren(int nutzerID, QString kennzeichen, QString marke, QString art, QString farbe, int baujahr, int sitzplaetze, QString fahrzeugtyp, int beschaedigung, QString stadt,
                                              QString plz, QString strasse, QString hausnr, int parkplatznr,QTime mo_von, QTime mo_bis, QTime di_von, QTime di_bis,
                                              QTime mi_von, QTime mi_bis, QTime do_von, QTime do_bis, QTime fr_von, QTime fr_bis, QTime sa_von, QTime sa_bis, QTime so_von, QTime so_bis){
    int error=0;
    qDebug()<<"Fmodell: "<<fahrzeugtyp;

    //Umwandeln von String Fahrzeugtyp zu int
    int fmodell=typ_toInt(fahrzeugtyp);
    if(fmodell==-1) {
        qDebug() << "fahrzeug_registrieren error bei fahrzeugmodell_string_zu_int";

        error=1;
        return error;
    }

    //Fahrzeug existiert beretis?
    int fid=db->get_fahrzeug_zu_werten(kennzeichen, marke, farbe, baujahr, beschaedigung, sitzplaetze, art, fmodell, nutzerID);
    if(fid!=-1) {
        qDebug() << "fahrzeug_registrieren error bei fahrzeug_existiert bereits";

        error=2;
        return error;
    }

    //Stellplatzerstellung in DB und Überprüfung
    int sid=this->stellplatz_registrieren(stadt, plz, strasse, hausnr, parkplatznr);
    if(sid==-1)
    {
        error=3;
        return error;
    } else {
        if(sid==-2) {
            error=4;
            return error;
        }
    }



    //Erstellung von Fahrzeug in DB
    fid=db->add_fahrzeug(kennzeichen, marke, farbe, baujahr, beschaedigung, sitzplaetze, art, fmodell, sid, parkplatznr, nutzerID);
    if(fid==-1) {
        qDebug() << "fahrzeug_registrieren error bei Fahrzeugerstellung";
        db->delete_stellplatz(sid);

        error=5;
        return error;
    }

    //Erstellung der Zeiträume
    int z0=this->zeitraum_ueberpruefen(fid, 1, mo_von, mo_bis);
    int z1=this->zeitraum_ueberpruefen(fid, 2, di_von, di_bis);
    int z2=this->zeitraum_ueberpruefen(fid, 3, mi_von, mi_bis);
    int z3=this->zeitraum_ueberpruefen(fid, 4, do_von, do_bis);
    int z4=this->zeitraum_ueberpruefen(fid, 5, fr_von, fr_bis);
    int z5=this->zeitraum_ueberpruefen(fid, 6, sa_von, sa_bis);
    int z6=this->zeitraum_ueberpruefen(fid, 7, so_von, so_bis);
    if(z0==-1 || z1==-1 || z2==-1 || z3==-1 || z4==-1 || z5==-1 || z6==-1) {
        qDebug() << "fahrzeug_registrieren error bei Zeitraumerstellung";
        db->delete_stellplatz(sid);
        db->delete_fahrzeug(fid);

        error=6;
        return error;
    } else { if(z0==0 && z1==0 && z2==0 && z3==0 && z4==0 && z5==0 && z6==0) {
            qDebug() << "fahrzeug_registrieren error bei Zeitraumerstellung: kein Zeitraum erstellt";
            db->delete_stellplatz(sid);
            db->delete_fahrzeug(fid);

            error=7;
            return error;
        }
    }
    return error;
}

int Fahrzeugverwaltung::zeitraum_ueberpruefen(int fid, int tag, QTime startzeit, QTime endzeit) {
    int ret=0;

    double von_min=static_cast<double>(startzeit.minute());
    double bis_min=static_cast<double>(endzeit.minute());
    double von=startzeit.hour() + (von_min/60);
    double bis=endzeit.hour() + (bis_min/60);

    if(von<bis) {
        ret=db->add_zeitraum(fid, tag, von, bis);
    }
    return ret;
}



//Stellplatzerstellung zu übergebenen Daten; wenn Standort bereits existiert: dessen ID zurückgegeben
//bei Fehler bei Erstellung: Rückgabe=-1; bei Fehler, weil Stellplatz und Fahrzeug mit gleicher Parkplatznr existiert: Rückgabe=-2
int Fahrzeugverwaltung::stellplatz_registrieren(QString stadt, QString plz, QString strasse, QString hausnr, int parkplatznr) {
    int stellplatzid=-1;

    //wenn als str./ strasse angegeben: ändern zu straße um einheitlich zu bleiben
    if(strasse.endsWith("str.")) {
        int len=strasse.length();
        strasse=strasse.left(len-4);
        strasse.append("straße");
    } else{
        if(strasse.endsWith("strasse")) {
            int len=strasse.length();
            strasse=strasse.left(len-7);
            strasse.append("straße");
        }
    }

    //Überprüfung, ob Stellplatz schon existiert: wenn ja, dann diese ID benutzen
    stellplatzid=db->get_stellplatz_zu_adresse(stadt, plz, strasse, hausnr);
    if(stellplatzid==-1)
    {
        //Stellplatz noch nicht vorhanden
        stellplatzid=db->add_stellplatz(stadt, plz, strasse, hausnr);
        if(stellplatzid==-1) {
            qDebug() << "stellplatz_registrieren error bei Stellplatzerstellung";

        }
    } else { //Überprüfung, ob Fahrzeug mit gleiche ParkplatzNr existiert
        QSqlQuery q=db->get_fahrzeug_zu_stellplatz(stellplatzid);
        while(q.next())
        {
            if(q.value("ParkplatzNr").toInt()==parkplatznr) {
                stellplatzid=-2;
                qDebug()<< "stellplatz_registrieren error bei ParkplatzNr mit Standort existiert bereits";
            }
        }
    }

    return stellplatzid;
}


//Methode zur Fahrzeugsuche
std::vector<Fahrzeug *> Fahrzeugverwaltung::fahrzeug_suchen(int sitze, QString stadt, int typ, QDate datum, QTime beginn, QTime ende) {
    std::vector<Fahrzeug *> vec;
    int datum_int = datum.dayOfWeek();
    double beginn_min = static_cast<double>(beginn.minute());
    double ende_min = static_cast<double>(ende.minute());
    double beginn_double = beginn.hour() + (beginn_min/60);
    double ende_double = ende.hour() + (ende_min/60);

    //alle passenden Fahrzeuge aus der DB anfragen und Vector damit füllen
    QSqlQuery q = db->get_fahrzeug_suchen(sitze, stadt, typ, datum_int, beginn_double, ende_double);
    vec = vector_erstellen(q);

    //Überprüfung, ob bereits Buchung in dem gewählten Zeitraum existiert
    std::vector<Fahrzeug *>::iterator itr = vec.begin();
    QDateTime wunsch_beginn = QDateTime(datum, beginn);
    QDateTime wunsch_ende = QDateTime(datum, ende);
    bool frei = true;
    while(itr != vec.end()) {
        QSqlQuery q_bng = db->get_buchung_zu_fahrzeug((*itr)->get_fahrzeug_id());
        if(!q_bng.isActive()) {
            qDebug() << "Buchungen zu Fahrzeug konnten nicht ermittelt werden!\n";
        } else {
            while(q_bng.next()) {
                QString adat_str = (q_bng.value("Ausleihe_datum")).toString();
                QString azeit_str = (q_bng.value("Ausleihe_zeit")).toString();
                QDate adat = QDate::fromString(adat_str, "dd.MM.yyyy");
                QTime azeit = QTime::fromString(azeit_str, "hh:mm:ss");
                QDateTime ausleihe = QDateTime(adat, azeit);

                QString rdat_str = (q_bng.value("Rückgabe_datum")).toString();
                QString rzeit_str = (q_bng.value("Rückgabe_zeit")).toString();
                QDate rdat = QDate::fromString(rdat_str, "dd.MM.yyyy");
                QTime rzeit = QTime::fromString(rzeit_str, "hh:mm:ss");
                QDateTime rueckgabe = QDateTime(rdat, rzeit);

                if((wunsch_beginn < ausleihe && wunsch_ende < ausleihe) || (wunsch_beginn > rueckgabe && wunsch_ende > rueckgabe)) {
                    frei = true;
                } else {
                    frei = false;
                    break;
                }
            }
        }
        if(frei) {
            itr++;
        } else {
            vec.erase(itr);
        }
    }
    return vec;
}

//Methode zur Anfrage aller Fahrzeuge eines Vermieters
std::vector<Fahrzeug *> Fahrzeugverwaltung::fahrzeuge_zu_person(int vermieter_id) {
    std::vector<Fahrzeug *> vec;
    QSqlQuery q = db->get_fahrzeug_zu_person(vermieter_id);
    vec = vector_erstellen(q);
    return vec;
}

//Methode zum Füllen eines Vectors mit Tupeln einer DB-Abfrage (ausgelagert, um Code-Duplikat) zu vermeiden)
std::vector<Fahrzeug *> Fahrzeugverwaltung::vector_erstellen(QSqlQuery q) {
    std::vector<Fahrzeug *> vec;
    if(!q.isActive()) {
        qDebug() << "Fahrzeuge konnten nicht ermittelt werden!\n";
    } else {
        while(q.next()) {
            //Vector mit allen passenden Fahrzeugen füllen
            int id = (q.value("FahrzeugID")).toInt();
            QString marke = (q.value("Marke")).toString();
            int typ_int = (q.value("Fahrzeugmodell")).toInt();
            enum typ typ_db = int_toTyp(typ_int);
            QString art = (q.value("Fahrzeugart")).toString();
            QString kennzeichen = (q.value("Kennzeichen")).toString();
            QString farbe = (q.value("Farbe")).toString();
            int baujahr = (q.value("Baujahr")).toInt();
            int schaden_int = (q.value("Beschädigungsgrad")).toInt();
            enum schaden beschaedigung = int_toSchaden(schaden_int);

            std::array<Zeitraum *, 7> arr_zeit;
            arr_zeit.fill(nullptr);
            QSqlQuery q_zeit = db->get_zeitraum_zu_fahrzeug(id);
            while(q_zeit.next()) {
                int tag = (q_zeit.value("Tag")).toInt();
                double beginn_double = (q_zeit.value("Mietbeginn")).toDouble();
                double ende_double = (q_zeit.value("Mietende")).toDouble();
                QString beginn_str = "";
                beginn_str.setNum(beginn_double, 'f', 2);
                if(beginn_double < 10) {
                    beginn_str.prepend("0");
                }
                QString ende_str = "";
                ende_str.setNum(ende_double, 'f', 2);
                if(ende_double < 10) {
                    ende_str.prepend("0");
                }
                QTime beginn = QTime::fromString(beginn_str, "hh.mm");
                QTime ende = QTime::fromString(ende_str, "hh.mm");
                Zeitraum *z = new Zeitraum(beginn, ende);
                arr_zeit.at(tag-1) = z;
            }

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

            Fahrzeug *neu = new Fahrzeug(id, marke, typ_db, art, kennzeichen, farbe, baujahr, beschaedigung, arr_zeit, adr, stellplatz_nr, sitze_db);
            vec.push_back(neu);
        }
    }
    return vec;
}
