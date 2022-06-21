#include "CActorObstacle.hpp"

CActorObstacle::CActorObstacle( int inRoomX, int inRoomY )
{
    xPos = inRoomX;
    yPos = inRoomY;
    health = 50000;
    attackDamage = 0;
    movementSpeed = 0;
    type = '#';
    deleteMe = false;

}

CActorObstacle::~CActorObstacle(){}

std::pair<int,int> CActorObstacle::move(const int & xSize, const int & ySize, const int & input, const int & tick, CActor * player )
{
    std::pair<int, int> toRet = {xPos, yPos};
    return toRet;
}
void CActorObstacle::attack(){}