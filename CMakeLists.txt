cmake_minimum_required(VERSION 3.5)

project(U-Car VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Core Widgets Sql REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Widgets Sql REQUIRED)

enable_testing()

add_subdirectory(test)

set(PROJECT_SOURCES
        mainwindow.h
        mainwindow.cpp
        mainwindow.ui
        loginansicht.h
        loginansicht.cpp
        loginansicht.ui

        suchansicht.h
        suchansicht.cpp
        suchansicht.ui
        buchungsansicht.h
        buchungsansicht.cpp
        buchungsansicht.ui
        fahrzeugansicht.h
        fahrzeugansicht.cpp
        fahrzeugansicht.ui
        profilansicht.h
        profilansicht.cpp
        profilansicht.ui

        kontoreg.h
        kontoreg.cpp
        kontoreg.ui
        fahrzeugreg.h
        fahrzeugreg.cpp
        fahrzeugreg.ui
        buchungreg.h
        buchungreg.cpp
        buchungreg.ui

        fahrzeugdetail.h
        fahrzeugdetail.cpp
        fahrzeugdetail.ui
        buchungdialogmieter.h
        buchungdialogmieter.cpp
        buchungdialogmieter.ui
        buchungdialogvermieter.h
        buchungdialogvermieter.cpp
        buchungdialogvermieter.ui
        abschlussdetail.h
        abschlussdetail.cpp
        abschlussdetail.ui
        rechnungdetail.h
        rechnungdetail.cpp
        rechnungdetail.ui
        
        adresse.h
        adresse.cpp
	stellplatz.h
	stellplatz.cpp

        adresse.h
        adresse.cpp
        stellplatz.h
        stellplatz.cpp
        buchung.h
        buchung.cpp
        buchungsverwaltung.h
        buchungsverwaltung.cpp
        verleih.h
        verleih.cpp
        rechnung.h
        rechnung.cpp
        zahlung.h
        zahlung.cpp

        fahrzeugmodell.h
        fahrzeugmodell.cpp
        fahrzeug.h
        fahrzeug.cpp
        fahrzeugverwaltung.h
        fahrzeugverwaltung.cpp
        zeitraum.h
        zeitraum.cpp

        mieter.h
        mieter.cpp
        mieterverwaltung.h
        mieterverwaltung.cpp
        vermieter.h
        vermieter.cpp
        vermieterverwaltung.h
        vermieterverwaltung.cpp
        person.h
        person.cpp

        datenbank_verbindung.h
        datenbank_verbindung.cpp
)

add_library(src SHARED ${PROJECT_SOURCES})

target_link_libraries(src PUBLIC
        Qt${QT_VERSION_MAJOR}::Core
        Qt${QT_VERSION_MAJOR}::Widgets
        Qt${QT_VERSION_MAJOR}::Sql
)

add_executable(U-Car main.cpp)

target_include_directories(U-Car PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include/)
target_include_directories(U-Car PUBLIC ${CMAKE_CURRENT_LIST_DIR})

target_link_libraries(U-Car PUBLIC
        src
)

