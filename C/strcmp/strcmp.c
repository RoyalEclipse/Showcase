#ifndef __PROGTEST__
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>
#endif /* __PROGTEST__ */

typedef struct input{
  char word[10000];
}input;

int sameWords ( const char * a, const char * b )
{

  // allocates and initializes strA and strB containing given const char a or b respectively
  size_t lengthA = strlen(a);
  size_t lengthB = strlen(b);
  char * strA = (char *) calloc(lengthA+1, sizeof(char));
  char * strB = (char *) calloc(lengthB+1, sizeof(char));
  strcpy(strA, a);
  strcpy(strB, b);

  // used for comparisons
  int intLengthA = lengthA;
  int intLengthB = lengthB;
  // changes all letters to uppercase in strA and strB
  int l = 0;
  char hold = 0;
  while(l != intLengthA){
    hold = strA[l];
    hold = toupper(hold);
    strA[l] = hold;
    l++;
  }

  l = 0;

  while(l != intLengthB){
    hold = strB[l];
    hold = toupper(hold);
    strB[l] = hold;
    l++;
  }

  // used for reallocation
  size_t wordAmountA = 10;
  size_t wordAmountB = 10;

  // allocates and initializes struct arrays which will contain parsed words
  input* wordsA = (input*) calloc(wordAmountA, sizeof(input));
  input* wordsB = (input*) calloc(wordAmountB, sizeof(input));

  // variables needed for parsing
  int index = 0;            // pos in the given const char array
  int j = 0;                // pos in char array "word" in struct array "wordsA"
  int k = 0;                // pos in struct array "wordsA"
  int totalWordsA = 0;      // used for final comparison, is later set to value of int k
  int temp = wordAmountA;   // used for comparison, wordAmountA is originally size_t
  int flag = 1;             // used to not add 1 to k in case of multiple spaces between words
  
  // saves letters as separate words from strA to struct array wordsA 
  //printf("intlengthA is: %d\n", intLengthA);
  while( index != intLengthA ){

    temp = wordAmountA;                       // dynamic reallocation when needed
    if(k == temp-1){
      wordAmountA += 10;
      temp = wordAmountA;
      wordsA = (input *) realloc(wordsA, wordAmountA * sizeof(input));
      for(int init = temp-11; init<temp; init++){   //inicialization of added arrs
        for(int letter = 0; letter < 100; letter++){
          wordsA[init].word[letter] = 0;
        }
      }
    }

    if( isalpha(strA[index]) != 0 ){          // saves letter if isalpha does not return 0, changes to next pos in struct array if does
      wordsA[k].word[j] = strA[index];
      //printf("saved letter : %c to WordsA[%d].word[%d]\n", strA[index], k, j);
      index++;
      j++;
      flag = 0;

    }else{
      if (flag != 1 && index != intLengthA-1 && index != intLengthA-2){ k++; }
      //printf(" strA on index %d is %c raising k to %d\n",index, strA[index], k);}
      index++;
      j = 0;
      flag = 1;
    }
  }

  // resets variables needed to loop again for b
  ////printf("strA on index %d is %c \n", index, strA[index]);
  //if(isalpha(strA[index])==0) k--;            // correction of k in case last letter is non-alpha
  totalWordsA = k;
  k = 0;
  index = 0;
  j = 0;

  temp = wordAmountB;
  flag = 1;

  // loop for input b, exactly the same as the first one
  //printf("intlengthB is: %d\n", intLengthB);
  while( index != intLengthB ){

    temp = wordAmountB;                       // dynamic reallocation when needed
    if(k == temp-1){
      wordAmountB += 10;
      temp = wordAmountB;
      wordsB = (input *) realloc(wordsB, wordAmountB * sizeof(input));
      for(int init = temp-11; init<temp; init++){   //inicialization of added arrs
        for(int letter = 0; letter < 100; letter++){
          wordsB[init].word[letter] = 0;
        }
      }
    }

    if( isalpha(strB[index]) != 0 ){          // saves letter if isalpha does not return 0, changes to next pos in struct array if does
      wordsB[k].word[j] = strB[index];
      //printf("saved letter : %c to WordsB[%d].word[%d]\n", strB[index], k, j);
      index++;
      j++;
      flag = 0;

    }else{
      if (flag != 1 && index != intLengthB-1 && index != intLengthB-2){ k++; }
      //printf(" strB on index %d is %c raising k to %d\n",index, strB[index], k);}



      index++;
      j = 0;
      flag = 1;
    }
  }
  //if(isalpha(strB[index-1])==0) k--;            // correction of k in case last letter is non-alpha
  int totalWordsB = k;
  /////////////////////////////////////////////
  //printf("totalWordsA is: %d\n", totalWordsA);
  //printf("totalWordsB is: %d\n", totalWordsB);
 for(int haha = 0; haha!=totalWordsA+1; haha++){
    //printf("A: saved on pos %d is: %s\n",haha,wordsA[haha].word);
  }
  for(int haha = 0; haha!=totalWordsB+1; haha++){
    //printf("B: saved on pos %d is: %s\n",haha,wordsB[haha].word);
  }
  /////////////////////////////////////////////

  // comparison of words, wordsA with wordsB
  int result = 0;
  //printf("totalWords A is: %d totalWords B is: %d\n", totalWordsA, totalWordsB);
  for(int p = 0; p <= totalWordsA+1; p++){
    //printf("p is : %d\n",p);
    for(int v = 0; v <= totalWordsB+1; v++){
      //printf("v is: %d\n",v);
      //////////////////debugging dont forget to remove////////////////////
      //printf("first: %s second: %s\n", wordsA[p].word, wordsB[v].word);
      /////////////////////////////////////////////////////////////////////
      
      if(strcmp(wordsA[p].word, wordsB[v].word) == 0){
        result = 1;
        //printf ("result is: %d, breaking.\n", result);
        break;
      }else result = 0;
      //printf ("result is: %d\n", result);
    }

    if(result == 0){ break; 
      free(wordsA);
      free(wordsB);
      free(strA);
      free(strB);
      return result;
    }
  }
  //printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
  //comparison of words, wordsB with wordsA
  for(int p = 0; p <= totalWordsB; p++){

    for(int v = 0; v <= totalWordsA; v++){

      //////////////////debugging dont forget to remove////////////////////
      //printf("first: %s second: %s\n", wordsB[p].word, wordsA[v].word);
      /////////////////////////////////////////////////////////////////////
      if(strcmp(wordsB[p].word, wordsA[v].word) == 0){
        result = 1;
        //printf ("result is: %d, breaking.\n", result);
        break;
      }else result = 0;
        //printf ("result is: %d\n", result);

    }

  if(result == 0) break;
  }

/*TODO 
when there are more than two nonalpha chars at the end of input this thig fucks up
*/












free(wordsA);
free(wordsB);
free(strA);
free(strB);
return result;
}

#ifndef __PROGTEST__
int main ( int argc, char * argv [] )
{
  assert ( sameWords ("iSCnftyZQc3x0w23WUoRILsS0ZeDRcX85SCuGHxQtShXxFT4OYzy3wjCjJpeJfXpTg8xTVLgjeHQHhBpp9NFMnjhaUZnGRKrsqAbx0FI47ZuUcj8WST1Fhd1CQDzLQ5qQJuXCPhhceB9PtOjLNEsszua1SoIgxRIDRei6ykIdpReiknfqt1muEzugNDqBAVinoaqYH5I", "iSCnftyZQc3x0w23WUoRILsS0ZeDRcX85SCuGHxQtShXxFT4OYzy3wjCjJpeJfXpTg8xTVLgjeHQHhBpp9NFMnjhaUZnGRKrsqAbx0FI47ZuUcj8WST1Fhd1CQDzLQ5qQJuXCPhhceB9PtOjLNEsszua1SoIgxRIDRei6ykIdpReiknfqt1muEzugNDqBAVinoaqYH5I") == 1);
  assert ( sameWords ("a a a a a a a a a a a a a a a a a a a a a a a a a","a a a a a a a a a a a a a a a a a a a a a a a a a") == 1);
  assert ( sameWords ("one two three four five six seven eight nine ten eleven twelve thirteen", "one two three four five six seven eight nine ten eleven twelve thirteen") == 1);
  assert ( sameWords ("one two three", "one two three..") == 1);
  assert ( sameWords ( "Hello students.", "HELLO studEnts!" ) == 1 );
  assert ( sameWords ( " He said 'hello!'", "'Hello.' he   said." ) == 1 );
  assert ( sameWords ( "He said he would do it.", "IT said: 'He would do it.'" ) == 1 );
  assert ( sameWords ( "one two three", "one two five" ) == 0 );
  return 0;
}
#endif /* __PROGTEST__ */
