#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

// performs all possible frees
void free_all(char *abbrev, char *input, char *phrase, int *found, char *phrase_uppered)
{
    free(phrase_uppered);
    free(phrase);
    free(found);
    free(input);
    free(abbrev);
    return;
}

// input check for abbreviation
int abbrev_check(char *abbrev, ssize_t *abbrev_nchar)
{
    if(*abbrev_nchar == 0)
    {
        free(abbrev);
        printf("Nespravny vstup.\n");
        return 1;
    }

    // checks for uppercase
    for(int i = 0; i < (int) *abbrev_nchar - 1; i++)
    {
        if(isupper(abbrev[i]) == 0)
        {
            free(abbrev);
            printf("Nespravny vstup.\n");
            return 1;
        }
    }

    return 0;
}

// reads one line from stdin with input checks
int get_input(char **input, char *abbrev, size_t *input_size, ssize_t *input_nchar, int *input_result)
{
    *input_nchar = getline(input, input_size, stdin);

    // check for eof and impossibly short input
    if((int) *input_nchar == -1)
    {
        return -1;
    }
    else if ((int) *input_nchar < 4)
    {
        printf("Nespravny vstup.\n");
        return 1;
    }

    // checks if command letter was properly inputted
    if(*input[0] != '?' && *input[0] != '#')
    {
        printf("Nespravny vstup.\n");
        return 1;
    }

    //////////////////////////////////////////////////////////////////////////
    // input check for quotation marks is located in function "parse_input" //
    //////////////////////////////////////////////////////////////////////////

    return 0;
}

// separates input into command letter, N and phrase
int parse_input(char *input, size_t *phrase_nchar, char *command, int *per_word, char *phrase, ssize_t *input_nchar, char *abbrev, char *phrase_uppered)
{
    int fields=0;
    fields = sscanf(input, "%c %d %[^\n]", command, per_word, phrase);

    // input check for missing fields
    if (fields < 3)
    {
        printf("Nespravny vstup.\n");
        return 1;
    }

    // finds out the number of chars in phrase
    int temp = 0;
    for(; phrase[temp]; temp++){}
    *phrase_nchar = temp;

    // input check for qotation marks and varios shenanigans
    int j = 1;
    for( ; j < (int) *phrase_nchar; j++)
    {
        if(phrase[j] == '"')
        break; 
    }
    if( isalpha(phrase[j+1]) || phrase[j+1] == '"') 
    {
        printf("Nespravny vstup.\n");
        return 1;
    }
    if (j == (int)*phrase_nchar)
    {
        printf("Nespravny vstup.\n");
        return 1;
    }
    for(int h = j+1 ; h < (int) *phrase_nchar; h++)
    {
        phrase[h] = 0;
    }

    if((phrase[0]) != '"')
    {
        printf("Nespravny vstup.\n");
        return 1;
    }

    //input check for N
    if(*per_word < 1)
    {
        printf("Nespravny vstup.\n");
        return 1;
    }

    // copies the function in uppercase and transforms the original into lowercase
    char hold;
    for(int i = 0; i < (int)*phrase_nchar; i++) 
    {   
        hold = phrase[i];
        hold = toupper(hold);
        phrase_uppered[i] = hold;
    }

    for(int i = 0; i < (int)*phrase_nchar; i++) 
    {   
        hold = phrase[i];
        hold = tolower(hold);
        phrase[i] = hold;
    }

    return 0;
}

// touppers the characters in "phrase" on position saved in "found", prints it, then resets the phrase to the original state
void print_found(int *found, char *phrase)
{
    char hold;
    for(int i = 0; found[i]; i++)
    {
        hold = phrase[(found[i])];
        hold = toupper(hold);
        phrase[(found[i])] = hold;
    }

    puts(phrase);

    for(int i = 0; found[i]; i++)
    {
        hold = phrase[(found[i])];
        hold = tolower(hold);
        phrase[(found[i])] = hold;
    }
    return;
}

// clears "found" array from position given in abbrev_pos until end of array
void clear_found(int *found, ssize_t *abbrev_nchar, int *abbrev_pos)
{
    for(int i = *abbrev_pos; i < (int) *abbrev_nchar; i++)
    {
        found[i] = 0;
    }

    return;
}

// moves phrase_pos to the next space in phrase and resets in_word_counter
int skip_to_next_word(char *phrase, int *phrase_pos, int *in_word_counter)
{
    *in_word_counter = 0;
    while(isalpha(phrase[*phrase_pos])) 
    { 
        if( phrase[*phrase_pos + 1] == '"' ) 
        {
            return 1;
        }
        *phrase_pos += 1; 
    }

    return 0;;
}

// recursive function, finds all possible abbreviations after letter and pos given by find_abbrevs
int locator_rec(int *found, int *per_word, char *phrase_uppered, ssize_t *abbrev_nchar, size_t *phrase_nchar, char *abbrev, int *abbrev_pos, int *phrase_pos, int *counter, char *phrase, int *in_word_counter, char *command)
{
    *abbrev_pos += 1;
    if (*abbrev_pos >= (int)*abbrev_nchar)
    {
        return 0;
    }

    // variables containing: abbrev_pos, phrase_pos, in_word_counter and a flag, used to reset current iteration to original state, after recursion.
    int temp = *abbrev_pos;
    int hold = 0;
    int in_word_reset = 0;
    int check = 0;

    do
    {
        in_word_reset = *in_word_counter;
        *phrase_pos += 1;

        // resets in_word_counter if the function passes through a space
        if(phrase_uppered[*phrase_pos] == ' ')
        { 
            *in_word_counter = 0;
        }

        // saves letter position to "found" if it matches the the letter in "abbrev" and either prints the result or launches another iteration
        if ( abbrev[*abbrev_pos] == phrase_uppered[*phrase_pos] )
        {
            found[*abbrev_pos] = *phrase_pos;
            hold = *phrase_pos;
            *in_word_counter += 1;

            // printing of the result
            if( (found[*abbrev_nchar - 1] != 0) && (command[0] == '?'))
            {
                print_found(found, phrase); 
                clear_found(found,abbrev_nchar,abbrev_pos); 
                *counter += 1;
            }
            else if((found[*abbrev_nchar - 1] != 0) && (command[0] == '#'))
            {
                clear_found(found,abbrev_nchar,abbrev_pos); 
                *counter += 1;
            }

            // skipping to next word for the next iteration
            if( *in_word_counter == *per_word && (int) *abbrev_nchar > *per_word)
            { 
                check = skip_to_next_word(phrase, phrase_pos, in_word_counter);
            }

            // launching of next iteration
            if( check != 1)
            {
                locator_rec(found, per_word, phrase_uppered, abbrev_nchar, phrase_nchar, abbrev, abbrev_pos, phrase_pos, counter, phrase, in_word_counter, command);
            }

            // The aforementioned resetting of variables after recursion.
            *abbrev_pos = temp;
            *phrase_pos = hold;
            clear_found(found, abbrev_nchar, abbrev_pos);
            *in_word_counter = in_word_reset;

        }

    }while(*phrase_pos <=(int) *phrase_nchar-1);

    return 0;
}

// finds the position(s) of the first letter in "abbrev"
int find_abbrevs(int *found, int *per_word, char *phrase_uppered, ssize_t *abbrev_nchar, size_t *phrase_nchar, char *abbrev, char *phrase, char *command)
{

    int abbrev_pos = 0;             // position in array "abbrev"
    int phrase_pos = 0;             // position in array "phrase"
    int counter = 0;                // number of found results
    int temp = 0;                   // saves "phrase_pos" between iterations of "locator_rec"
    int in_word_counter = 0;        // number of found letters in current word
    
    do
    {
        in_word_counter = 0;

        if( abbrev[0] == phrase_uppered[phrase_pos] )
        {
            in_word_counter = 1;
            found[0] = phrase_pos;

            // prints results or saves number of found letters in case "abbrev" is only one char long
            if( (int) *abbrev_nchar == 1 && command[0] == '#')
            {
                counter += 1;
            }
            else if( (int) *abbrev_nchar == 1 )
            {
                print_found(found, phrase);
                clear_found(found, abbrev_nchar, &abbrev_pos);
                counter += 1;
            }

            temp = phrase_pos;

            // skips to next word if necessary
            if( in_word_counter == *per_word && (int) *abbrev_nchar > *per_word)
            {
                skip_to_next_word(phrase, &phrase_pos, &in_word_counter);
            }

            locator_rec(found, per_word, phrase_uppered, abbrev_nchar, phrase_nchar, abbrev, &abbrev_pos, &phrase_pos, &counter, phrase, &in_word_counter, command);

            // resetting of variables after "locator_rec"
            abbrev_pos = 0;
            clear_found(found, abbrev_nchar, &abbrev_pos);
            phrase_pos = temp;
        }

        phrase_pos++;

    }while(phrase_pos < (int) *phrase_nchar - 1);
    
    abbrev_pos = 0;
    clear_found(found,abbrev_nchar, &abbrev_pos);

    // prints the number of found combinations, depending on "command"
    if( command[0] == '?')
    printf("> %d\n",counter);
    else
    printf("> limit %d: %d\n",*per_word, counter);

    // printf("find_abbrevs: done, returning 0\n");
    return 0;
}

// launches "find_abbrevs" with increasing N
int list_combs(int *found, int *per_word, char *phrase_uppered, ssize_t *abbrev_nchar, size_t *phrase_nchar, char *abbrev, char *phrase, char *command)
{
    int i = 1;
    if((int)*abbrev_nchar <= (int)*phrase_nchar)
    {
        for( ; i <= *per_word; i++)
        {
            find_abbrevs(found, &i, phrase_uppered, abbrev_nchar, phrase_nchar, abbrev, phrase, command);
        }
    }
    // timesave in case the abbreviation is longer than the phrase
    else 
    {
        for( ; i <= *per_word; i++)
        {
            printf("> limit %d: 0\n",i);
        }
    }
    return 0;
}

int main(void)
{
    // abbreviation variables
    char *abbrev = NULL;
    size_t abbrev_size = 0;
    ssize_t abbrev_nchar = 0;
    
    // raw input variables
    char *input = NULL;
    size_t input_size = 0;
    ssize_t input_nchar = 0;
    int input_result = 0;

    // parsed input variables
    char *phrase = NULL;
    char *phrase_uppered = NULL;
    size_t phrase_nchar = 0;
    char command = 'a';
    int per_word = 0;

    // input of abbreviation with elementary input checks
    printf("Zkratka:\n");
    abbrev_nchar = getline(&abbrev, &abbrev_size, stdin);

    if( abbrev[0] == '\n' || abbrev_nchar == -1)
    {
        free(abbrev);
        printf("Nespravny vstup.\n");
        return 1;
    }
    abbrev[abbrev_nchar - 1] = 0;
    if(abbrev_check(abbrev, &abbrev_nchar) == 1)
    {
        return 1;
    }
    // allocation of int array "found", which will contain positions in "phrase" where the matching letters are
    int *found =(int *) calloc(abbrev_nchar, sizeof(int));
    abbrev_nchar--;

    // input of commands
    printf("Problemy:\n");

    // repeatedly launches all necessary functions to process input and performs neccesary frees in the end
    while(input_result < 1)
    {
        input_result = get_input(&input, abbrev, &input_size, &input_nchar, &input_result);
        if (input_result == -1)
        {
            free_all(abbrev, input, phrase, found, phrase_uppered);
            return 0;
        }
        else if( input_result == 1)
        { 
            free(abbrev);
            free(input);
            free(found);
            return 1;
        }
        else if(input_result == 0)
        {
            // reallocs and clears "phrase" and "phrase_uppered" after each iteration
            phrase = (char *) realloc(phrase, input_nchar);
            for(int i = 0; i<0; i++)
            {
                phrase[i] = 0; 
            }

            phrase_uppered = (char *) realloc(phrase_uppered, input_nchar);
            for(int i = 0; i<input_nchar; i++)
            {
                phrase_uppered[i]=0;
            }

            input_result = parse_input(input, &phrase_nchar, &command, &per_word, phrase, &input_nchar, abbrev, phrase_uppered);
        }

        if(input_result == 1)
        {
            free_all(abbrev, input, phrase, found, phrase_uppered);
            return 0;
        }

        if (input_result < 1)
        {   
            if((int)abbrev_nchar > (int)phrase_nchar && command == '?') printf("> 0\n");
            else if( command == '?')
            find_abbrevs(found, &per_word, phrase_uppered, &abbrev_nchar, &phrase_nchar, abbrev, phrase, &command);
            else
            list_combs(found, &per_word, phrase_uppered, &abbrev_nchar, &phrase_nchar, abbrev, phrase, &command);
        }
    }

    if(input_result<1)
    {   
        free_all(abbrev, input, phrase, found, phrase_uppered);
    }
    return 0;
}