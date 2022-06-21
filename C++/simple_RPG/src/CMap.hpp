#pragma once

#include "CRoom.hpp"
#include "CActorProjectile.hpp"
#include "CActorItem.hpp"
#include "CActorPlayerInventory.hpp"
#include "CActorObstacle.hpp"
#include <iostream>
#include <map>
#include <ncurses.h>

/**
 * @brief handles rendering and updating game logic
 * 
 */
class CMap
{
private:
    /**
     * @brief coordinates of the player in the current room, <X, Y>
    */
    std::pair<int,int> playerPosInRoom;
public:
    /**
     * @brief coordinates of the player on the map, <X, Y> 
    */
    std::pair<int,int> playerPosInMap;

    /**
     * @brief map, keyed by coordinates <X, Y>, containing pointers to the rooms on those coordinates 
     */
    std::map< std::pair<int,int>, CRoom * > rooms;

    ~CMap();
    
    /**
     * @brief Completely erases, resizes and re-renders the given window with the contents of the given room
     * 
     * @param curWin ncurses window to use
     * @param toRender room which is to be rendered
     */
    void renderRoom( WINDOW * curWin, CRoom * toRender );
    // void openDoors( void );

    /**
     * @brief re-renders all the actors in a room, clears dead actors and updates all logic as needed
     * 
     * @param curWin window to write into
     * @param toRender room to update
     * @param input input from the player to be handed over to the actors move method
     * @param player pointer to the player CActor
     * @param gameTick current game tick to be handed over to the actors move method
     * @return true or false, if any actor moved or not
     */
    bool updateActors( WINDOW * curWin, CRoom * toRender, const int & input, CActorPlayerInventory * player, const int & gameTick );

    /**
     * @brief Prints the contents of the map to std::cerr, calls printActors for each room 
     */
    void printMapContents( void );

    /**
     * @brief Prints all the actors along with some of their attributes to std::cerr
     * 
     * @param toPrint vector of actors to print the contents of
     */
    void printActors( std::vector<CActor *> toPrint );

    /**
     * @brief Check whether there is an actor on given coordinates in the room given, ignoring the actor given, also handles deletion of projectiles upon reaching the walls
     * 
     * @param xyCoords coordinates to search for
     * @param curRoom room whose actors to go through
     * @param toIgnore actor to ignore, typically the one who is attempting to move to the coordinates given
     * @return CActor* of the entity found on given coordinates, nullptr if none found
     */
    CActor * checkCollision( const std::pair<int,int> & xyCoords,const CRoom * curRoom, CActor * toIgnore );

    /**
     * @brief Prints the doors, either open or closed, depending on doorsOpen bool from the room given, to window given.
     * 
     * @param curWin window into which to print
     * @param curRoom room from which to take the doorsOpen bool and coordinates to print to
     */
    void addDoors( WINDOW * curWin, CRoom * curRoom );

    /**
     * @brief spawns a CActorProjectile entity in front of the player and adds it to the curRoom actors vector
     * 
     * @param player pointer to the current player, used for coordinates and direction
     * @param curRoom room in which to spawn the projectiles
     * @param tick current game tick, projectiles will only spawn depending on spd of the player
     */
    void spawnProjectile( CActor * player, CRoom * curRoom, const int & tick );

    /**
     * @brief deletes all actors in the given room, whose deleteMe bool is set to 1 and erases the pointer from the vector of actors
     * 
     * @param toCleanse pointer to the room whose actors are to be cleansed
     */
    void annihilate( CRoom * toCleanse );

    /**
     * @brief Checks whether player is on the edge of a room in the doorway, changes their direction to reflect the direction they are going in
     * 
     * @param player pointer to the player, used for the x and y coordinates
     * @param curRoom pointer to the current room, used for the x and y coordinates of the doorways
     * @return std::pair<int,int> to be added to std::pair<int,int> playerPosInMap 
     */
    std::pair<int,int> changeRoom( CActor * player, CRoom * curRoom );

    /**
     * @brief Puts the player on the edge of a room depending on their direction, as if they just arrived in the room
     * 
     * @param player pointer to the player, used to change their coordinates
     * @param curRoom pointer to the current room, used to get the coordinates to change the player coordinates to
     */
    void repositionPlayer( CActor * player, CRoom * curRoom );

    /**
     * @brief Checks whether the player attempted to exit the room when the are no doors to go through, puts the player back where he began if yes
     * 
     * @param toRender pointer to the current room
     * @param player pointer to the player
     * @param movedTo coordinates where the player is attempting to move to
     * @param movedFrom coordinates where the player is moving from
     */
    void checkOutOfBounds( CRoom * toRender, std::pair<int,int>movedTo, std::pair<int,int>movedFrom, CActor * player );

    /**
     * @brief Checks whether the position in front of the player is occupied by a CActorItem, sets its deleteMe to true and calls player->addItem if yes
     * 
     * @param toRender room whose actors to search through
     * @param player pointer to the player
     */
    void interact( CRoom * toRender, CActorPlayerInventory * player );






};