#pragma once

#include "CActor.hpp"
#include <vector>

struct CRoom
{
    CRoom(int sizeX, int sizeY, bool doorUp, bool doorDown, bool doorLeft, bool doorRight, bool noItem);
    ~CRoom();
    int xSize;
    int ySize;
    /**
     * @brief vector containing pointers to all the actors in the room in no particular order 
     */
    std::vector<CActor *> actors;
    bool upDoor;
    bool downDoor;
    bool leftDoor;
    bool rightDoor;
    /**
     * @brief true if doors should be open, false otherwise, set to true when all hostile actors are deleted 
     */
    bool openDoors;
    
    /**
     * @brief  set to true when all hostile actors were defeated and an item spawned once already
     */
    bool itemSpawned;
};