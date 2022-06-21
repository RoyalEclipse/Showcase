#include "CActor.hpp"

CActor::~CActor(){}

void CActor::takeDamage( const int & toTake )
{
    health -= toTake;
    if( health <= 0 ) deleteMe = true;
}