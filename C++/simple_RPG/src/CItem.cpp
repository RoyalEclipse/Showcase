#include "CItem.hpp"

CItem::CItem( int hpChange, int dmgChange, int spdChange, std::string name, std::string description )
{
    healthChange = hpChange;
    damageChange = dmgChange;
    speedChange = spdChange;
    itemName = name;
    itemDescription = description;
}