#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <errno.h>
#include <limits.h>

#define MAX_STATS            1000
#define MAX_WORDS             100
#define MAX_WORD_LEN           30 
#define MAX_NUM_WRONG_GUESSES   5
#define NUM_LINES_IN_STAT_FILE  3

#define SUCCESS                  1
#define FAILURE                  0 

#define TRUE                     1
#define FALSE                    0

typedef struct statistics {
    int gameNumber;
    int wins;
    int losses;
} STATS, *PSTATS;

typedef struct game {
    int  numWrongGuess;
    char *word;
    char line[MAX_WORD_LEN];
} GAME, *PGAME;



int validateStats(char * buff, int *si)
{
    int status = FAILURE;

    // validate buffer can be converted from string to integer
    char *end;
    errno = 0;

    const long sl = strtol(buff, &end, 10);
    
    if (end == buff) {
        fprintf(stderr, "%s: not a decimal number\n", buff);
    } else if ('\0' != *end) {
        fprintf(stderr, "%s: extra characters at end of input: %s\n", buff, end);
    } else if (( LONG_MIN == sl || LONG_MAX == sl ) && ERANGE == errno ) {
        fprintf(stderr, "%s out of range of type long\n", buff);
    } else if ( sl > INT_MAX) {
        fprintf( stderr, "%ld greater than INT_MAX\n", sl);
    } else if ( sl < INT_MIN) {
        fprintf(stderr, "%ld less than INT_MIN\n", sl);
    } else {
        *si = (int)sl;
        status = SUCCESS; 
    }
    
    // validate converted integer is with acceptable range
    if ( *si < 0 || *si > MAX_STATS )
    {
        status = FAILURE;
    }

    return status;
}

void displayStats(PSTATS s)
{
    printf("\n******************************\n");
    printf("%s%d%s", "Game# ", s->gameNumber, "  ");
    printf("  %d%s%d%s", s->wins, " wins / ",  s->losses, " losses" );
    printf("\n******************************\n");
    return;
}

int writeStats(PSTATS s, const char *filepath)
{
    FILE *fp = NULL; 

    if ( ( fp = fopen( filepath, "w" ) ) == NULL ) 
    {
            

    }

    return FAILURE;    
}

int readStats(PSTATS s, const char *filepath)
{
    int status = FAILURE;
    FILE * fp = NULL;
    if ( ( fp = fopen( filepath, "r" ) ) == NULL )
    {
        fprintf( stderr, "%s%s\n", "file not found: ", filepath );

        // initialize stats structure (first time playing)
        s->gameNumber = 0;
        s->wins = 0;
        s->losses = 0;

        status = SUCCESS;
    }

    else 
    {
        // stats file already exists, read in game stats
        char *p;
        char line[10] = { '\0' };

        int gameStatNum = 0;
        int temp[NUM_LINES_IN_STAT_FILE] = { 0 };
        int linesSuccessfullyRead = 0;

        // only read in 3 lines
        while ( ( fgets(line, sizeof(line), fp ) != NULL ) && linesSuccessfullyRead < NUM_LINES_IN_STAT_FILE )
        {
            // remove newline
            p = strchr(line, '\n');
            if ( p )
            {
                *p = '\0';
#ifdef DEBUG
                printf("\t%s%s%zu\n", line, "  strlen(line): ", strlen(line));
#endif
                if ( ( validateStats ( line, &gameStatNum ) ) == SUCCESS )
                {
                    // initialize stats struct with valid values
                    temp[linesSuccessfullyRead] = gameStatNum; 
                    linesSuccessfullyRead++;
                }
                else
                {
                    fprintf(stderr, "%s%s\n", "invalid value in stats file: ", line);
                    status = FAILURE;
                    goto Exit;
                }
            } 

            else 
            {
                fprintf(stderr, "%s%s\n", "error with parsing line: ", line);
                status = FAILURE;
                goto Exit;
            }

        } // end while
        
        // initialize struct after first valid lines are read (lines after are ignored)
        s->gameNumber = temp[0];
        s->wins = temp[1];
        s->losses = temp[2];
            
        status = SUCCESS;
    }

Exit:
    if ( fp )
    {
        fclose(fp);
    }

    return status; 
}


int selectWord(const char *filepath, char **rWord)
{
    srand(time(NULL));

    char word[MAX_WORD_LEN];
    char wordList[MAX_WORDS][MAX_WORD_LEN] = { '\0' };
    char *p = NULL;
    int numWords = 0;
    int randomIdx = 0;

#ifdef DEBUG
    printf("%s%s\n", "OPENING FILE: ", filepath);
#endif
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
#ifdef DEBUG
            printf("\t%s\n", word);
#endif

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
    int i;
    char c = '_';

    g->numWrongGuess = 0;
    g->word = rWord;

    memset(g->line, '\0', sizeof(g->line));
   
    // fill buffer with underscores based on length of random word
    for( i = 0; i < strlen(g->word); i++ )
    {
        strncat(g->line, &c, sizeof(char));
    }
    printf("\n");
}

void printGame(PGAME g)
{
    printf("%d ", g->numWrongGuess);
    printf("%s ", g->line);
    printf("%s", " : ");
    fflush(stdout);
}

void updateGame(PGAME g, char * choice)
{
    int i;
    int didNotFindChoice = TRUE ;

    // check if choice appears in word
    for ( i = 0; i < strlen(g->word); i++)
    {
	// correct guess - overwrite place in line with letter choice
	if ( g->word[i] == *choice ) 
	{
	    g->line[i] = *choice;
	    didNotFindChoice = FALSE;
	} 
    }  
    if ( didNotFindChoice )
    {
	g->numWrongGuess++;
    }
}

int checkWin(PGAME g)
{
    int gameWon = FALSE;
    char c = '_';

    if ( ( g->numWrongGuess <=  5 ) &&  (! strchr(g->line, c) ) )
    {
        gameWon = TRUE;
    }
    return gameWon;
}

int checkLoss(PGAME g)
{
    int gameLost = FALSE;
    if ( g->numWrongGuess > 5 ) 
    {
	gameLost = TRUE;
    }
    return gameLost;
}

int main(int argc, char *argv[])
{
    GAME            hangmanGame;
    STATS           hangmanStats;
    const char      *statsFile = "hangman_stats.txt";
    char            *wordlist = "words";
    char            *randomWord = NULL;

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
#ifdef DEBUG
    printf("%s%s\n", "random word selected: ", randomWord);
#endif

    memset(&hangmanGame, '\0', sizeof(hangmanGame));
    memset(&hangmanStats, '\0', sizeof(hangmanStats));

    // read in stats from file
    if ( readStats(&hangmanStats, statsFile ) == FAILURE)
    {
        fprintf(stderr, "%s\n", "error processing stats file. exiting...");    
        exit(1);
    }

    displayStats(&hangmanStats);

    initializeGame(&hangmanGame, randomWord);

    printGame(&hangmanGame);

    while ( 1 ) 
    {
        // get user input (choice of letter)    
	// get one byte, extra getchar() to eat newline
	char letterChoice;
	letterChoice  = getchar();
	getchar();
    
        updateGame(&hangmanGame, &letterChoice);

	if ( checkLoss( &hangmanGame ) )
	{
	    printf("%s\n", "GAME LOST");
	    printf("%s%s\n", "WORD: ", hangmanGame.word);
	    break;
	}

	if ( checkWin( &hangmanGame) )
	{
            printf("%s%d\n", "GAME WON!!! Number of misses: ", hangmanGame.numWrongGuess );
	    break;
	}
	printGame(&hangmanGame);
    }

    writeStats( &hangmanStats, statsFile );

    printf("\n");

    return 0;
}
