#ifndef __PROGTEST__
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cctype>
#include <climits>
#include <cassert>
#include <cstdint>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>
#include <algorithm>
#include <set>
#include <queue>
#include <memory>
#include <functional>
#include <stdexcept>
using namespace std;
#endif /* __PROGTEST__ */

// did huffman huff glue? Why does god punish me so

// struct used for tree generation
typedef struct node
{
  struct node * zero = NULL;
  struct node * one = NULL;
  char letter = NULL;
};

// creates the tree through recursion
bool createTreeRec( ifstream& myFile, node current, bool& curBit, char& curLetter )
{
  // bools for error checking
  bool left = false;
  bool right = false;

  myFile >> curBit;

  // if 0 creates two new nodes and initiates a new round of recursion, starting with left aka zero
  if( curBit == false)
  {
    current.zero = new node;
    current.one = new node;
    
    left = createTree( myFile, current.zero, curBit, curLetter, isFinished);
    right = createTree( myFile, current.one, curBit, curLetter, isFinished);

    // ends the instance, returns false if an error is encountered
    if ( left == true && right == true ) return true;
    else return false;
  }
  // if 1 sets the value of current node to a letter and ends the instance
  else if ( curBit == true )
  {
    myFile >> curLetter;
    current.letter = curLetter;

    return true;
  }

  return 0;
}

bool generateText( ifstream myFile, node * root, ofstream outputFile)

bool decompressFile ( const char * inFileName, const char * outFileName )
{
  bool curBit;
  char curLetter;
  node * root = new knot();
  node * current = root;

  // opens a file as binary
  ifstream myFile( inFileName, ios::binary | ios::in );
  if ( myFile . fail () ) return false;

  // calls a function to create a decoding tree
  if ( createTreeRec( myFile, current, curBit, curLetter) == false )
  return false;

  generateText( myFile, root )



  return false;
}

bool compressFile ( const char * inFileName, const char * outFileName )
{
  // keep this dummy implementation (no bonus) or implement the compression (bonus)
  return false;
}
#ifndef __PROGTEST__
bool identicalFiles ( const char * fileName1, const char * fileName2 )
{
  // todo
  return false;
}

int main ( void )
{
  assert ( decompressFile ( "tests/test0.huf", "tempfile" ) );
  assert ( identicalFiles ( "tests/test0.orig", "tempfile" ) );

  assert ( decompressFile ( "tests/test1.huf", "tempfile" ) );
  assert ( identicalFiles ( "tests/test1.orig", "tempfile" ) );

  assert ( decompressFile ( "tests/test2.huf", "tempfile" ) );
  assert ( identicalFiles ( "tests/test2.orig", "tempfile" ) );

  assert ( decompressFile ( "tests/test3.huf", "tempfile" ) );
  assert ( identicalFiles ( "tests/test3.orig", "tempfile" ) );

  assert ( decompressFile ( "tests/test4.huf", "tempfile" ) );
  assert ( identicalFiles ( "tests/test4.orig", "tempfile" ) );

  assert ( ! decompressFile ( "tests/test5.huf", "tempfile" ) );


  assert ( decompressFile ( "tests/extra0.huf", "tempfile" ) );
  assert ( identicalFiles ( "tests/extra0.orig", "tempfile" ) );

  assert ( decompressFile ( "tests/extra1.huf", "tempfile" ) );
  assert ( identicalFiles ( "tests/extra1.orig", "tempfile" ) );

  assert ( decompressFile ( "tests/extra2.huf", "tempfile" ) );
  assert ( identicalFiles ( "tests/extra2.orig", "tempfile" ) );

  assert ( decompressFile ( "tests/extra3.huf", "tempfile" ) );
  assert ( identicalFiles ( "tests/extra3.orig", "tempfile" ) );

  assert ( decompressFile ( "tests/extra4.huf", "tempfile" ) );
  assert ( identicalFiles ( "tests/extra4.orig", "tempfile" ) );

  assert ( decompressFile ( "tests/extra5.huf", "tempfile" ) );
  assert ( identicalFiles ( "tests/extra5.orig", "tempfile" ) );

  assert ( decompressFile ( "tests/extra6.huf", "tempfile" ) );
  assert ( identicalFiles ( "tests/extra6.orig", "tempfile" ) );

  assert ( decompressFile ( "tests/extra7.huf", "tempfile" ) );
  assert ( identicalFiles ( "tests/extra7.orig", "tempfile" ) );

  assert ( decompressFile ( "tests/extra8.huf", "tempfile" ) );
  assert ( identicalFiles ( "tests/extra8.orig", "tempfile" ) );

  assert ( decompressFile ( "tests/extra9.huf", "tempfile" ) );
  assert ( identicalFiles ( "tests/extra9.orig", "tempfile" ) );

  return 0;
}
#endif /* __PROGTEST__ */
