TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle

QT += core gui

SOURCES += \
    casilla.cpp \
    casillaespecial.cpp \
    dado.cpp \
    juego.cpp \
    jugador.cpp \
    main.cpp \
    tablero.cpp

HEADERS += \
    casilla.h \
    casillaespecial.h \
    dado.h \
    juego.h \
    jugador.h \
    tablero.h
