#include "tablero.h"


tablero::tablero()
{
    for(int i=0;i<=63;i++) {
        if(i==6){
            casillas.append(new casillaespecial(i, "punte"));
        }
        else if(i == 19){
            casillas.append(new casillaespecial(i, "posada"));
        }
        else if(i==31){
            casillas.append(new casillaespecial(i,"laberinto"));
        }
        else{
            casillas.append(new casillas(i));
        }
    }
}
tablero::~tablero() {
    qDeleteAll(casillas);
    casillas.clear();
}

void tablero::aplicarAccion(jugador& j) {
    int pos = j.getPosicion();
    if (pos >= 0 && pos < casillas.size()) {
        casillas[pos]->accion(j);
    }
}
