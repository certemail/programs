#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_WORDS     100
#define MAX_WORD_LEN   50
#define SUCCESS         0
#define FAILURE         1

int selectWord(char *filepath, char **rWord)
{
    srand(time(NULL));

    char word[MAX_WORD_LEN];
    char wordList[MAX_WORDS][MAX_WORD_LEN] = { '\0' };
    char *p = NULL;
    int numWords = 0;
    int randomIdx = 0;

    printf("%s%s\n", "OPENING FILE: ", filepath);
    FILE *fp = NULL;
    if ( ( fp = fopen( filepath, "r" )) == NULL )
    {
        fprintf( stderr, "error opening file\n"); 
        return( FAILURE );
    }
    
    
    while ( fgets(word, MAX_WORD_LEN, fp ) != NULL )
    {
        // remove newline
        p = strchr(word, '\n');
        if ( p )
        {
            *p = '\0';
            printf("\t%s\n", word);
        } 

        else 
        {
            fprintf( stderr, "%s%s%s%zu\n", "word length exceed max word length: ", word, " | strlen(word): ", strlen(word));
            continue;
        }

        // copy word into array
        strncpy(wordList[numWords], word, MAX_WORD_LEN);
        numWords++;
    }
#ifdef DEBUG
    printf("%s\n", "--------------------");
    printf("%s%d\n", "number of words in list: ", numWords);
    int i;
    for ( i = 0; i < numWords; i++ )
    {
        printf("%s\n", wordList[i]);
    } 
#endif

    // randomly select word in wordList
    randomIdx = rand() % numWords; 
    *rWord = wordList[randomIdx];

    fclose( fp );

    return SUCCESS;
}

int main(int argc, char *argv[])
{
    char *wordlist = "words";
    char *randomWord = NULL;

    if (argc > 2) {
        printf("%s%s%s\n", "usage: ", argv[0], " <path_to_word_list>");
        exit( 1 );
    }

    if (argv[1]) 
    {
        wordlist = argv[1];    
    }
    if (selectWord(wordlist, &randomWord) == FAILURE ) 
    {
        exit(2);
    }
    printf("%s%s\n", "random word selected: ", randomWord);


    return 0;
}
