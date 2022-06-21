#ifndef __PROGTEST__
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cassert>
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <map>
#include <list>
#include <set>
#include <queue>
#include <stack>
#include <deque>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <memory>
using namespace std;
#endif /* __PROGTEST__ */

// stores date of expiry for use in map
class CDate
{
  public:

    CDate ( int y,int m,int d )
    {
        Cyear = y;
        Cmonth = m;
        Cday = d;
    }

    int Cyear;
    int Cmonth;
    int Cday;

    // comparing tied ints for ease of writing
    bool operator<(const CDate& toComp ) const
    {
        return ( tie(Cyear, Cmonth, Cday) < tie(toComp.Cyear, toComp.Cmonth, toComp.Cday) );
    }

    bool operator>( const CDate& toComp ) const
    {
        return ( tie(Cyear, Cmonth, Cday) > tie(toComp.Cyear, toComp.Cmonth, toComp.Cday) );
    }

    bool operator==( const CDate& toComp ) const
    {
        return ( tie(Cyear, Cmonth, Cday) == tie(toComp.Cyear, toComp.Cmonth, toComp.Cday) );
    }

};

class CSupermarket
{
  public:

    // stores a new product or increases count of existing
    CSupermarket& store ( const string& name, const CDate& expiryDate, const int& count )
    {
        // [] creates an element if it does not exist, first "if" thus takes care of creating an element when needed
        if( warehouse[name].count(expiryDate) == 0 )
        {
            warehouse[name].emplace(expiryDate, count);
        }
        else
        {
            warehouse[name].at(expiryDate) += count;
        }

    return *this;
    }

    // sells items from warehouse, what to sell defined in shopping list, modifies shopping list if order fulfilled
    CSupermarket& sell ( list<pair<string,int>>& shoppingList )
    {
    
    auto shoppingListIndex = shoppingList.begin();
    string searchedItem;
    string closestMatch;
    int toSell;

    // creates a set of unsellable names
    set<string> unsellable;
    while( shoppingListIndex != shoppingList.end() )
    {
        auto match = findItem( (*shoppingListIndex).first, closestMatch);
        if( match == warehouse.end() )
        {
            unsellable.insert(shoppingListIndex->first);
        }
        shoppingListIndex++;
    }

    shoppingListIndex = shoppingList.begin();

    // the actual selling process
    while( shoppingListIndex != shoppingList.end() )
    {
        // for ease of writing
        searchedItem = (*shoppingListIndex).first;
        toSell = (*shoppingListIndex).second;

        // if name is unsellable skip it
        if( unsellable.count(searchedItem) != 0 )
        {
            shoppingListIndex++;
            continue;
        }

        // findItem returns warehouse.end() if no match found!
        auto match = findItem(searchedItem, closestMatch);
        
        if( match != warehouse.end() )
        {
            int itemsSold = removeItems( closestMatch, toSell );

            shoppingListIndex->second = toSell - itemsSold;

            // remove item from shopping list if order fulfilled AND move on
            if(shoppingListIndex->second == 0)
            {
                auto copy = shoppingListIndex;
                shoppingListIndex++;
                shoppingList.erase(copy);
            }
            else shoppingListIndex++;
        }
        else
        {
            shoppingListIndex++;
        }

    }
    
    return *this;
    }

    // iterates through everything and saves expired stuff into a multimap sorted by amount
    list<pair<string,int>> expired( const CDate& date ) const
    {
        multimap<int, string, greater<int>> expiredProduce;

        for( auto i = warehouse.begin(); i != warehouse.end(); i++ )
        {
            int amountExpired = 0;

            auto k = (i->second).begin();
            for( ; k != (i->second).end(); k++ )
            {
                if( k->first < date )
                {
                    amountExpired += k->second;
                } 
            }

            if( amountExpired > 0 )
            {
                expiredProduce.emplace( amountExpired, i->first );
            }
        }

        list<pair<string,int>> expiredProduceList;
        pair<string,int> temp;

        // copy from the multimap into the list through temp pair
        for( auto i = expiredProduce.begin(); i != expiredProduce.end(); i++ )
        {
            temp.first = i->second;
            temp.second = i->first;
            expiredProduceList.emplace_back(temp);
        }

        return expiredProduceList;
    }

    // testing function
    void printlist( const list<pair<string,int>>& toPrint)
    {
        for( auto i = toPrint.begin(); i != toPrint.end(); i++)
        {
            cerr << i->first << " " << i->second << endl;
        }
        
    }

    // testing function
    void printWarehouse(void)
    {
        for( auto i = warehouse.begin(); i != warehouse.end(); i++)
        {
            cerr << i->first << endl;
            for( auto k = i->second.begin(); k != i->second.end(); k++ )
            {
                cerr << "    " << k->first.Cyear << "-" << k->first.Cmonth << "-" << k->first.Cday << " " << k->second << endl;
            }
        }
        cerr << "------" << endl;
    }
  private:

    // all praise Láďa and recordings from last year.
    unordered_map<string, map<CDate,int>> warehouse;

    // returns the length of a string
    int stringLength(const string& toCount)
    {
        int counter = 0;

        for(auto i = toCount.begin(); i != toCount.end(); i++) counter++;

        return counter;
    }

    // compares strings, allows one letter to be different, but len has to be the same
    bool strCmpPermissive(const string& first, const string& second)
    {
        if( stringLength(first) != stringLength(second) ) return false;

        // direct match
        if( first == second ) return true;
        else
        {
            int diffCounter = 0;
            auto firstIndex = first.begin();
            auto secondIndex = second.begin();

            // iterates through the string char by char, if too many differences, return false
            while(true)
            {
                if( firstIndex == first.end() || secondIndex == second.end() ) break;

                if( *firstIndex != *secondIndex ) diffCounter++;

                if( diffCounter > 1 ) return false;

                firstIndex++;
                secondIndex++;
            }
            return true;
        }
        return true;
    }

    // finds the item in warehouse or its closest match if only one exists, otherwise clears closest match and returns warehouse.end()
    unordered_map<string, map<CDate,int>>::iterator findItem( const string& nameToFind, string& closestMatch )
    {
        closestMatch.clear();

        // if there is a direct match just return the same
        if( warehouse.count(nameToFind) )
        {
            closestMatch = nameToFind;
            return warehouse.find(nameToFind);
        }
        else
        {
            // iterate through and search for similar matches
            for( auto i = warehouse.begin(); i != warehouse.end(); i++ )
            {
                if ( strCmpPermissive(nameToFind, i->first ) == true )
                {
                    // if one closest match already found clear and end, because there is no conclusive result
                    if( !closestMatch.empty() )
                    {
                        closestMatch.clear();
                        return warehouse.end();
                    }
                    else 
                    {
                        closestMatch = i->first;
                    }
                } 
            }
        }

    return warehouse.find(closestMatch);
    }

    // removes items from storage starting with oldest by expiry date
    int removeItems(const string& name, int& amount)
    {
        int amountSold = 0;

        while(amountSold != amount)
        {
            // in case there is not enough items;
            if( warehouse[name].empty() )
            {
                warehouse.erase( name );
                break;
            } 

            // oldest item in map
            auto itemIterator = warehouse[name].begin();

            // if not enough in stock with the same expiry date, delete element and "sell" items
            if( itemIterator->second <= amount - amountSold )
            {
                amountSold += itemIterator->second;
                warehouse[name].erase(itemIterator);
                 if( warehouse[name].empty() )
                {
                    warehouse.erase( name );
                    break;
                } 
            }
            else
            {
                itemIterator->second -= amount - amountSold;
                amountSold += amount - amountSold;
            }
        }

        return amountSold;
    }

};
#ifndef __PROGTEST__
int main ( void )
{
  CSupermarket s;
  s . store ( "bread", CDate ( 2016, 4, 30 ), 100 )
    . store ( "butter", CDate ( 2016, 5, 10 ), 10 )
    . store ( "beer", CDate ( 2016, 8, 10 ), 50 )
    . store ( "bread", CDate ( 2016, 4, 25 ), 100 )
    . store ( "okey", CDate ( 2016, 7, 18 ), 5 );

  list<pair<string,int> > l0 = s . expired ( CDate ( 2018, 4, 30 ) );
  assert ( l0 . size () == 4 );
  assert ( ( l0 == list<pair<string,int> > { { "bread", 200 }, { "beer", 50 }, { "butter", 10 }, { "okey", 5 } } ) );

  list<pair<string,int> > l1 { { "bread", 2 }, { "Coke", 5 }, { "butter", 20 } };
  s . sell ( l1 );
  assert ( l1 . size () == 2 );
  assert ( ( l1 == list<pair<string,int> > { { "Coke", 5 }, { "butter", 10 } } ) );

  list<pair<string,int> > l2 = s . expired ( CDate ( 2016, 4, 30 ) );
  assert ( l2 . size () == 1 );
  assert ( ( l2 == list<pair<string,int> > { { "bread", 98 } } ) );

  list<pair<string,int> > l3 = s . expired ( CDate ( 2016, 5, 20 ) );
  assert ( l3 . size () == 1 );
  assert ( ( l3 == list<pair<string,int> > { { "bread", 198 } } ) );

  list<pair<string,int> > l4 { { "bread", 105 } };
  s . sell ( l4 );
  assert ( l4 . size () == 0 );
  assert ( ( l4 == list<pair<string,int> > {  } ) );

  list<pair<string,int> > l5 = s . expired ( CDate ( 2017, 1, 1 ) );
  assert ( l5 . size () == 3 );
  assert ( ( l5 == list<pair<string,int> > { { "bread", 93 }, { "beer", 50 }, { "okey", 5 } } ) );

  s . store ( "Coke", CDate ( 2016, 12, 31 ), 10 );

  list<pair<string,int> > l6 { { "Cake", 1 }, { "Coke", 1 }, { "cake", 1 }, { "coke", 1 }, { "cuke", 1 }, { "Cokes", 1 } };
  s . sell ( l6 );
  assert ( l6 . size () == 3 );
  assert ( ( l6 == list<pair<string,int> > { { "cake", 1 }, { "cuke", 1 }, { "Cokes", 1 } } ) );

  list<pair<string,int> > l7 = s . expired ( CDate ( 2017, 1, 1 ) );
  assert ( l7 . size () == 4 );
  assert ( ( l7 == list<pair<string,int> > { { "bread", 93 }, { "beer", 50 }, { "Coke", 7 }, { "okey", 5 } } ) );

  s . store ( "cake", CDate ( 2016, 11, 1 ), 5 );

  list<pair<string,int> > l8 { { "Cake", 1 }, { "Coke", 1 }, { "cake", 1 }, { "coke", 1 }, { "cuke", 1 } };
  s . sell ( l8 );
  assert ( l8 . size () == 2 );
  assert ( ( l8 == list<pair<string,int> > { { "Cake", 1 }, { "coke", 1 } } ) );

  list<pair<string,int> > l9 = s . expired ( CDate ( 2017, 1, 1 ) );
  assert ( l9 . size () == 5 );
  assert ( ( l9 == list<pair<string,int> > { { "bread", 93 }, { "beer", 50 }, { "Coke", 6 }, { "okey", 5 }, { "cake", 3 } } ) );

  list<pair<string,int> > l10 { { "cake", 15 }, { "Cake", 2 } };
  s . sell ( l10 );
  assert ( l10 . size () == 2 );
  assert ( ( l10 == list<pair<string,int> > { { "cake", 12 }, { "Cake", 2 } } ) );

  list<pair<string,int> > l11 = s . expired ( CDate ( 2017, 1, 1 ) );
  assert ( l11 . size () == 4 );
  assert ( ( l11 == list<pair<string,int> > { { "bread", 93 }, { "beer", 50 }, { "Coke", 6 }, { "okey", 5 } } ) );

  list<pair<string,int> > l12 { { "Cake", 4 } };
  s . sell ( l12 );
  assert ( l12 . size () == 0 );
  assert ( ( l12 == list<pair<string,int> > {  } ) );

  list<pair<string,int> > l13 = s . expired ( CDate ( 2017, 1, 1 ) );
  assert ( l13 . size () == 4 );
  assert ( ( l13 == list<pair<string,int> > { { "bread", 93 }, { "beer", 50 }, { "okey", 5 }, { "Coke", 2 } } ) );

  list<pair<string,int> > l14 { { "Beer", 20 }, { "Coke", 1 }, { "bear", 25 }, { "beer", 10 } };
  s . sell ( l14 );
  assert ( l14 . size () == 1 );
  assert ( ( l14 == list<pair<string,int> > { { "beer", 5 } } ) );

  s . store ( "ccccb", CDate ( 2019, 3, 11 ), 100 )
    . store ( "ccccd", CDate ( 2019, 6, 9 ), 100 )
    . store ( "dcccc", CDate ( 2019, 2, 14 ), 100 );

  list<pair<string,int> > l15 { { "ccccc", 10 } };
  s . sell ( l15 );
  assert ( l15 . size () == 1 );
  assert ( ( l15 == list<pair<string,int> > { { "ccccc", 10 } } ) );

  return EXIT_SUCCESS;
}
#endif /* __PROGTEST__ */
