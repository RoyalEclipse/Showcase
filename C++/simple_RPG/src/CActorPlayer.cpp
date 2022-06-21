#include "CActorPlayer.hpp"

CActorPlayer::~CActorPlayer(){}

std::pair<int,int> CActorPlayer::move(const int & xSize, const int & ySize, const int & input, const int & tick, CActor * player )
{
    std::pair<int, int> toRet = {0, 0};

    switch (input)
    {
    case 'w':
        if( yPos != 1 || ( ( yPos == 1 ) && ( xPos == xSize/2 ) && canLeave == true ) )
        {
            direction = 0;
            yPos--; 
            break;
        }
        else return toRet;
    case 'a':
        if( xPos != 1 || ( ( xPos == 1 ) && ( yPos == ySize/2 ) && canLeave == true ) )
        {
            direction = 3;
            xPos--; 
            break;
        }
        else return toRet;
    case 's':
        if( yPos != (ySize - 2) || ( (yPos == ySize - 2) && ( xPos == xSize/2 ) && canLeave == true ) )
        {
            direction = 2;
            yPos++; 
            break;
        }
        else return toRet;
    case 'd':
        if( xPos != (xSize - 2) || ( (xPos == xSize - 2) && ( yPos == ySize/2 ) && canLeave == true ) )
        {
            direction = 1;
            xPos++;
            break;
        }
        else return toRet;
    default:
        break;
    }

    toRet = {xPos, yPos};
    return toRet;
}
void CActorPlayer::attack(){}