#include "CActorEnemyZombie.hpp"

CActorEnemyZombie::CActorEnemyZombie(int X, int Y, int HP,int DMG,int SPD)
{
    xPos = X;
    yPos = Y;
    health = HP;
    attackDamage = DMG;
    movementSpeed = SPD;
    type = 'Z';
    deleteMe = false;

}

CActorEnemyZombie::~CActorEnemyZombie(){}

std::pair<int,int> CActorEnemyZombie::move(const int & xSize, const int & ySize, const int & input, const int & tick, CActor * player )
{
    if( tick % movementSpeed != 0 )
    {
        return std::make_pair( xPos, yPos );
    }

    if( player->xPos < this->xPos ){ xPos--; }
    else if( player->xPos > this->xPos ){ xPos++; }
    
    if( player->yPos < this->yPos ){ yPos--; }
    else if( player->yPos > this->yPos ){ yPos++; }

    std::pair<int, int> toRet = {xPos, yPos};
    return toRet;
}
void CActorEnemyZombie::attack(){}