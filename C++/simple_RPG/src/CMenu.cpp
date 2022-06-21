#include "CMenu.hpp"

CMenu::CMenu()
{
    initscr();
    cbreak();
    noecho();
    curs_set(0);
    nonl();
    intrflush(stdscr, FALSE);
    // keypad(stdscr, TRUE);
    getmaxyx(stdscr, yMax, xMax);
    curWin = newwin(yMax/2, xMax/2, yMax/4, xMax/4); 
    box(curWin, 0, 0);
    curPos = 0;
    highlight( 0 );
}

CMenu::~CMenu()
{
    delwin( curWin );
    endwin();
}

int CMenu::mainScreen()
{
    while( true )
    {
        curButton = wgetch(curWin);
        if( curButton == 's' || curButton == 'w' )
        {
            changeMenuPos( curButton );
            highlight( curPos );
        }
        else if( curButton == 'd' || curButton == 'e' || curButton == ' ' )
            return curPos;
    }
}

void CMenu::highlight( int menuPos )
{
    printOptions();

    wattron(curWin, A_STANDOUT );
    
    switch ( menuPos )
    {
    case 0:
        mvwprintw(curWin, 2, 4, "New game");
        break;
    case 1:
        mvwprintw(curWin, 4, 4, "Load game");
        break;

    case 2:
        mvwprintw(curWin, 6, 4, "End game");
        break;

    default:
        break;
    }

    wattroff(curWin, A_STANDOUT );
}

void CMenu::highlightClass( int menuPos )
{
    printOptionsClass();

    wattron(curWin, A_STANDOUT );
    
    switch ( menuPos )
    {
    case 0:
        mvwprintw(curWin, 2, 4, "Mage");
        break;
    case 1:
        mvwprintw(curWin, 4, 4, "Tank");
        break;

    case 2:
        mvwprintw(curWin, 6, 4, "Rogue");
        break;

    default:
        break;
    }

    wattroff(curWin, A_STANDOUT );
}

void CMenu::printOptions()
{
    mvwprintw(curWin, 0, 2, "Welcome, adventurer!");
    mvwprintw(curWin, 2, 4, "New game");
    mvwprintw(curWin, 4, 4, "Load game");
    mvwprintw(curWin, 6, 4, "End game");
}

void CMenu::printOptionsClass()
{
    mvwprintw(curWin, 0, 2, "Select your class!");
    mvwprintw(curWin, 2, 4, "Mage");
    mvwprintw(curWin, 4, 4, "Tank");
    mvwprintw(curWin, 6, 4, "Rogue");

}

int CMenu::changeMenuPos( const char& buttonPressed )
{
    if( buttonPressed == 's' )
    {
        curPos += 1;
    }
    else if( buttonPressed == 'w' )
    {
        curPos -= 1;
    }

    if( curPos < 0 )
    {
        curPos = 2;
    }
    else
    {
        curPos = curPos % 3;
    }
    return curPos;
}

void CMenu::newGameScreen()
{
    werase( curWin );
    box(curWin, 0, 0);
    printOptionsClass();
    curPos = 0;
    highlightClass( curPos );
    int selectedClass;

    while( true )
    {
        curButton = wgetch(curWin);
        if( curButton == 's' || curButton == 'w' )
        {
            changeMenuPos( curButton );
            highlightClass( curPos );
        }
        else if( curButton == 'd' || curButton == 'e' || curButton == ' ' )
        {
            selectedClass = curPos;
            break;
        }
    }

    std::ifstream src("src/template.save", std::ios::binary);
    std::ofstream dest("src/default.save", std::ios::binary);

    dest << src.rdbuf() << std::flush;

    switch (selectedClass)
    {
    case 0:
        dest << "\n5 3 10 3 0 0 5 5\n";
        break;
    case 1:
        dest << "\n5 10 5 5 0 0 5 5\n";
        break;
    case 2:
        dest << "\n5 1 3 2 0 0 5 5\n";
        break;
    default:
        break;
    }

    src.close();
    dest.close();
}

int CMenu::pauseScreen( WINDOW * gameWin )
{

    wclear(gameWin);
    wrefresh(gameWin);
    getmaxyx(stdscr, yMax, xMax);
    wresize( gameWin, yMax/2, xMax/2 ); 
    box(gameWin, 0, 0);
    curPos = 0;
    highlightPause( 0, gameWin);

    while( true )
    {
        curButton = wgetch(gameWin);
        if( curButton == 's' || curButton == 'w' )
        {
            changeMenuPos( curButton );
            highlightPause( curPos, gameWin );
        }
        else if( curButton == 'd' || curButton == 'e' || curButton == ' ' )
            return curPos;
    }
}

void CMenu::printOptionsPause( WINDOW * gameWin )
{
    mvwprintw(gameWin, 0, 2, "What is thy wish?");
    mvwprintw(gameWin, 2, 4, "Open inventory");
    mvwprintw(gameWin, 4, 4, "Save progress");
    mvwprintw(gameWin, 6, 4, "Exit to terminal");

}

void CMenu::highlightPause( int menuPos, WINDOW * gameWin )
{
    printOptionsPause(gameWin);

    wattron(gameWin, A_STANDOUT );
    
    switch ( menuPos )
    {
    case 0:
        mvwprintw(gameWin, 2, 4, "Open inventory");
        break;
    case 1:
        mvwprintw(gameWin, 4, 4, "Save progress");
        break;

    case 2:
        mvwprintw(gameWin, 6, 4, "Exit to terminal");
        break;

    default:
        break;
    }

    wattroff(gameWin, A_STANDOUT );
}