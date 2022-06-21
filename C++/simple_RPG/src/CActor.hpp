#pragma once

#include <utility>
#include <iostream>

class CActor
{
protected:
    bool interactive;

public:
    char axis;
    int health;
    int movementSpeed;
    int attackDamage;
    int xPos;
    int yPos;
    char type;
    int direction;    
    bool deleteMe;

    virtual ~CActor() = 0;

    /**
     * @brief called when the actor collides with something, used for changing internal variables, such as projectiles self destructing or slimes occasionally changing directions 
     */
    virtual void attack() = 0;

    /**
     * @brief handles all movement of the actor, including boundary checking, movement speed, ai, input handling etc
     * 
     * @param xSize current max xSize of the room the actor is in
     * @param ySize current max ySize of the room the actor is in
     * @param input input from keyboard, used only for the player
     * @param tick current game tick, used for movement speed of enemies
     * @param player pointer to the player
     * @return std::pair<int,int> coordinates <X, Y> to which the actor moved
     */
    virtual std::pair<int,int> move(const int & xSize, const int & ySize, const int & input, const int & tick, CActor * player ) = 0;

    /**
     * @brief decreases the actors health by int given and sets deleteMe to true if it reaches 0 or less
     * 
     * @param toTake amount to decrease by
     */
    void takeDamage( const int & toTake);
    

};