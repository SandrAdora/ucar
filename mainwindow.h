#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTabWidget>
#include "suchansicht.h"
#include "buchungsansicht.h"
#include "fahrzeugansicht.h"
#include "profilansicht.h"
#include "person.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(Person *, QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QTabWidget *tabWidget;
    SuchAnsicht * s_ansicht;
    BuchungsAnsicht * b_ansicht;
    FahrzeugAnsicht * f_ansicht;
    ProfilAnsicht * p_ansicht;
    Person *person;
    enum Berechtigung berechtigung;

private slots:
    void tabWidget_clicked(int);
};
#endif // MAINWINDOW_H
