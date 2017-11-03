#ifndef _UTILS_H
#define _UTILS_H

#define SUCCESS         0
#define FAILURE         1

char * remove_newline(char *line);

void convert_to_lowercase(char * token);

char * convert_decimal_to_string( int num );

int convert_string_to_int(char * buff, int *si);

#endif // _UTILS_H
