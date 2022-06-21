#include "CGame.hpp"

CGame::~CGame()
{
    delete curMap;
    if( player != nullptr )
        delete player;
}

CGame::CGame()
{
    player = nullptr;
    curMap = nullptr;
}

int CGame::startGame()
{
    gameState = menu.mainScreen();
    
    curMap = new CMap;

    if( gameState == 2 )
    {
        endwin();
        return 0;
    }
    else if( gameState == 1 )
    {
        if ( loadGame( true ) )
        {
            endwin();
            std::cout << "ERROR: no custom.save file found or not accessible" << std::endl;
            return 1;
        }
    }   
    else
    {
        menu.newGameScreen();
        if ( loadGame( false ) )
        {
            endwin();
            std::cout << "ERROR: no template.save file found or not accessible" << std::endl;
            return 1;
        }

    }

    int yMax;
    int xMax;
    delwin( menu.curWin );
    refresh();

    getmaxyx(stdscr, yMax, xMax);
    WINDOW * gameWin = newwin(yMax, xMax, 0, 0 );
    // curMap->renderRoom( gameWin, curMap->rooms.at( curMap->playerPosInMap ) );
    (curMap->rooms.at( curMap->playerPosInMap ) )->actors.emplace_back( player );
    wtimeout(gameWin, 0);
    cbreak();

    int input = 0;
    bool roomChanged = true;
    std::pair<int,int> toAdd;

    // FPS setup
    int msPerFrame = 1000/30; // ms per frame, number after '1000/' is the desired framerate
    auto frameTime = std::chrono::steady_clock::now();
    // WARNING all game logic is tied to frames, increasing them from 30 speeds up the game accordingly

    int gameTicks = 0;

    ////////////////////////////////// main game loop///////////////////////////////////////////////////
    while ( true )
    {
        frameTime += std::chrono::milliseconds( msPerFrame );

        // counts to, used for changing movement speed of enemies
        modulateTicks( gameTicks );

        // get ONE char and flush buffer
        input = wgetch(gameWin);
        flushinp();

        if( input == 'q' )
        { 
            auto pauseStartTime = std::chrono::steady_clock::now();    
            handlePause(gameWin );
            roomChanged = true;
            auto pauseEndTime = std::chrono::steady_clock::now();
            frameTime += pauseEndTime - pauseStartTime;
        }

        // update the logic and screen
        player->canLeave=curMap->rooms.at( curMap->playerPosInMap )->openDoors;                 // if doors are open player can move out of bounds
        toAdd = curMap->changeRoom( player, curMap->rooms.at( curMap->playerPosInMap ) );       // changes the room if player is out of bounds
        
        if( toAdd != std::make_pair( 0, 0 ))                                                    // changes map coords
        {
            curMap->playerPosInMap.first += toAdd.first;
            curMap->playerPosInMap.second += toAdd.second;
            curMap->repositionPlayer( player, curMap->rooms.at( curMap->playerPosInMap ) );
            if( !checkForPlayer( curMap->rooms.at( curMap->playerPosInMap ) ) ){ (curMap->rooms.at( curMap->playerPosInMap ) )->actors.emplace_back( player ); }
            roomChanged = true;
        }

        if( roomChanged ){ curMap->renderRoom( gameWin, curMap->rooms.at( curMap->playerPosInMap ) ); roomChanged=false; } // completely re-renders the room, resizes window etc
        
        (*curMap).updateActors( gameWin, curMap->rooms.at( curMap->playerPosInMap ), input, player, gameTicks );// re-renders room without changes to window

        // if player is dead end the game
        if( player->deleteMe == true ){ break; }

        std::this_thread::sleep_until( frameTime );
    }
    ////////////////////////////////////////////////////////////////////////////////////////////////

    // ncurses cleanup
    delwin( gameWin );
    endwin();
    
    return 0;
}

int CGame::modulateTicks( int & gameTick )
{
    gameTick++;
    gameTick = gameTick % 10;

    return gameTick;
}

bool CGame::checkForPlayer( CRoom * toCheck )
{
    for( auto i = toCheck->actors.begin(); i != toCheck->actors.end(); i++ )
    {
        if( (*i)->type == 'P' ) return true;
    }
    return false;
}

int CGame::loadGame( bool useDefault )
{
    std::string curLine;
    std::ifstream saveFile;

    if( useDefault == false )
    {
        saveFile.open("src/default.save");
    }
    else
    {
        saveFile.open("src/custom.save");
    }

    if( ! saveFile.is_open() ) return 1;
    if( saveFile.fail() ) return 1;

    while( saveFile.good() )
    {
        getline(saveFile, curLine);

        if( curLine.empty() ) continue;

        auto curLineIt = curLine.begin();
        if( *curLineIt == '#' )
            continue;
        else if( *curLineIt == '0' )
            parseRoom( curLine );
        else
            parseActor( curLine );
    }

    return 0;
}

void CGame::handlePause( WINDOW * gameWin)
{
    int pauseReturn = menu.pauseScreen(gameWin);

    switch (pauseReturn)
    {
    case 0:
        player->openInvScreen(gameWin);
        break;
    case 1:
        saveGame();
        break;
    case 2:
        player->deleteMe = true;
    default:
        break;
    }

}

bool CGame::saveGame()
{
    std::stringstream curLine;
    std::ofstream saveFile;
    saveFile.open("src/custom.save");
    if( ! saveFile.is_open() ) return 1;
    if( saveFile.fail() ) return 1;

    // rooms
    for( auto i = curMap->rooms.begin(); i != curMap->rooms.end(); i++ )
    {
        curLine.str("");

        curLine << "0 " << i->first.first << " " << i->first.second << " "
        << i->second->xSize << " " << i->second->ySize << " "
        << i->second->upDoor << " " << i->second->downDoor << " "
        << i->second->leftDoor << " " << i->second->rightDoor << " " << (i->second->itemSpawned) << std::endl;

        saveFile << curLine.rdbuf();

        // actors
        for( auto j = i->second->actors.begin(); j !=i->second->actors.end(); j++ )
        {
            curLine.str("");

            switch ( (*j)->type )
            {
            case 'O':
                curLine << "1 " << (*j)->xPos << " " << (*j)->yPos << " " 
                << (*j)->health << " " << (*j)->attackDamage << " " << (*j)->movementSpeed;
                if( (*j)->axis == 'x')
                    curLine << " 1" << std::endl;
                else
                    curLine << " 0" << std::endl;
                break;
            case 'Z':
                curLine << "2 " << (*j)->xPos << " " << (*j)->yPos << " " 
                << (*j)->health << " " << (*j)->attackDamage << " " << (*j)->movementSpeed << std::endl;
                break;
            case '#':
                curLine << "3 " << (*j)->xPos << " " << (*j)->yPos << " " << std::endl; 
                break;
            case '?':
                curLine << "6 " << (*j)->xPos << " " << (*j)->yPos << " " << std::endl;
                break;
            default:
                continue;
            }
            saveFile << curLine.rdbuf();
        }
        
    }

    curLine.str("");

    // player stats
    curLine << "5 " << player->health << " " << player->attackDamage << " " << player->movementSpeed << " "
    << curMap->playerPosInMap.first << " " << curMap->playerPosInMap.second << " " << player->xPos << " " << player->yPos
    << std::endl;
    saveFile << curLine.rdbuf();

    // player inventory
    for( auto it = player->inventory.begin(); it != player->inventory.end(); it++)
    {
        curLine.str("");
        curLine << "4 " << (*it)->itemName << "|" << (*it)->itemDescription << std::endl;
        saveFile << curLine.rdbuf();
    }

    return 0;
}

int CGame::parseRoom( std::string & toParse )
{
    int found = 0;
    std::string temp;
    temp.clear();
    std::stringstream ss;
    ss << toParse;
    std::vector<int> foundNums;

    while( ! ss.eof() )
    {
        ss >> temp;
        if ( std::stringstream(temp) >> found )
            foundNums.emplace_back( found );
    }

    auto foundIt = foundNums.begin();
    foundIt++;

    int onMapX = 0;
    int onMapY = 0;
    int roomX = 0;
    int roomY = 0;
    bool up = 0;
    bool down = 0;
    bool left = 0;
    bool right = 0;
    bool noItem = 0;

    onMapX = *foundIt;
    foundIt++;
    onMapY = *foundIt;
    foundIt++;
    roomX = *foundIt;
    foundIt++;
    roomY = *foundIt;
    foundIt++;
    up = *foundIt;
    foundIt++;
    down = *foundIt;
    foundIt++;
    left = *foundIt;
    foundIt++;
    right = *foundIt;
    foundIt++;
    noItem = *foundIt;

    CRoom * toSave = new CRoom(roomX, roomY, up, down, left, right, noItem);

    std::pair<int,int> coords = { onMapX, onMapY };
    curMap->rooms[coords] = toSave;
    lastRoom = coords;
    
    return 0;
}

int CGame::parseActor( std::string & toParse )
{
    int found;
    std::string temp;
    std::stringstream ss;
    ss << toParse;
    std::vector<int> foundNums;

    while( ! ss.eof() )
    {
        ss >> temp;
        if ( std::stringstream(temp) >> found )
            foundNums.emplace_back( found );
    }

    auto foundIt = foundNums.begin();
    int type = *foundIt;
    foundIt++;

    int inRoomX;
    int inRoomY;
    int HP;
    int DMG;
    int SPD;
    int mapX = 0;
    int mapY = 0;
    bool axisIsX = 0;
    std::string desc;
    std::string name;

    if( type == 5 )
    {
        parseAttributes(HP, DMG, SPD, foundIt);
        mapX = *foundIt;
        foundIt++;
        mapY = *foundIt;
        foundIt++;
        inRoomX = *foundIt;
        foundIt++;
        inRoomY = *foundIt;
    }
    else if( type == 1 || type == 2 || type == 3 || type == 6 )
    {
        parseCoords(inRoomX, inRoomY, foundIt);
        if( type == 1 || type == 2 )
            parseAttributes(HP, DMG, SPD, foundIt);
        if( type == 1 ) 
            axisIsX = *foundIt;
    }
    else
    {
        parseItem( name, desc, HP, DMG, SPD, toParse );
    }
    
    CActor * toSave = nullptr;
    CItem * itemToSave = nullptr;
    switch (type)
    {
    case 1:
        toSave = new CActorEnemySlime(inRoomX, inRoomY, HP, DMG, SPD, axisIsX);
        delete itemToSave;
        break;
    case 2:
        toSave = new CActorEnemyZombie(inRoomX, inRoomY, HP, DMG, SPD);
        delete itemToSave;
        break;
    case 3:
        toSave = new CActorObstacle( inRoomX, inRoomY );
        delete itemToSave;
        break;
    case 4:
        itemToSave = new CItem(HP, DMG, SPD, name, desc);
        player->inventory.emplace_back(itemToSave);
        delete toSave;
        return 0;
        break;
    case 5:
        player = new CActorPlayerInventory( HP, DMG, SPD );
        player->xPos = inRoomX;
        player->yPos = inRoomY;
        curMap->playerPosInMap.first = mapX;
        curMap->playerPosInMap.second = mapY;
        delete toSave;
        delete itemToSave;
        return 0;
        break;
    case 6:
        toSave = new CActorItem( inRoomX, inRoomY );
        delete itemToSave;
    default:
        break;
    }

    curMap->rooms.at(lastRoom)->actors.emplace_back(toSave);

    return 0;
}

int CGame::parseItem( std::string & name, std::string & desc, int & HP, int & DMG, int & SPD, std::string toParse )
{
    auto it = toParse.begin();
    
    while ( (*it) != '|' )
    {
        if( (*it) != '4' )
        name += ( (*it) );
        it++;
    }
    
    it++;
    
    while( it != toParse.end() )
    {
        desc += ( (*it) );
        it++;
    }

    std::stringstream ss;
    int temp;

    ss << desc;

    ss >> temp;
    HP = temp;
    ss >> temp;
    DMG = temp;
    ss >> temp;
    SPD = temp;

    return 0;
}

int CGame::parseCoords( int &X, int &Y, std::vector<int>::iterator & foundIt )
{
    X = *foundIt;
    foundIt++;
    Y = *foundIt;
    foundIt++;
    return 0;
}

int CGame::parseAttributes(int &HP, int &DMG, int &SPD, std::vector<int>::iterator & foundIt)
{
    HP = *foundIt;
    foundIt++;
    DMG = *foundIt;
    foundIt++;
    SPD = *foundIt;
    foundIt++;
    return 0;
}