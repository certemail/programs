#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_WORDS  1000
#define LINE_SIZE   500

typedef struct _word {
    char *word;
    int count;
} WORD, *PWORD;

PWORD word_list[MAX_WORDS];


char * remove_newline(char *line)
{
    //returns NULL if newline not found
    char *p = strchr(line, '\n');
    if( p )
    {
        *p = '\0';
    }
    return p;
} //----------------end remove_newline()

void sanitize_token(char * token)
{
    // convert to lowercase
    int i;
    for ( i = 0 ; i < strlen(token); i++ )
    {
        token[i] = tolower(token[i]);
    }
}//----------------end sanitize_token()

void print_word_list()
{
   printf("%s\n", "printing list:");
   int i;
   for ( i = 0; i < MAX_WORDS && word_list[i] != NULL; i++ )
   {
        printf( "%d %s\n", word_list[i]->count, word_list[i]->word);
   }
}//----------------end print_word_list()

void add_word(char *w)
{
    PWORD *wptr;
    PWORD *end;

    wptr = word_list;
    end  = word_list + MAX_WORDS;

    while ( ( wptr < end ) && ( *wptr != NULL ) )
    {
        if ( strcmp( (*wptr)->word, w ) == 0 )
        {
            // word is already in the word_list
            printf("%s%s\n\n", (*wptr)->word,  " already exists in list" );
            (*wptr)->count++;
            
            return;
        }
        wptr++;    
    }

    // word has not been added yet

    // allocate space for new WORD struct
    *wptr = (PWORD)malloc( sizeof(WORD) );
    if(  *wptr == NULL ) 
    {
        fprintf( stderr, "%s%d%s\n", __FILE__, __LINE__, " : malloc failed()" );
        abort();
    }

    // zero out new memory allocated
    memset( *wptr, '\0', sizeof(WORD) );

    // add word 
    (*wptr)->word = (char *)malloc( strlen(w) + 1 );
    if ( (*wptr)->word == NULL )
    {
        fprintf( stderr, "%s%d%s\n", __FILE__, __LINE__, " : malloc failed()" );
        abort();
    }

    
    //sufficient space for NULL terminator
    strcpy( (*wptr)->word, w );

    // update count
    (*wptr)->count++;
    
    printf("just added: %s\n", (*wptr)->word);
    printf("count is now: %d\n\n", (*wptr)->count);

    return;
}//----------------end add_word()

void process_line( char *line )
{
    char *token;
    const char *delims = " .?;!,\n\t\\";

    char *copy = (char *)malloc( strlen( line ) + 1);
    if ( copy == NULL ) 
    {
        fprintf( stderr, "%s%d%s\n", __FILE__, __LINE__, " : malloc failed()" );
        abort();
    }

    // NULL terminator space included
    strcpy( copy, line );

    // get first token in line
    token = strtok( copy, delims );

    // sanitize (convert to lowercase, check for non-alpa chars)
    sanitize_token( token );
    
    // add first token to word_list
    add_word( token );

    // get subsequent tokens
    while( (token = strtok(NULL, delims) ) ) 
    {
        sanitize_token(token);
        add_word(token);
    }
    free( copy );
    copy = NULL;
    
    return;
}//----------------end process_line() 

void process_from_stdin()
{
    // read from command line
    char buffer[MAX_WORDS];
    int ch;
    char *p;
    
    // read from stdin 
    if (fgets(buffer, sizeof(buffer), stdin)) 
    {
        p = strchr(buffer, '\n');
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
    }

    process_line( buffer );
}//----------------end process_from_stdin()

void process_file( const char * filename )
{
    FILE *fp;
    char line[LINE_SIZE]; 

    printf("***processing: %s\n", filename);
    
    if (  ( fp = fopen( filename, "r" ) )   == NULL )
    {
        fprintf( stderr, "%s%s\n", "error opening file: ", filename );
        goto Exit;
    }
    
    // read lines
    while ( ( fgets( line, sizeof(line), fp ) != NULL ) )
    {
        // remove newline to check if buffer exceeded
        if ( remove_newline(line) == NULL ) 
        {
            fprintf(stderr, "%s%d\n", "LINE EXCEEDED", LINE_SIZE);
        }
        process_line( line );
    }

Exit:
    // close file pointer
    if ( fp ) {
        fclose( fp) ;
    }
}//----------------end process_file()

void free_word_list()
{
    PWORD *wptr;
    PWORD *end;

    wptr = word_list;
    end  = word_list + MAX_WORDS;

    while ( ( wptr < end ) && ( *wptr != NULL ) )
    {
        // free memory for wptr->word
        if ( (*wptr)->word != NULL ) 
        {
            free( (*wptr)->word );
        }

        // free memory for WORD structure
        if ( (*wptr) != NULL )
        {
            free( *wptr );
        }
        wptr++;    
    }
}//----------------end free_word()

int sorting_func(const void *left, const void *right)
{
    PWORD l =  *((PWORD *)left);  // 
    PWORD r =  *((PWORD *)right); // TODO r does not get set correctly here, why ??

#ifdef DEBUG
    printf("%s\n", "in qsort comparison function...");
    printf("%s ", "l->word: ");
    fflush(stdout);
    printf("%s\n", l->word);
    fflush(stdout);

    printf("%s ", "r->word: ");
    fflush(stdout);
    printf("%s\n", r->word);
    fflush(stdout);
#endif

    return ( strcmp( l->word, r->word ) );
}//----------------end sorting_func()

void sort_word_list()
{
    // find number of elements
    PWORD *wptr;
    PWORD *end;
    size_t num_items = 0;

    wptr = word_list;
    end  = word_list + MAX_WORDS;

    while ( ( wptr < end ) && ( *wptr != NULL ) )
    {
        wptr++;    
        num_items++;
    }
    printf("number of items: %ld\n", num_items);

    qsort( word_list, num_items, sizeof(PWORD), sorting_func );

    printf("sorting complete\n");
}//----------------end sort_word_list()


