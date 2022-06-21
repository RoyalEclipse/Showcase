#include "CActorEnemySlime.hpp"

CActorEnemySlime::CActorEnemySlime(int X, int Y, int HP,int DMG,int SPD, bool axisIsX )
{
    xPos = X;
    yPos = Y;
    health = HP;
    attackDamage = DMG;
    movementSpeed = SPD;
    type = 'O';
    if( axisIsX )
        axis = 'x';
    else
        axis = 'y';
    hitRight = false;
    deleteMe = false;
}

CActorEnemySlime::~CActorEnemySlime(){}

std::pair<int,int> CActorEnemySlime::move(const int & xSize, const int & ySize, const int & input, const int & tick, CActor * player  )
{

    if( tick % movementSpeed != 0 )
    {
        return std::make_pair( xPos, yPos );
    }

    if( xPos == 1 || xPos == (xSize - 2) || yPos == 1 || yPos == (ySize - 2) )
    {
        hitRight = !hitRight;
    }
    
    if( hitRight )
    {
        if( axis == 'x' ) xPos++;
        else yPos++;
    }
    else 
    {
        if( axis == 'x' ) xPos--;
        else yPos--;
    }   
    std::pair<int, int> toRet = {xPos, yPos};
    return toRet;
}
void CActorEnemySlime::attack()
{
    hitRight = !hitRight;
}