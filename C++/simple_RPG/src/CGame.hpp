#pragma once

#include "CActor.hpp"
#include "CActorEnemySlime.hpp"
#include "CActorEnemyZombie.hpp"
#include "CActorItem.hpp"
#include "CActorObstacle.hpp"
#include "CActorPlayer.hpp"
#include "CActorPlayerInventory.hpp"
#include "CActorProjectile.hpp"
#include "CMenu.hpp"
#include "CMap.hpp"
#include <ncurses.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <chrono>
#include <thread>
#include <stdio.h>

/**
 * @brief main game class, handles virtually everything
 * 
 */
class CGame
{
private:
    int gameState;

    /**
     * @brief pointer to the current map, to be filled by loadgame 
     */
    CMap * curMap;

    std::pair<int, int> lastRoom;
    CActorPlayerInventory * player;
    char curButton;
    CMenu menu;

    /**
     * @brief checks whether a CActorPlayer is present in a room already
     * 
     * @param toCheck room whose actors to check
     * @return true if player present, false otherwise
     */
    bool checkForPlayer( CRoom * toCheck );

public:
    CGame();
    ~CGame();

    /**
     * @brief main game function, handles literally everything
     * 
     * @return int 0 if exited correctly, 1 otherwise
     */
    int startGame();

    /**
     * @brief saves the contents of curMap to a custom.save file in the correct format
     * 
     * @return true on success, false otherwise
     */
    bool saveGame();

    /**
     * @brief Loads game from custom.save or default.save depending on bool given
     * 
     * @param useDefault 
     * @return int 0 on success, 1 on fail 
     */
    int loadGame( bool useDefault);

    /**
     * @brief Parses the string given for all the variables necessary and saves the room to curMap
     * 
     * @param toParse string containing numbers to parse through
     * @return int 0 on success, 1 on fail
     */
    int parseRoom( std::string & toParse );

    /**
     * @brief Parses the string given for all the variables necessary and saves the actor to the last room parsed
     * 
     * @param toParse string containing numbers to parse through
     * @return int 0 on success, 1 on fail
     */
    int parseActor( std::string & toParse );

    /**
     * @brief supporting function for parse actor, iterates through the int vector created by parse actor and modifies the variables given
     * 
     * @param X x coordinate of the actor being parsed
     * @param Y y coordinate of the actor being parsed
     * @param foundIt iterator to use
     * @return 0 on success, 1 on fail
     */
    int parseCoords( int &X, int &Y, std::vector<int>::iterator & foundIt);

    /**
     * @brief supporting function for parse actor, iterates through the int vector created by parse actor and modifies the variables given
     * 
     * @param HP hp of the actor being parsed
     * @param DMG dmg of the actor being parsed
     * @param SPD spd of the actor being parsed
     * @param foundIt iterator to use 
     * @return 0 on success, 1 on fail
     */
    int parseAttributes(int &HP, int &DMG, int &SPD, std::vector<int>::iterator & foundIt);

    /**
     * @brief Handles the pause menu, calls all the necessary functions
     * 
     * @param gameWin current ncurses window to be handed over to player->openInvScreen method
     */
    void handlePause( WINDOW * gameWin );
    // WINDOW * createGameWindow();

    /**
     * @brief increases and modulates the given game tick variable
     * 
     * @param gameTick variable to be modified
     * @return new gameTick value
     */
    int modulateTicks( int & gameTick );
    
    /**
     * @brief supporting function for parse actor, modifies the variables given
     * 
     * @param name name of the CItem to be saved in player inventory
     * @param desc description of the CItem to be saved in player inventory
     * @param HP health change of the CItem to be saved in player inventory
     * @param DMG damage change of the CItem to be saved in player inventory
     * @param SPD speed change of the CItem to be saved in player inventory
     * @return int 0 on success 1 on fail
     */
    int parseItem( std::string & name, std::string & desc, int & HP, int & DMG, int & SPD, std::string toParse );

};