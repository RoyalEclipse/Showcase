#pragma once

#include "CActor.hpp"

class CActorEnemyZombie : public CActor
{
    private:

    public:
    CActorEnemyZombie(int X, int Y, int HP,int DMG,int SPD);
    virtual ~CActorEnemyZombie();

    /**
    * @brief handles all movement of the actor, including boundary checking, movement speed, ai, input handling etc
    * in this case contains extremely simple ai which may also move diagonally
    * @param xSize current max xSize of the room the actor is in
    * @param ySize current max ySize of the room the actor is in
    * @param input input from keyboard, used only for the player
    * @param tick current game tick, used for movement speed of enemies
    * @param player pointer to the player
    * @return std::pair<int,int> coordinates <X, Y> to which the actor moved
    */
    std::pair<int,int> move(const int & xSize, const int & ySize, const int & input, const int & tick, CActor * player ) override;
    void attack() override;

};