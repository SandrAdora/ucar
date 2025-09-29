cmake_minimum_required(VERSION 3.5)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets Sql REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets Sql REQUIRED)

include(FetchContent)

FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

set(TEST_SOURCES
        test_suchen.cpp
        test_buchen.cpp
        test_stornieren.cpp
        test_datenbank_verbindung.cpp
        test_fahrzeug_reg.cpp
        test_main.cpp
        test_rechnung.cpp
        test_personregistrieren.cpp
        test_personanmelden.cpp
)

add_executable(unittest ${TEST_SOURCES})

target_include_directories(unittest PUBLIC googletest/include)
target_include_directories(unittest PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include/)
target_include_directories(unittest PUBLIC ${CMAKE_CURRENT_LIST_DIR})

target_link_libraries(unittest PUBLIC
        gtest_main
        src
)

include(GoogleTest)

add_test(
        NAME unittest
        COMMAND unittest
)
