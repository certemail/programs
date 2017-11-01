#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_WORDS  1000
#define LINE_SIZE   500
#define FAILURE      0
#define SUCCESS      1

typedef struct _word {
    char *word;
    int count;
} WORD, *PWORD;

PWORD word_list[MAX_WORDS];

char * remove_newline(char *line)
{
    char *p = strchr(line, '\n');
    if( p )
    {
        *p = '\0';
    }
    return p;
}

void sanitize_token(char * token)
{
    // convert to lowercase
    int i;
    for ( i = 0 ; i < strlen(token); i++ )
    {
        token[i] = tolower(token[i]);
    }

    // TODO remove non-alphanumeric chars

}

void print_word_list()
{
   printf("%s\n", "printing list:");
   int i;
   for ( i = 0; i < MAX_WORDS && word_list[i] != NULL; i++ )
   {
        printf( "%s %s %d\n", word_list[i]->word, " count: ", word_list[i]->count );
   }
    //PWORD *wptr;
    //PWORD *end;

    //wptr = word_list;
    //end  = word_list + MAX_WORDS;

    //printf("printing word_list: \n");

    //while ( ( *wptr < *end ) && ( *wptr != NULL ) )
    //{
    //    printf("%s ", (*wptr)->word);
    //    printf(" %d ", (*wptr)->count);
    //    wptr++;    
    //}
}

void add_word(char *w)
{
    PWORD *wptr;
    PWORD *end;

    wptr = word_list;
    end  = word_list + MAX_WORDS;


    while ( ( wptr < end ) && ( *wptr != NULL ) )
    {
        wptr++;    
    }
    // word has not been added yet

    // allocate space for new WORD struct
    *wptr = (PWORD)malloc( sizeof(WORD) );

    // zero out new memory allocated
    memset( *wptr, '\0', sizeof(WORD) );

    // add word
    (*wptr)->word = (char *)malloc( strlen(w) + 1 );
    strcpy( (*wptr)->word, w);

    // update count
    (*wptr)->count++;
    
    printf("just added: %s\n", (*wptr)->word);
    printf("count is now: %d\n\n", (*wptr)->count);

}

void process_file( const char * filename )
{
    FILE *fp;
    char *token;
    char line[LINE_SIZE]; 
    const char *delims = " ?;!,\n\t\\";

    printf("processing: %s\n", filename);
    
    if (  ( fp = fopen( filename, "r" ) )   == NULL )
    {
        fprintf( stderr, "%s%s\n", "error opening file: ", filename );
        goto Exit;
    }
    
    // read lines
    while ( ( fgets( line, sizeof(line), fp ) != NULL ) )
    {
        // remove newline to check if buffer exceeded
        if ( remove_newline(line) == NULL ) {
            fprintf(stderr, "%s%d\n", "LINE EXCEEDED", LINE_SIZE);
        }

        char *copy = (char *)malloc(strlen(line) + 1);
        if (copy == NULL) {
            goto Exit;
        }

        // NULL terminator space included
        strcpy(copy, line);

        token = strtok(copy, delims);

        // sanitize (convert to lowercase, check for non-alpa chars)
        sanitize_token(token);
    
        // add word to word_list
        add_word(token);

        //puts(token); 

        while( (token = strtok(NULL, delims) ) ) {
            //puts(token);
            add_word(token);
        }
        free(copy);
        copy = NULL;
    }
    printf("\n"); 

Exit:
    if ( fp ) {
        fclose(fp);
    }
}

int main(int argc, char *argv[])
{
    int idx;

    printf("\n");
    if ( argc < 2 ) 
    {
        printf( "usage: <prog> <filename>\n" );
    } 
    else 
    {
        memset(word_list, '\0', sizeof(word_list));

        idx = argc - 1;
        while (idx >= 1) 
        {
            process_file(argv[idx]);
            idx--;
        }
    }
    print_word_list();

}
