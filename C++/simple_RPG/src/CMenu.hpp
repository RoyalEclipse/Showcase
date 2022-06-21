#pragma once

// #include "CGame.hpp"
#include <ncurses.h>
#include <math.h>
#include <iostream>
#include <fstream>

/**
 * @brief handles all game menus apart from inventory
 * 
 */
class CMenu
{
    private:
    
    int yMax;
    int xMax;
    char curButton;
    int curPos;

    public:
    WINDOW * curWin;

    CMenu();
    ~CMenu();

    /**
    * @brief Creates the main menu screen
    * @return int curPos at the time of pressing confirm, ie 'd', 'e' or ' ', 0 for new game, 1 for load game, 2 for end game
    */
    int mainScreen();

    /**
    * @brief Creates the class selection screen, creates and modifies default.save, copies over everything from template.save and adds a line for the player according to selected class
    */
    void newGameScreen();

    /**
     * @brief Resizes and uses given window to display the pause menu, which includes opitions to open inventory, save game or load game.
     * 
     * @param gameWin given ncurses window to use
     * @return int 
     */
    int pauseScreen( WINDOW * gameWin );

    /**
    * @brief Highlights an option in the main menu.
    * @param menuPos position in the menu to highlight, from 0 to 2
    */
    void highlight( int menuPos );

    /**
    * @brief Highlights an option in the class selection menu.
    * @param menuPos position in he menu to highlight, from 0 to 2
    * @return void
    */
    void highlightClass( int menuPos );

    /**
    * @brief Highlights an option in the pause selection menu.
    * @param menuPos position in he menu to highlight from 0 to 2
    * @param gameWin window to print into
    * @return void
    */
    void highlightPause( int menuPos, WINDOW * gameWin );

    /**
    * @brief Prints all options in their place in the main menu window
    */
    void printOptions();

    /**
    * @brief prints all options in their place in the class selection menu window
    */
    void printOptionsClass();

    /**
     * @brief prints all options in their place in the given window
     * 
     * @param gameWin ncurses window to print into
     */
    void printOptionsPause( WINDOW * gameWin );

    /**
    * @brief Changes menu pos depending on button pressed, automatically jumps to top or bottom.
    * @param buttonPressed current button pressed as given by wgetch()
    * @return new curPos as int
    */
    int changeMenuPos( const char& buttonPressed );
};