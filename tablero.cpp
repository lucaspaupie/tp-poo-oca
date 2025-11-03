#include "tablero.h"
#include "jugador.h"
#include "casillaespecial.h"
#include <QMap>
#include "mainwindow.h"
#include <random>   // <-- NUEVO
#include <QSet>     // <-- NUEVO (para evitar casillas duplicadas)
#include <QDebug>   // <-- NUEVO (opcional, para depurar)



tablero::tablero(int numCasillasElegidas)
{
    if (numCasillasElegidas < 63)
        numCasillasElegidas = 63;
    else if (numCasillasElegidas > 90)
        numCasillasElegidas = 90;

    m_numCasillas = numCasillasElegidas;

    for (int i = 0; i < m_numCasillas; ++i)
        casillas.append(new casilla(i));

    generarCasillasEspeciales();
    cargarCoordenadas();
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
QString tablero::moverJugador(jugador& j, int pasos) {
    int meta = casillas.size() - 1;
    int nuevaPos = j.getPosicion() + pasos;

    if (nuevaPos > meta) {
        int exceso = nuevaPos - meta;
        nuevaPos = meta - exceso; // Rebota
    }

    j.setPosicion(nuevaPos);

    QString mensaje = casillas[nuevaPos]->accion(j);

    // Si es una oca, saltamos automáticamente a la siguiente
    casillaespecial* especial = dynamic_cast<casillaespecial*>(casillas[nuevaPos]);
    if (especial && especial->getTipo() == "oca") {
        int siguiente = casillaespecial::siguienteOca(nuevaPos);
        if (siguiente != -1) {
            j.setPosicion(siguiente);  // Teletransporta
            mensaje += "\n¡De oca en oca y tiro porque me toca! (Avanzaste a la casilla " + QString::number(siguiente) + ")";
        }
    }
    return mensaje;
}

QPoint tablero::getCoordenadaCasilla(int casilla, int jugadorID) {
    // Usamos el jugadorID para calcular el offset, tal como se definió en el cpp
    if (casilla >= posicionesJugadores[0].size())
        return QPoint(0, 0);  // fallback
    QPoint base = posicionesJugadores[0][casilla];
    switch (jugadorID) {
    case 1: return base + QPoint(15, 0);
    case 2: return base + QPoint(0, 15);
    case 3: return base + QPoint(15,15);
    default: return base;
    }
}
void tablero::cargarCoordenadas() {
}

casilla* tablero::getCasilla(int numero){
    if(numero>=0 && numero < casillas.size()){
        return casillas[numero];
    }
    return nullptr;
}



void tablero::generarCasillasEspeciales() {

    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_int_distribution<> dis(1, m_numCasillas - 2);
    QSet<int> posicionesUsadas;

    // Hacemos que sea proporcional al tamaño del tablero
    int numOcas = m_numCasillas / 10;     // Ej: 64/10 = 6 ocas
    int numPuentes = m_numCasillas / 30;  // Ej: 64/30 = 2 puentes
    int numPozos = 1;
    int numPosadas = 1;
    int numLaberintos = 1;
    int numCarceles = 1;
    int numCalaveras = 1;

    // --- Función auxiliar (Lambda) para plantar una casilla ---
    // Esto es para no repetir código. Captura 'dis', 'gen', y 'posicionesUsadas'
    auto plantarEspecial = [&](const QString& tipo) {
        int pos;
        do {
            pos = dis(gen); // Elige un número al azar
        } while (posicionesUsadas.contains(pos)); // Si ya está usado, elige otro

        posicionesUsadas.insert(pos); // Marca la posición como usada

        // ¡IMPORTANTE! Borramos la casilla normal ANTES de reemplazarla
        delete casillas[pos];

        // Creamos y asignamos la nueva casilla especial
        casillas[pos] = new casillaespecial(pos, tipo);

       // qDebug() << "Generada casilla" << tipo << "en" << pos; // Para depurar
    };

    // --- Plantamos las casillas --- [cite: 31, 33]
    for (int i = 0; i < numOcas; ++i) {
        plantarEspecial("oca");
    }
    for (int i = 0; i < numPuentes; ++i) {
        plantarEspecial("puente");
    }
    for (int i = 0; i < numPosadas; ++i) { plantarEspecial("posada"); }
    for (int i = 0; i < numPozos; ++i) { plantarEspecial("pozo"); }
    for (int i = 0; i < numLaberintos; ++i) { plantarEspecial("laberinto"); }
    for (int i = 0; i < numCarceles; ++i) { plantarEspecial("carcel"); }
    for (int i = 0; i < numCalaveras; ++i) { plantarEspecial("calavera"); }
}
void tablero::setNumCasillas(int n)
{
    if (n < 1)
        n = 1;

    m_numCasillas = n;

    // Si ya había casillas, las eliminamos y regeneramos
    if (!casillas.isEmpty()) {
        qDeleteAll(casillas);
        casillas.clear();
    }

    // Crear las nuevas casillas básicas
    for (int i = 0; i < m_numCasillas; ++i) {
        casillas.append(new casilla(i));
    }

    qDebug() << "Tablero reconfigurado con" << m_numCasillas << "casillas.";
}

QJsonObject tablero::toJson() const { // <--- ¡AÑADE ESTO!
    QJsonObject json;
    json["numCasillas"] = m_numCasillas;
    return json;
}

tablero* tablero::fromJson(const QJsonObject& json) { // <--- ¡AÑADE ESTO!
    if (json.contains("numCasillas") && json["numCasillas"].isDouble()) {
        int num = json["numCasillas"].toInt();
        // Creamos un nuevo tablero con el número de casillas guardado
        return new tablero(num);
    }
    qWarning() << "Error al cargar el número de casillas desde JSON.";
    return nullptr;
}
#include "casillaespecial.h" // Necesario para dynamic_cast

QDataStream &operator<<(QDataStream &out, const tablero &t) {
    // 1. Guarda el número total de casillas
    out << t.numCasillas;

    // 2. Itera y guarda cada casilla (incluído el tipo para el polimorfismo)
    for (casilla* c : t.casillas) {
        if (casillaespecial* ce = dynamic_cast<casillaespecial*>(c)) {
            // Si es especial, guarda un identificador (1) y luego la casilla especial
            out << (quint8)1; // ID para casilla especial
            out << *ce;
        } else {
            // Si es normal, guarda un identificador (0) y luego la casilla base
            out << (quint8)0; // ID para casilla normal
            out << *c;
        }
    }
    return out;
}

QDataStream &operator>>(QDataStream &in, tablero &t) {
    // 1. Limpiar tablero actual (liberar memoria)
    for (casilla* c : t.casillas) {
        delete c;
    }
    t.casillas.clear();

    // 2. Cargar el número total de casillas
    in >> t.numCasillas;

    // 3. Itera y carga cada casilla
    for (int i = 0; i < t.numCasillas; ++i) {
        quint8 tipoID;
        in >> tipoID;

        casilla* c = nullptr;
        if (tipoID == 1) { // Casilla Especial
            casillaespecial ce;
            in >> ce;
            // IMPORTANTE: Crear una copia dinámica del objeto cargado
            c = new casillaespecial(ce);
        } else { // Casilla Normal (0)
            casilla cb;
            in >> cb;
            // IMPORTANTE: Crear una copia dinámica del objeto cargado
            c = new casilla(cb.getNumero()); // Asumo constructor por número
            c->setTipo(cb.getTipo());
        }
        t.casillas.append(c);
    }
    return in;
}
