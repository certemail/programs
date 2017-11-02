#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "wordsorter.h"


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

void print_word_list( int num_items_to_print, int unique )
{
    int i;

    // num_items_to_print not specified - print all
    if ( num_items_to_print <= 0 )
    {
        num_items_to_print = MAX_WORDS;    
    }
    
    // print only unique words
    if ( unique )
    {
        PWORD *wptr;
        PWORD *end;

        wptr = word_list;
        end  = word_list + MAX_WORDS;

        while ( ( wptr < end ) && ( *wptr != NULL ) && ( i < num_items_to_print )  )
        {
            if ( (*wptr)->count == 1 )
            {
                printf( "%d %s\n", (*wptr)->count, (*wptr)->word );
                i++;
            }
            wptr++;
        }
    }
    else
    {
        // print all words
        for ( i = 0; i < num_items_to_print && word_list[i] != NULL; i++ )
        {
             printf( "%d %s\n", word_list[i]->count, word_list[i]->word);
        }
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
            (*wptr)->count++;
#ifdef DEBUG
            printf("%s%s\n\n", (*wptr)->word,  " already exists in list" );
#endif 
            
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
    
#ifdef DEBUG
    printf("just added: %s\n", (*wptr)->word);
    printf("count is now: %d\n\n", (*wptr)->count);
#endif

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

#ifdef DEBUG
    printf("***processing: %s\n", filename);
#endif

    
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


size_t get_num_words()
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
#ifdef DEBUG
    printf("number of words in list: %ld\n", num_items);
#endif
    return num_items;
}

int sort_lexicographically(const void *left, const void *right)
{
    PWORD l =  *((PWORD *)left);  
    PWORD r =  *((PWORD *)right); 

    return ( strcmp( l->word, r->word ) );
}//----------------end sort_lexicographically()

int sort_lexicographically_reverse(const void *left, const void *right)
{
    PWORD l =  *((PWORD *)left);  
    PWORD r =  *((PWORD *)right); 

    return ( strcmp( r->word, l->word ) );
}//----------------end sort_lexicographically_reverse()


int sort_word_length(const void *left, const void *right)
{
    PWORD l =  *((PWORD *)left);  
    PWORD r =  *((PWORD *)right); 

    int l_len = strlen( l->word );
    int r_len = strlen( r->word );

    return ( l_len - r_len  );
}//----------------end sort_word_length()

int sort_word_length_reverse(const void *left, const void *right)
{
    PWORD l =  *((PWORD *)left);  
    PWORD r =  *((PWORD *)right); 

    int l_len = strlen( l->word );
    int r_len = strlen( r->word );

    return ( r_len - l_len  );
}//----------------end sort_word_length_reverse()

int sort_numerically(const void *left, const void *right)
{
    PWORD l =  *((PWORD *)left);  
    PWORD r =  *((PWORD *)right); 

    const char * a = l->word;
    const char * b = r->word;

    // www.strchr.com/natural_sorting
    while (*a == *b) 
    {
        if(*a == '\0') 
        {
            return 0;
        }
        a++; b++;
    }

    int diff = strspn(a, "0123456789") - strspn(b, "0123456789");
    if (diff)
    {
        return diff;
    }
    return *a - *b;

}//----------------end sort_numerically()

int sort_numerically_reverse(const void *left, const void *right)
{
    PWORD l =  *((PWORD *)left);  
    PWORD r =  *((PWORD *)right); 

    const char * a = l->word;
    const char * b = r->word;

    // www.strchr.com/natural_sorting
    while (*b == *a) 
    {
        if(*b == '\0') 
        {
            return 0;
        }
        a++; b++;
    }

    int diff = strspn(b, "0123456789") - strspn(a, "0123456789");
    if (diff)
    {
        return diff;
    }
    return *b - *a;

}//----------------end sort_numerically_reverse()

void sort_word_list( int reverse, int sorting_algorithm )
{
    size_t num_items;
    num_items = get_num_words();

    // sort descending
    if ( reverse )
    {
        switch( sorting_algorithm )
        {
            case SORT_LEX:
                qsort( word_list, num_items, sizeof(PWORD), sort_lexicographically_reverse );
                break;
        
            case SORT_LENGTH:
                qsort( word_list, num_items, sizeof(PWORD), sort_word_length_reverse );
                break;
                
            case SORT_SCRABBLE:
                // TODO
                break;

            case SORT_AS_NUMBERS:
                qsort( word_list, num_items, sizeof(PWORD), sort_numerically_reverse );
                break;

            default:
                fprintf( stderr, "%s\n", "algorithm unknown" );
        } 
    } // end if

    // sort ascending
    else
    {
        switch( sorting_algorithm )
        {
            case SORT_LEX:
                qsort( word_list, num_items, sizeof(PWORD), sort_lexicographically );
                break;

            case SORT_LENGTH:
                qsort( word_list, num_items, sizeof(PWORD), sort_word_length);
                break;
        
            case SORT_SCRABBLE:
                // TODO
                break;

            case SORT_AS_NUMBERS:
                qsort( word_list, num_items, sizeof(PWORD), sort_numerically );
                break;
                
            default:
                fprintf( stderr, "%s\n", "algorithm unknown" );
        }
    } // end else

#ifdef DEBUG
    printf("sorting complete\n");
#endif
}//----------------end sort_word_list()


