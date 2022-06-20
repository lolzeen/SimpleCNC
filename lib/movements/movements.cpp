#include "movements.hpp"

namespace MovementsLeo
{
    void Movements::moveLeft()
    {
        digitalWrite(ENX, HIGH);
        digitalWrite(DIRX, HIGH);
    }
    void Movements::moveRight()
    {
        digitalWrite(ENX, HIGH);
        digitalWrite(DIRX, LOW);
    }
    void Movements::moveUp()
    {
        digitalWrite(ENZ, HIGH);
        digitalWrite(DIRZ, HIGH);
    }
    void Movements::moveDown()
    {
        digitalWrite(ENZ, HIGH);
        digitalWrite(DIRZ, LOW);
    }
}