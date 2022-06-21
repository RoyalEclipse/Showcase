#include "CMap.hpp"

CMap::~CMap()
{
    for( auto it = rooms.begin(); it != rooms.end(); it++ )
    {
        delete (*it).second;
    }
}

void CMap::renderRoom( WINDOW * curWin, CRoom * toRender )
{
    wclear(curWin);
    wrefresh(curWin);
    wrefresh(stdscr);

    int xMax, yMax;
    getmaxyx(stdscr, yMax, xMax );
    wresize(curWin, toRender->ySize, toRender->xSize );
    int uLeftY = (yMax - toRender->ySize) / 2;
    int uLeftX = (xMax - toRender->xSize) / 2;
    mvwin(curWin, uLeftY, uLeftX );
    box(curWin, 0, 0);
    
    wrefresh(curWin);

    int yRelative = 0;
    int xRelative = 0;
    char representation;

    for(auto it = toRender->actors.begin(); it != toRender->actors.end(); it++ )
    {
        yRelative = (*it)->yPos;
        xRelative = (*it)->xPos;
        representation = (*it)->type;

        mvwaddch(curWin, yRelative, xRelative, representation);
    }
    toRender->openDoors=false;
    addDoors(curWin, toRender);

    wrefresh(curWin);
}

// void CMap::openDoors( void ){}

bool CMap::updateActors( WINDOW * curWin, CRoom * toRender, const int & input, CActorPlayerInventory * player, const int & gameTick )
{
    int ySize, xSize;
    std::pair<int,int> movedFrom;
    std::pair<int,int> movedTo;

    bool somethingMoved = false;

    getmaxyx(curWin, ySize, xSize );

    annihilate( toRender );

    if( input == ' ' ) spawnProjectile( player, toRender, gameTick );
    if( input == 'e' ){ interact( toRender, player ); somethingMoved = true; }
    bool enemiesLeft = false;

    // moves and checks for collisions
    for(auto it = toRender->actors.begin(); it != toRender->actors.end(); it++ )
    {
        // check for remaining enemies, used for opening doors
        if( (*it)->type == 'Z' || (*it)->type == 'O' ) enemiesLeft = true;

        // attempt to move
        movedFrom = { (*it)->xPos , (*it)->yPos };
        if( (*it)->type == 'P' && input == -1 ) continue;
        movedTo = (*it)->move(xSize, ySize, input, gameTick, player);
        if( (*it)->type == 'P' ) checkOutOfBounds( toRender, movedTo, movedFrom, (*it) );

        // check for collisions, deal dmg and reset if yes
        CActor * collidedWith = checkCollision(movedTo, toRender, (*it) );
        if( collidedWith != nullptr )
        {
            (*it)->attack();
            collidedWith->takeDamage( (*it)->attackDamage );
            (*it)->xPos = movedFrom.first;
            (*it)->yPos = movedFrom.second;
        }

        if( movedTo != std::make_pair(0,0) ) somethingMoved = true;
    }

    if( enemiesLeft == false )
    { 
        toRender->openDoors = true;
        
        if( toRender->itemSpawned == false)
        {
            CActor * item = new CActorItem( toRender->xSize/2, toRender->ySize/2 );
            toRender->actors.emplace_back( item );
            toRender->itemSpawned = true;
        }
    }
    // annihilate(toRender);

    // if something moved then redraw and refresh screen
    if( somethingMoved )
    {
        int yRelative, xRelative;
        char representation;
    
        werase(curWin);
        box(curWin, 0, 0);

        for(auto it = toRender->actors.begin(); it != toRender->actors.end(); it++ )
        {
            yRelative = (*it)->yPos;
            xRelative = (*it)->xPos;
            representation = (*it)->type;
    
            mvwaddch(curWin, yRelative, xRelative, representation);
        }
    
        addDoors(curWin, toRender);
        wrefresh(curWin);
    }
    return somethingMoved;
}

void CMap::interact( CRoom * toRender, CActorPlayerInventory * player )
{
    int xToSearch = player->xPos;
    int yToSearch = player->yPos;

    switch ( player->direction )
    {
    case 0:
        yToSearch--;
        break;
    case 1:
        xToSearch++;
        break;
    case 2:
        yToSearch++;
        break;
    case 3:
        xToSearch--;
        break;
    default:
        break;
    }
    auto res = checkCollision( std::make_pair( xToSearch, yToSearch ), toRender, player );

    if( res == nullptr ) return;

    if( res->type == '?' )
    {
        res->deleteMe = true;
        player->addItem();
    }

}

void CMap::checkOutOfBounds( CRoom * toRender, std::pair<int,int>movedTo, std::pair<int,int>movedFrom, CActor * player )
{
    bool rollback = false;

    if( ( movedTo.second == 0 ) && ( movedTo.first == toRender->xSize/2 ) && !toRender->upDoor) { rollback = true; }
    else if( ( movedTo.first == 0 ) && ( movedTo.second == toRender->ySize/2 ) && !toRender->leftDoor){ rollback = true; }
    else if( (movedTo.second == toRender->ySize - 1) && ( movedTo.first == toRender->xSize/2 ) && !toRender->downDoor){ rollback = true; }
    else if( (movedTo.first == toRender->xSize - 1) && ( movedTo.second == toRender->ySize/2 ) && !toRender->rightDoor){ rollback = true; }

    if( rollback )
    {
        player->xPos = movedFrom.first;
        player->yPos = movedFrom.second;
    }

}

void CMap::annihilate( CRoom * toCleanse )
{
    int size = toCleanse->actors.size();
    for( auto i = 0; i < size; i++ )
    {
        if( toCleanse->actors.at(i)->deleteMe == true && toCleanse->actors.at(i)->type != 'P' )
        {
            delete toCleanse->actors.at(i);
            toCleanse->actors.erase( ( toCleanse->actors.begin() + i ) );
            size = toCleanse->actors.size();
            i--;
        }
    }
}

std::pair<int,int> CMap::changeRoom( CActor * player, CRoom * curRoom )
{
    if( player->xPos < 1 || player->xPos > curRoom->xSize - 2 || player->yPos < 1 || player->yPos > curRoom->ySize - 2 )
    {
        if( player->xPos < 1 && player->yPos == curRoom->ySize/2 )
        {
            player->direction = 3;
            return std::make_pair( -1, 0 );
        }
        else if( player->xPos > curRoom->xSize - 2 && player->yPos == curRoom->ySize/2 )
        {
            player->direction = 1;
            return std::make_pair( 1, 0 );
        }
        else if( player->yPos < 1 && player->xPos == curRoom->xSize/2 )
        {
            player->direction = 0;
            return std::make_pair( 0, -1 );
        }
        else if( player->yPos > curRoom->ySize - 2 && player->xPos == curRoom->xSize/2 )
        {
            player->direction = 2;
            return std::make_pair( 0, 1 );
        }
    }
    return std::make_pair( 0, 0 );
}

void CMap::repositionPlayer( CActor * player, CRoom * curRoom )
{
    switch (player->direction)
    {
    case 0:
        player->xPos = curRoom->xSize/2 ;
        player->yPos = curRoom->ySize - 2;
        break;
    case 1:
        player->xPos =  1;
        player->yPos =  curRoom->ySize/2;
        break;
    case 2:
        player->xPos = curRoom->xSize/2 ;
        player->yPos =  1;
        break;
    case 3:
        player->xPos =  curRoom->xSize - 2;
        player->yPos =  curRoom->ySize/2;
        break;
    
    default:
        break;
    }
}

CActor * CMap::checkCollision( const std::pair<int,int> & xyCoords, const CRoom * curRoom, CActor * toIgnore )
{

    if( toIgnore->type=='o' && ( xyCoords.first <= 0 || xyCoords.second <= 0 || xyCoords.first >= curRoom->xSize || xyCoords.second >= curRoom->ySize ) )
    {
        toIgnore->deleteMe = true;
        return nullptr;
    }

    for( auto it = curRoom->actors.begin(); it != curRoom->actors.end(); it++ )
    {
        if( xyCoords == std::make_pair( (*it)->xPos, (*it)->yPos  ) && (*it) != toIgnore ) return *it;
    }
    
    return nullptr;
}

void CMap::addDoors( WINDOW * curWin, CRoom * curRoom )
{
    char doorVertical = '|';
    char doorHorizontal = '-';
    char doorOpen = ' ';

    if(curRoom->openDoors == false )
    {
        if(curRoom->leftDoor)   mvwaddch(curWin, curRoom->ySize/2, 0, doorVertical);
        if(curRoom->upDoor)     mvwaddch(curWin, 0, curRoom->xSize/2, doorHorizontal);
        if(curRoom->rightDoor)  mvwaddch(curWin, curRoom->ySize/2, curRoom->xSize - 1, doorVertical);
        if(curRoom->downDoor)   mvwaddch(curWin, (curRoom->ySize-1), (curRoom->xSize/2), doorHorizontal);
    }
    else
    {
        if(curRoom->leftDoor)   mvwaddch(curWin, curRoom->ySize/2, 0, doorOpen);
        if(curRoom->upDoor)     mvwaddch(curWin, 0, curRoom->xSize/2, doorOpen);
        if(curRoom->rightDoor)  mvwaddch(curWin, curRoom->ySize/2, curRoom->xSize - 1, doorOpen);
        if(curRoom->downDoor)   mvwaddch(curWin, (curRoom->ySize-1), (curRoom->xSize/2), doorOpen);
    }

    wrefresh(curWin);
}

void CMap::spawnProjectile( CActor * player, CRoom * curRoom, const int & tick )
{
    if( tick % player->movementSpeed != 0 ) return;
    CActor * projectile = new CActorProjectile( player );
    curRoom->actors.emplace_back( projectile );
}

void CMap::printMapContents( void )
{
    if( rooms.empty() )
    {
        std::cerr << "current map is empty." << std::endl;
    }
    
    for ( auto it = rooms.begin(); it != rooms.end(); it++ )
    {
        std::cerr << "xsize: " << (*it).second->xSize << " ySize: " << (*it).second->ySize <<
        " actors: " << std::endl;
        printActors( (*it).second->actors );
    }
    
    
}

void CMap::printActors( std::vector<CActor *> toPrint)
{
    if( toPrint.empty() )
    {
        std::cerr << "    no Actors." << std::endl;
        return;
    }

    for (auto actorIt = toPrint.begin(); actorIt != toPrint.end(); actorIt++ )
    {
        std::cerr << "    type is: " << (*actorIt)->type << " coords are: " << (*actorIt)->xPos <<
        " " << (*actorIt)->yPos << std::endl;
    }
}