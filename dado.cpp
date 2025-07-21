#include "dado.h"
#include <QRandomGenerator>

dado::dado() {}


int dado::tirar() {
    return QRandomGenerator::global()->bounded(1, 7); // 1 a 6
}
