#ifndef CASILLA_H
#define CASILLA_H
#include <QString>

class jugador;

class casilla
{
protected:
    int numero;
public:
    casilla(int numero);
    virtual ~casilla();


    virtual QString accion(jugador& j);
    int getNumero() const;
};

#endif // CASILLA_H
