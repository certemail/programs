#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_WORDS             100
#define MAX_WORD_LEN           30 
#define MAX_NUM_WRONG_GUESSES   5

#define SUCCESS                 0
#define FAILURE                 1

typedef struct statistics {
    int wins;
    int losses;
    int gameNumber;
} STATS, *PSTATS;

typedef struct game {
    int  numCorrectGuess;
    int  numWrongGuess;
    char *word;
    char line[MAX_WORD_LEN];
} GAME, *PGAME;

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


void initializeGame(PGAME g, char *rWord)
{
    printf("\n%s\n", "initializing game...");
    int i;
    char c = '_';

    g->numCorrectGuess = 0;
    g->numWrongGuess = 0;
    g->word = rWord;

    memset(g->line, '\0', sizeof(g->line));
   
    // fill buffer with underscores based on length of random word
    for( i = 0; i < strlen(g->word); i++ )
    {
        strncat(g->line, &c, sizeof(char));
    }
}

void printGame(PGAME g)
{
    printf("\n");
    printf("%s%d\n", "wrong   guesses: ", g->numWrongGuess);
    printf("%s%d\n", "correct guesses: ", g->numWrongGuess);
    printf("%s%s\n", "word: ", g->word); 
    printf("%s%s\n", "line: ", g->line);

    printf("\n"); 
}

int main(int argc, char *argv[])
{
    GAME hangmanGame;
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

    //initialize game
    initializeGame(&hangmanGame, randomWord);

    printGame(&hangmanGame);

    return 0;
}
