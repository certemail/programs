#include <stdio.h>
#include <string.h>
#include <malloc.h>

char *decode(char *s, size_t len);


char *decode(char *s, size_t len)
{
    char *dec_str;
    unsigned i;

    printf("decoding: %s\n", s);

    dec_str = (char *)malloc(sizeof(char) * len);

    for (i = 0; i < len; i++)
    {
        dec_str[i] = s[i] ^ 0x15;
        printf("dec_str: %c\n", dec_str[i]);
    }
    return s;
}


int main(void)
{
    char * str = "}aaef/::lz`a";
    char * dec_str = decode(str, strlen(str));
    int x, y;
    int z;


    /* strackstring example */
    char strackstring[10] = { '\0' };
    strackstring[0] = 'h';
    strackstring[1] = 'e';
    z = x, y = 5;
    strackstring[2] = 'l';
    strackstring[3] = 'l';
    strackstring[4] = 'o';
    strackstring[5] = '\0';

    printf("%s\n", strackstring);

    return 0;
}
