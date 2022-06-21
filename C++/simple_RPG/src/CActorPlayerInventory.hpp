#pragma once

#include "CActorPlayer.hpp"
#include "CItem.hpp"
#include <vector>
#include <ncurses.h>
#include <random>
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>

/**
 * @brief child of CActorPlayer with an inventory attached
 * 
 */
class CActorPlayerInventory : public CActorPlayer
{
    private: 

    public:
        std::vector<CItem *> inventory;
        CActorPlayerInventory(int HP,int DMG,int SPD );
        virtual ~CActorPlayerInventory();
        void useItem( const int toUse );
        void openInvScreen(WINDOW * gameWin);
        void printInventory( WINDOW * gameWin );
        void printLine( WINDOW * gameWin, int position );
        void addItem();


};