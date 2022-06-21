#pragma once

#include <string>

class CItem
{
    public:
        CItem( int hpChange, int dmgChange, int spdChange, std::string name, std::string description );
        std::string itemDescription;
        std::string itemName;
        int healthChange;
        int damageChange;
        int speedChange;
};