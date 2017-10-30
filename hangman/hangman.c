// RS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <errno.h>
#include <limits.h>
#include <ctype.h>

#define MAX_STATS               1000
#define MAX_WORDS                100
#define MAX_WORD_LEN              30 
#define MAX_NUM_WRONG_GUESSES      5
#define NUM_LINES_IN_STAT_FILE     3

#define SUCCESS                    1
#define FAILURE                    0 

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

void displayHangman(int wrongGuesses)
{
    switch( wrongGuesses )
    {
        case 0:
            printf("\n");
            printf("\n");
            break;

        case 1:
            printf("    O \n");
            printf("\n");
            break;

        case 2:
            printf("    O \n");
            printf("    | \n");
            printf("\n");
            break;

        case 3:
            printf("    O \n");
            printf("   /| \n");
            printf("\n");
            break; 

        case 4:
            printf("    O \n");
            printf("   /|\\ \n");
            printf("\n");
            break;

        case 5: 
            printf("    O    \n");
            printf("   /|\\  \n");
            printf("   /     \n");
            printf("\n");
            break;

        case 6:
            printf("    O     \n");
            printf("   /|\\   \n");
            printf("   / \\   \n");
            printf("\n");
            break;

        default:
            fprintf( stderr, "%s\n", "error displaying hangman" );
    }
}

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
}//-------------------------------validateStats()

void displayStats(PSTATS s)
{
    printf("\n***********************************\n");
    printf("%s%d%s", "Game# ", s->gameNumber, "  ");
    printf("  %d", s->wins);
    printf("  %s%c", " win", (s->wins == 1) ? ' ' : 's');
    printf("%s", " / ");
    printf("  %d", s->losses);
    printf("  %s%s", " loss", (s->losses == 1) ? " " : "es");
    printf("\n***********************************\n");
    return;
}//-------------------------------displayStats()

int writeStats(PSTATS s, const char *filepath)
{
    int status = FAILURE;
    FILE *fp = NULL; 

    if ( ( fp = fopen( filepath, "w" ) ) != NULL ) 
    {
        fprintf( fp, "%d\n%d\n%d\n", s->gameNumber, s->wins, s->losses );            
        status = SUCCESS;
    }

    if ( fp ) 
    {
        fclose( fp );
    }

    return status;    
}//-------------------------------end writeStats()

int readStats(PSTATS s, const char *filepath)
{
    int status = FAILURE;
    FILE * fp = NULL;
    if ( ( fp = fopen( filepath, "r" ) ) == NULL )
    {
        fprintf( stderr, "%s%s\n", "file not found: ", filepath );

        // initialize stats structure (first time playing)
        s->gameNumber = 1;
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
}//-------------------------------end readStats() 

int selectWord(const char *filepath, char **rWord)
{
    srand(time(NULL));

    char word[MAX_WORD_LEN];
    char wordList[MAX_WORDS][MAX_WORD_LEN] = { '\0' };
    char *p = NULL;
    int numWords = 0;
    int randomIdx = 0;
    int i;

#ifdef DEBUG
    printf("%s%s\n", "OPENING FILE: ", filepath);
#endif

    FILE *fp = NULL;
    if ( ( fp = fopen( filepath, "r" ) ) == NULL )
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

        // convert to lower case
        for ( i = 0; word[i]; i++ )
        {
            word[i] = tolower( (unsigned char)word[i] );
        }
#ifdef DEBUG
        printf("word tolower: %s\n", word);
#endif
        // copy word into array
        // word is already NULL terminated
        strncpy(wordList[numWords], word, MAX_WORD_LEN);
        numWords++;
    }

    // randomly select word in wordList
    randomIdx = rand() % numWords; 
    *rWord = wordList[randomIdx];

    fclose( fp );

    return SUCCESS;
} //-------------------------------end selectWord()

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
}//-------------------------------end initializeGame()

void printGame(PGAME g)
{
    printf("%d ", g->numWrongGuess);
    printf("%s ", g->line);
    printf("%s", " : ");

    fflush(stdout);
}//-------------------------------end printGame()

void updateGame(PGAME g, char * choice)
{
    int i;
    int didNotFindChoice = 1 ;

    // check if choice appears in word
    for ( i = 0; i < strlen(g->word); i++)
    {
	// correct guess - overwrite place in line with letter choice
	if ( g->word[i] == *choice ) 
	{
	    g->line[i] = *choice;
	    didNotFindChoice = 0;
	} 
    }  
    if ( didNotFindChoice )
    {
	g->numWrongGuess++;
    }
}//-------------------------------end updateGame()

int checkWin(PGAME g)
{
    int gameWon = 0;
    char c = '_';

    if ( ( g->numWrongGuess <=  5 ) &&  (! strchr(g->line, c) ) )
    {
        gameWon = 1;
    }
    return gameWon;
}//-------------------------------end checkWin()

int checkLoss(PGAME g)
{
    int gameLost = 0;
    if ( g->numWrongGuess > 5 ) 
    {
	gameLost = 1;
    }
    return gameLost;
}//-------------------------------end checkLoss()

// reads HOME environment variable and concatenates it with filename
int concatHomeDirAndFile(char **fullPath, const char *fileName)
{
    char *buf = NULL;
    char *homeEnv = NULL; 
    char *pathSep = "/";
    int status = FAILURE;
    size_t homeEnvLen;
    size_t bufLen;
    size_t pathSepLen;
    size_t strLen; 
    size_t totalSize;
    
    homeEnv = getenv("HOME");
    if ( homeEnv == NULL ) 
    {
        // HOME not set
        fprintf(stderr, "%s\n", "HOME environment variable not set...");
        goto Exit;
    } 
    else 
    {
        homeEnvLen = strlen(homeEnv) + 1 ;
        buf = (char *)malloc(homeEnvLen);
        if ( buf == NULL ) 
        {
            fprintf( stderr, "%s\n", "malloc failed");
            goto Exit;
        }
        // NULL terminator is included 
        memcpy( buf, homeEnv, homeEnvLen );
    }

    bufLen = strlen(buf);
    pathSepLen = strlen(pathSep);
    strLen = strlen(fileName);

#ifdef DEBUG
    printf("bufLen: %ld\n", bufLen);
    printf("pathSepLen: %ld\n", pathSepLen);
    printf("wordListLen: %ld\n", strLen);
    printf("Total buffer size (including NULL): %ld\n", bufLen + pathSepLen + strLen + 1);
#endif

    // add one for NULL terminator
    totalSize = bufLen + pathSepLen + strLen + 1;
    
    *fullPath = (char *)malloc( totalSize );
    if ( *fullPath == NULL )
    {
        fprintf(stderr, "%s\n", "malloc failed");
        goto Exit;
    }

    // snprintf() returns on success number of characters printed excluding the NULL terminator
    int n;
    n = snprintf( *fullPath, totalSize, "%s%s%s", buf, pathSep, fileName );
    if ( n < 0 || n > totalSize - 1 ) {
        goto Exit;
    }
    status = SUCCESS;

Exit:
    if ( buf ) {
        free( buf );
    }
    return status;
}

int main(int argc, char *argv[])
{
    GAME            hangmanGame;
    STATS           hangmanStats;
    const char      *defaultStatsFile = ".stats";   
    const char      *defaultWordFile = ".words";
    const char      *wordlist = NULL;              
    char            *randomWord = NULL;
    char            *fullPathToDefaultWordList = NULL;
    char            *fullPathToStatsFile = NULL;
    char            *otherWordList = NULL;

    if (argc > 2) {
        printf("%s%s%s\n", "usage: ", argv[0], " <path_to_word_list>");
        exit( 1 );
    }

    // word list provided by cmd line arg 
    if ( argv[1] ) 
    {
        //wordlist = argv[1];    
        otherWordList = (char *)malloc( strlen (argv[1] + 1 ));
        if ( otherWordList != NULL )
        {
            strcpy( otherWordList, argv[1] );
            otherWordList[ strlen(argv[1]) ] = '\0';
        } 
        else
        {
            fprintf( stderr, "%s\n", "malloc() failed" );
            goto Exit;
        }
        wordlist = otherWordList;
    } 
    else 
    {
        // build full path to default word list in HOME directory
        if ( concatHomeDirAndFile( &fullPathToDefaultWordList, defaultWordFile) == FAILURE ) 
        {
            fprintf( stderr, "%s\n", "error getting path to word file" );
            goto Exit;
        }
        wordlist = fullPathToDefaultWordList;
    }

    // select random word
    if (selectWord(wordlist, &randomWord) == FAILURE ) 
    {
        fprintf( stderr, "%s\n", "error selecting word" );
        goto Exit;
    }

    // zero out memory
    memset(&hangmanGame, '\0', sizeof(hangmanGame));
    memset(&hangmanStats, '\0', sizeof(hangmanStats));

    // build full path to stats file in HOME directory
    if (concatHomeDirAndFile( &fullPathToStatsFile, defaultStatsFile ) == FAILURE )
    {
        fprintf( stderr, "%s\n", "error opening stats file" );
        goto Exit;
    }
    
    // read in stats from file
    if ( readStats(&hangmanStats, fullPathToStatsFile ) == FAILURE)
    {
        fprintf( stderr, "%s\n", "error reading stats file");    
        goto Exit;
    }

    printf("%s%s\n", "Using word list:  ", wordlist );
    printf( "%s%s\n", "Using stats file: ", fullPathToStatsFile );

    displayStats(&hangmanStats);
    initializeGame(&hangmanGame, randomWord);
    printGame(&hangmanGame);

    while ( 1 ) 
    {
	char letterChoice;
	char tempBuf[5];
	int ch;
	char *p;

        // read from stdin restricted to 5 bytes saved in temp buffer
	if (fgets(tempBuf, sizeof(tempBuf), stdin)) 
	{
            p = strchr(tempBuf, '\n');
            if (p) 
            {
                *p = '\0';
	    }	
	    else 
            {
                // newline not found (input exceeded buffer size) flush stdin to end of line
                while (((ch = getchar()) != '\n')
                            && !feof(stdin)
                            && !ferror(stdin)  );
            }
	}
	else 
        {
            fprintf(stderr, "%s\n", "failure to reading from stdin");
            goto Exit;
	}
        // cast to unsigned char (tolower expects an int)
	letterChoice = tolower( (unsigned char)tempBuf[0] );

        updateGame(&hangmanGame, &letterChoice);

	if ( checkLoss( &hangmanGame ) )
	{
            displayHangman( hangmanGame.numWrongGuess);
	    printf("%s\n", "GAME LOST!!");
	    printf("%s%s\n", "WORD: ", hangmanGame.word);
            hangmanStats.losses++;
	    break;
	}

	if ( checkWin( &hangmanGame) )
	{
            printf("%s%d\n", "GAME WON!!! Number of misses: ", hangmanGame.numWrongGuess );
            hangmanStats.wins++;
	    break;
	}

        displayHangman(hangmanGame.numWrongGuess);

	printGame(&hangmanGame);
    } //---end while()

    hangmanStats.gameNumber++;
    writeStats( &hangmanStats, fullPathToStatsFile );

Exit:
    // free memory still in use
    if ( wordlist ) {
        free ( wordlist );
    }
    if ( fullPathToStatsFile ) {
        free ( fullPathToStatsFile );
    }

    return 0;
}//-------------------------------end main()
