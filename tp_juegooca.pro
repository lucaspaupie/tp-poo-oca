TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle

QT += core gui \
    widgets

SOURCES += \
    casilla.cpp \
    casillaespecial.cpp \
    dado.cpp \
    juego.cpp \
    jugador.cpp \
    main.cpp \
    mainwindow.cpp \
    tablero.cpp

HEADERS += \
    casilla.h \
    casillaespecial.h \
    dado.h \
    juego.h \
    jugador.h \
    mainwindow.h \
    tablero.h

FORMS += \
    mainwindow.ui

RESOURCES += \
    imagen.qrc
