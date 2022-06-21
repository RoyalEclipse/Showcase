#include "CActorPlayerInventory.hpp"

CActorPlayerInventory::CActorPlayerInventory(int HP,int DMG,int SPD )
{
    health = HP;
    attackDamage = DMG;
    movementSpeed = SPD;
    type = 'P';
    deleteMe = false;
    xPos = 5;
    yPos = 5;
    direction = 0;
    canLeave = false;
}

CActorPlayerInventory::~CActorPlayerInventory()
{
    for(auto it = inventory.begin(); it != inventory.end(); it++)
    {
        delete (*it);
    }
}

void CActorPlayerInventory::openInvScreen(WINDOW * gameWin)
{
    int yMax, xMax = 0;
    wclear(gameWin);
    wrefresh(gameWin);
    getmaxyx(stdscr, yMax, xMax);
    wresize( gameWin, yMax/2, xMax/2 ); 
    box(gameWin, 0, 0);

    inventory.shrink_to_fit();

    char input;
    int size = inventory.size();
    int position = 0;

    while( true )
    {
        input = wgetch( gameWin );
        flushinp();
        if( input == 'e' ) break;
        if( input == 's' ) position++;
        else if (input == 'w' )position--;

        if( position >= 5 || position > size ) position = 0;
        if( position < 0) position = size;

        printInventory( gameWin );
        wattron(gameWin, A_STANDOUT );
        printLine( gameWin, position );
        wattroff(gameWin, A_STANDOUT );
    }

    if( position == 0) return;
    useItem( position );

}
void CActorPlayerInventory::useItem( const int toUse )
{
    auto it = inventory.begin();
    for( int i = 0; i != toUse - 1; i++){ it++; }

    health += (*it)->healthChange;
    attackDamage += (*it)->damageChange;
    movementSpeed += (*it)->speedChange;
    if( health <= 0 ) health = 1;
    if( attackDamage <= 0 ) attackDamage = 1;
    if( movementSpeed <= 1 ) movementSpeed = 2;

    delete *( inventory.begin() + (toUse - 1 ) );
    inventory.erase( inventory.begin() + (toUse - 1 ) );
}

void CActorPlayerInventory::printLine( WINDOW * gameWin, int position )
{
    int xWritePos = 2;
    int yWritePos = 4;


    if( inventory.empty() || position == 0 )
    {
        mvwprintw(gameWin, 2, xWritePos, "Exit Inventory" );
        return;
    }


    auto it = inventory.begin();
    int counter = 0;

    for( ; it!= inventory.end(); it++ )
    {
        if( counter == position - 1 ) break;
        yWritePos += 2;
        counter++;
    }

    mvwprintw(gameWin, yWritePos, xWritePos, "%s", (*it)->itemName.data() );
}

void CActorPlayerInventory::printInventory( WINDOW * gameWin )
{
    int xWritePos = 2;
    int yWritePos = 4;
    mvwprintw(gameWin, 2, xWritePos, "exit Inventory" );
    
    if( inventory.empty() ) return;
    
    for( auto i = inventory.begin(); i != inventory.end(); i++ )
    {
        mvwprintw(gameWin, yWritePos, xWritePos, "%s", (*i)->itemName.data() );
        yWritePos++;
        mvwprintw(gameWin, yWritePos, xWritePos, "    %s", (*i)->itemDescription.data());
        yWritePos++;
    }
} 

void CActorPlayerInventory::addItem()
{
    srand (time(NULL));

    if( inventory.size() > 5 ) return;

    int positive = std::rand() % 3;
    int negative = std::rand() % 3;
    
    int hp = 0;
    int dmg = 0;
    int spd = 0;

    switch (positive)
    {
    case 0:
        hp += 2;
        break;
    case 1:
        dmg += 2;
        break;
    case 2:
        spd -= 2;
        break;
    default:
        break;
    }
    switch (negative)
    {
    case 0:
        hp -= 1;
        break;
    case 1:
        dmg -= 1;
        break;
    case 2:
        spd += 1;
        break;
    default:
        break;
    }

    std::ifstream nameList("src/namelist");
    std::string name;
    if( nameList.fail() || nameList.bad() )
    {
        std::cerr << "failed to load item names from src/namelist." << std::endl;
    }

    int lineNum = std::rand() % 100;

    do
    {
        getline(nameList, name);
        lineNum--;
    } while (lineNum > 0);
    
    std::stringstream strm(std::ios_base::in | std::ios_base::out);
    std::string description;

    strm << "HP: " << hp << " DMG: " << dmg << " SPD: " << spd << std::endl;
    description = strm.str();

    CItem * toSave = new CItem(hp, dmg, spd, name, description );
    inventory.emplace_back( toSave );
}
