#include <stdio.h>

#define HIDE_LETTER(a)   (a) + 0x50
#define UNHIDE_STRING(str)  do { char * ptr = str ; while (*ptr) *ptr++ -= 0x50; } while(0)
#define HIDE_STRING(str)  do {char * ptr = str ; while (*ptr) *ptr++ += 0x50;} while(0)
int main()
{   // store the "secret password" as mangled byte array in binary
        char str1[] =   { 
                            HIDE_LETTER('P') , 
                            HIDE_LETTER('R') , 
                            HIDE_LETTER('I') , 
                            HIDE_LETTER('N') , 
                            HIDE_LETTER('T') ,
                            HIDE_LETTER('F') ,
                            '\0'
                        };
        UNHIDE_STRING(str1);  // unmangle the string in-place
        printf("Here goes the secret we hide: \n%s\n", str1);
        HIDE_STRING(str1);  //mangle back

        /*  TODO use function pointer to call by string name */

        

    return 0;
}
