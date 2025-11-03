#include "jugador.h"
#include <QJsonObject>
#include <QDebug>
#include <QDataStream>

// --- Serialización Binaria (QDataStream) ---

QDataStream &operator<<(QDataStream &out, const jugador &j) {
    out << j.nombre
        << j.posicion
        << j.turnosPenalizado
        << j.atrapado
        << j.repetirTurno;
    return out;
}


QDataStream &operator>>(QDataStream &in, jugador &j) {
    in >> j.nombre
        >> j.posicion
        >> j.turnosPenalizado
        >> j.atrapado
        >> j.repetirTurno;
    return in;
}

// --- Serialización JSON (Texto) ---

QJsonObject jugador::toJson() const {
    QJsonObject json;
    json["nombre"] = nombre;
    json["posicion"] = posicion;
    json["turnosPenalizado"] = turnosPenalizado;
    json["atrapado"] = atrapado;
    json["repetirTurno"] = repetirTurno;
    return json;
}

// Implementación de deserialización (Cargar)
jugador jugador::fromJson(const QJsonObject& json) {
    jugador j(json["nombre"].toString());

    j.posicion = json["posicion"].toInt();
    j.turnosPenalizado = json["turnosPenalizado"].toInt();
    j.atrapado = json["atrapado"].toBool();
    j.repetirTurno = json["repetirTurno"].toBool();

    return j;
}

// --- MÉTODOS EXISTENTES ---

jugador::jugador(const QString& nombre): nombre(nombre), posicion(0), turnosPenalizado(0) {}

void jugador::mover(int pasos) {
    if (posicion + pasos <= 63) {
        posicion += pasos;
    } else {
        int exceso = (posicion + pasos) - 63;
        posicion = 63 - exceso;
    }
}

int jugador::getPosicion() const{
    return posicion;
}
void jugador::setPosicion(int nuevaPos) { //set posicion para acomodarlo
    posicion = nuevaPos;
}
QString jugador::getNombre() const{
    return nombre;
}

bool jugador::ganador() const{
    return posicion == 63;
}

/////////////penalizar casilla/////////////////
void jugador::penalizar(int turnos) {
    turnosPenalizado += turnos;
    if (turnosPenalizado < 0) turnosPenalizado = 0; // Asegura que no sea negativo
}

bool jugador::estaPenalizado(){

    return turnosPenalizado>0;
}
void jugador::restarTurnosPenalizado(){
    if(turnosPenalizado>0){
        turnosPenalizado--;
    }
}

int jugador::getTurnosPenalizados() {
    if (turnosPenalizado < 0) turnosPenalizado = 0;
    return turnosPenalizado;
}

bool jugador::puedeJugar() {
    return !atrapado && turnosPenalizado <= 0;
}


void jugador::atrapar() {
    atrapado = true;
}

void jugador::liberar() {
    atrapado = false;
}

void jugador::retrocederACasilla(int nuevaPosicion) {
    posicion = nuevaPosicion;
}

void jugador::reiniciar() {
    posicion = 1;
}

void jugador::setRepetirTurno(bool val) {
    repetirTurno = val;
}

bool jugador::getRepetirTurno() const {
    return repetirTurno;
}

int jugador::getTurnosPenalizado() const {
    return turnosPenalizado;
}

bool jugador::estaAtrapado() const {
    return atrapado;
}
