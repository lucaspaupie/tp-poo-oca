#include "jugador.h"

jugador::jugador(const QString& nombre): nombre(nombre), posicion(0) {}

void jugador::mover(int pasos){
    if(posicion + pasos <= 63){
        posicion += pasos;
    }
    else{
        int exceso = (posicion + pasos) - 63;
        posicion = 63 - exceso;
    }
}

int jugador::getPosicion() const{
    return posicion;
}

QString jugador::getNombre() const{
    return nombre;
}

bool jugador::ganador() const{
    return posicion == 63;
}
