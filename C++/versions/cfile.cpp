#ifndef __PROGTEST__
#include <cassert>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <iostream>
using namespace std;
#endif /* __PROGTEST__ */

class CFile
{
  public:

    struct data
    {
      uint32_t fileCapacity;
      uint8_t * storage;
      int * refCounter;
      
      data()
      {
        fileCapacity = 0;
        storage = nullptr;
        refCounter = new int(1);
      }

      data( data& toCopy )
      {
        fileCapacity = toCopy.fileCapacity;
        storage = toCopy.storage;
        refCounter = toCopy.refCounter;
        *refCounter = *refCounter + 1;
      }

      ~data()
      {
        if( *refCounter <= 1 )deleter();
        else
          (*refCounter) = (*refCounter) - 1;
        // deleter();
      }

      void deleter()
      {
        *refCounter = *refCounter - 1;
        if( *refCounter <= 0 )
        {
          
          delete[] storage;
          delete refCounter;
        }
      }

      void deleter( CFile &toDelete)
      {
        (*toDelete.storedData.refCounter) = (*toDelete.storedData.refCounter) - 1;
        if( (*toDelete.storedData.refCounter) <= 0 )
        {
          delete[] toDelete.storedData.storage;
          delete toDelete.storedData.refCounter;
        }
      }

      data operator= (const data& toCopy)
      {
        if( &toCopy == this ) return *this;
        
        (*toCopy.refCounter)++;
        deleter();

        storage = toCopy.storage;
        refCounter = toCopy.refCounter;
        fileCapacity = toCopy.fileCapacity;
        return *this;
      }

      data deepCopy()
      {
        data temp;
        // delete[] temp.storage;
        temp.storage = new uint8_t[ fileCapacity ] ();

        uint32_t bytes = fileCapacity * sizeof(uint8_t);
        mempcpy(temp.storage, storage, bytes );
        temp.fileCapacity = fileCapacity;
        return temp;
      }

      void resizeStorage( uint32_t newSize )
      {
        if( storage == nullptr )
        {
          storage = new uint8_t [newSize] ();
          fileCapacity = newSize;
          return;
        }

        uint8_t * temp = new uint8_t [newSize] ();

        if( newSize > fileCapacity )
          memcpy(temp, storage, fileCapacity );
        else
          memcpy(temp, storage, newSize );
        
        // deleter();
        delete[] storage;
        storage = temp;
        fileCapacity = newSize;
      }

      uint8_t& get( uint32_t index )
      {
        return storage[index];
      }

      bool test()
      {
        
        resizeStorage(10);
        storage[2]='i';
        cerr << "fileCapacity is: " << fileCapacity << endl;
        cerr << "sizeof storage is: " << sizeof(storage) << endl;
        return 1;
      }

      void printStorage(uint32_t index)
      {
        cerr << "{";
        for(uint32_t i = index; i < fileCapacity; i++)
          cerr << unsigned( storage[i] ) << ", ";
        cerr << "}" << endl;
      }

      void printStorage()
      {
        cerr << "{";
        for(uint32_t i = 0; i < fileCapacity; i++)
          cerr << unsigned( storage[i] ) << ", ";
        cerr << "}" << endl;
      }

      

    };

    CFile( void )
    {
      index = 0;
      previous = nullptr;
    }

    ~CFile( void )
    {
      delete previous;
    }

    // copying constructor
    CFile( const CFile& toCopy )
    {
      storedData = toCopy.storedData;
      this->previous = nullptr;

      if( toCopy.previous != nullptr )
      {
        this->previous = new CFile( *toCopy.previous );
      }

      index = toCopy.index;
    }

    CFile operator= ( const CFile& toCopy )
    {
      if( &toCopy == this ) return *this;
      CFile *temp = previous;

      storedData = toCopy.storedData;
      index = toCopy.index;
      this->previous = nullptr;

      if( toCopy.previous != nullptr )
      {
        this->previous = new CFile( *toCopy.previous );
      }


      // storedData.deleter(*temp);  //THIS LEAKS LIKE YOUR MOTHER WHEN I VISIT
      delete temp;
      return *this;
    }

    // copy cons, dtor, op=
    bool seek( uint32_t offset )
    {
      if( storedData.fileCapacity < offset ) return 0;
      index = offset;
      return 1;
    }

    uint32_t read( uint8_t * dst, uint32_t bytes )
    {
      // storedData.printStorage(index);
      if( index + bytes > storedData.fileCapacity ) bytes = storedData.fileCapacity - index;
      memcpy(dst, &storedData.get(index), bytes );
      index += bytes;
      return bytes;
    }

    uint32_t write( const uint8_t * src, uint32_t bytes )
    {
      if( bytes == 0 ) return 0;
      if( *(storedData.refCounter) > 1 )
        storedData = storedData.deepCopy();

      if( index + bytes > storedData.fileCapacity )
        storedData.resizeStorage( index + bytes );


      // uint32_t srcIndex = 0;
      // for( uint32_t i = index; i < storedData.fileCapacity && srcIndex < bytes; i++)
      // {
      //   storedData.storage[i] = src[srcIndex];
      //   srcIndex++;
      // }

      memcpy(&storedData.storage[index], src, bytes);

      index += bytes;
      return bytes;
    }

    void truncate( void )
    {
      if(*(storedData.refCounter) > 1 )
      {
        storedData = storedData.deepCopy();
      } 
      storedData.resizeStorage(index);
    }

    //  getter for fileCapacity
    uint32_t fileSize( void ) const
    {
      return storedData.fileCapacity;
    }

    // adds current storage array and needed variables to the array of CFiles "versions" using copying constructor
    void addVersion( void )
    {
      CFile * temp = previous;
      previous = new CFile(*this);
      delete temp;
    }

    bool undoVersion ( void )
    {
      if( previous == nullptr ) return 0;
      *this = *previous;
      return 1;
    }
    

  data storedData;
  uint32_t index;
  private:

  CFile * previous;

};

#ifndef __PROGTEST__
bool writeTest( CFile& x, const initializer_list<uint8_t> & data, uint32_t wrLen )
{
  return x . write ( data . begin (), data . size () ) == wrLen;
}

bool readTest( CFile& x, const initializer_list<uint8_t> & data, uint32_t rdLen )
{
  uint8_t  tmp[100];
  uint32_t idx = 0;

  if ( x . read ( tmp, rdLen ) != data . size ())
    {
      return false;
    }
  for ( auto v : data )
  {
    if ( tmp[idx++] != v )
      return false;
  }
  return true;
}

int main ( void )
{
  CFile f0;
  
  assert ( writeTest ( f0, { 10, 20, 30 }, 3 ) );
  assert ( f0 . fileSize () == 3 );
  assert ( writeTest ( f0, { 60, 70, 80 }, 3 ) );
  assert ( f0 . fileSize () == 6 );
  assert ( f0 . seek ( 2 ));
  assert ( writeTest ( f0, { 5, 4 }, 2 ) );
  assert ( f0 . fileSize () == 6 );
  assert ( f0 . seek ( 1 ));
  assert ( readTest ( f0, { 20, 5, 4, 70, 80 }, 7 ));  
  assert ( f0 . seek ( 3 ));
  f0 . addVersion();
  assert ( f0 . seek ( 6 ));  
  assert ( writeTest ( f0, { 100, 101, 102, 103 }, 4 ) );  
  f0 . addVersion();
  assert ( f0 . seek ( 5 ));
  CFile f1 ( f0 );
  f0 . truncate ();
  assert ( f0 . seek ( 0 ));
  assert ( readTest ( f0, { 10, 20, 5, 4, 70 }, 20 ));
  assert ( f0 . undoVersion () );
  assert ( f0 . seek ( 0 ));
  assert ( readTest ( f0, { 10, 20, 5, 4, 70, 80, 100, 101, 102, 103 }, 20 ));
  assert ( f0 . undoVersion () );
  assert ( f0 . seek ( 0 ));
  assert ( readTest ( f0, { 10, 20, 5, 4, 70, 80 }, 20 ));
  assert ( !f0 . seek ( 100 ));
  assert ( writeTest ( f1, { 200, 210, 220 }, 3 ) );
  assert ( f1 . seek ( 0 ));
  assert ( readTest ( f1, { 10, 20, 5, 4, 70, 200, 210, 220, 102, 103 }, 20 ));
  assert ( f1 . undoVersion () );
  assert ( f1 . undoVersion () );
  assert ( readTest ( f1, { 4, 70, 80 }, 20 ));
  assert ( !f1 . undoVersion () );
  return EXIT_SUCCESS;
}
#endif /* __PROGTEST__ */
