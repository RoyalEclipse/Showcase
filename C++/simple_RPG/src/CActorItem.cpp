#include "CActorItem.hpp"

CActorItem::CActorItem( int inRoomX, int inRoomY )
{
    xPos = inRoomX;
    yPos = inRoomY;
    health = 50000;
    attackDamage = 0;
    movementSpeed = 0;
    type = '?';
    deleteMe = false;

}

CActorItem::~CActorItem(){}

std::pair<int,int> CActorItem::move(const int & xSize, const int & ySize, const int & input, const int & tick, CActor * player )
{
    std::pair<int, int> toRet = {xPos, yPos};
    return toRet;
}
void CActorItem::attack(){}