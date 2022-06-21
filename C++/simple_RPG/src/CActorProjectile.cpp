#include "CActorProjectile.hpp"

CActorProjectile::CActorProjectile(CActor * player )
{
    this->health = 1;
    this->attackDamage = player->attackDamage;
    this->direction = player->direction;
    this->type = 'o';
    this->deleteMe = false;

    switch (this->direction)
    {
    case 0:
        this->xPos = player->xPos;
        this->yPos = player->yPos - 1;
        break;
    case 1:
        this->xPos = player->xPos + 1;
        this->yPos = player->yPos;
        break;
    case 2:
        this->xPos = player->xPos;
        this->yPos = player->yPos + 1;
        break;
    case 3:
        this->xPos = player->xPos - 1;
        this->yPos = player->yPos;
        break;
    default:
        break;
    }
}

std::pair<int,int> CActorProjectile::move( const int & xSize, const int & ySize, const int & input, const int & tick, CActor * player  )
{
    switch (direction)
    {
    case 0:
        yPos--;
        break;
    case 1:
        xPos++;
        break;
    case 2:
        yPos++;
        break;
    case 3:
        xPos--;
        break;
    default:
        break;
    }

    return ( std::make_pair( xPos, yPos ) );
}

void CActorProjectile::attack(){ deleteMe = true; }