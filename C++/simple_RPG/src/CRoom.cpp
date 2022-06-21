#include "CRoom.hpp"

CRoom::~CRoom()
{
    for( auto it = actors.begin(); it != actors.end(); it++)
    {
        if( *it != nullptr && (*it)->type != 'P' )
        {
            std::cerr << "deleting: " << (*it)->type << std::endl;
            delete (*it);
        }
    }
    actors.clear();
}

CRoom::CRoom(int sizeX, int sizeY, bool doorUp, bool doorDown, bool doorLeft, bool doorRight, bool noItem ):xSize(sizeX),ySize(sizeY),upDoor(doorUp),downDoor(doorDown),leftDoor(doorLeft),rightDoor(doorRight),openDoors(false),itemSpawned(noItem){}