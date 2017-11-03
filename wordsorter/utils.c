#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include <errno.h> 
#include "utils.h"

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


void convert_to_lowercase(char * token)
{
    // convert to lowercase
    int i;
    for ( i = 0 ; i < strlen(token); i++ )
    {
        token[i] = tolower(token[i]);
    }
}//----------------end sanitize_token()


char * convert_decimal_to_string( int num )
{
    // callee must free memory

    char * buffer = NULL;
    size_t buffer_size = sizeof(int) * 4 + 1;

    buffer = (char *)malloc( buffer_size );

    if ( buffer == NULL )
    {
        fprintf( stderr, "%s\n", "malloc failed()" );
        abort();
    }

    snprintf( buffer, buffer_size, "%d", num );

    return buffer;
}//-------------------------------end convert_decimal_to_string() 


int convert_string_to_int(char * buff, int *si)
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

    return status;
}//-------------------------------end convert_string_to_int()
