#ifndef CASILLA_H
#define CASILLA_H

class jugador;

class casilla
{
protected:
    int numero;
public:
    casilla(int numero);
    virtual ~casilla();


    virtual void accion(jugador& j);
    int getNumero() const;
};

#endif // CASILLA_H
