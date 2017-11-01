#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>

int main(int argc, char **argv)
{

    int c_flag = 0;
    int r_flag = 0;
    int n_flag = 0;
    int l_flag = 0;
    int s_flag = 0;
    int a_flag = 0;
    int u_flag = 0;
    int h_flag = 0;
    
    char *c_value = NULL;

    int index;
    int c;

    opterr = 0;

    while ( ( c = getopt( argc, argv, "c:rnlsauh") ) != -1 )
    {
        switch( c )
        {
            case 'c':
                c_flag = 1;
                c_value = optarg;
                break;

            case 'r':
                r_flag = 1;
                break;

           case 'n':
                n_flag = 1;
                break;

            case 'l':
                l_flag = 1;
                break;

            case 's':
                s_flag = 1;
                break;

            case 'a':
                a_flag = 1;
                break;

            case 'u':
                u_flag = 1;
                break;

            case 'h':
                h_flag = 1;
                break;

            case '?':
                if (optopt == 'c') 
                {
                    fprintf( stderr, "option -%c requires an argument.\n", optopt );
                }
                else if ( isprint ( optopt ) )
                {
                    fprintf( stderr, "unknown option -%c\n", optopt );
                }
                else
                {
                    fprintf( stderr, "unknown option character: %x\n", optopt );
                }
                exit(1);

            // default case
            default:
                exit (1);
        }
    }

#ifdef DEBUG
     printf( "%s%d\n", "c_flag: ", c_flag );
     printf( "%s%s\n", "c_value: ", c_value );
     printf( "%s%d\n", "r_flag: ", r_flag );
     printf( "%s%d\n", "n_flag: ", n_flag );
     printf( "%s%d\n", "l_flag: ", l_flag );
     printf( "%s%d\n", "s_flag: ", s_flag );
     printf( "%s%d\n", "a_flag: ", a_flag ); 
     printf( "%s%d\n", "u_flag: ", u_flag );
     printf( "%s%d\n", "h_flag: ", h_flag );
#endif

    if ( h_flag ) {
        printf("usage: %s\n", argv[0]);
        printf("\t%s\n", "-c <number_first_results_to_print>");
        printf("\t%s\n", "-r print in reverse order");
        printf("\t%s\n", "-n sort words as if numbers");
        printf("\t%s\n", "-l sort words by length");
        printf("\t%s\n", "-s sorts by scrabble score");
        printf("\t%s\n", "-a sorts lexicographically");
        printf("\t%s\n", "-u print only unique words");
        printf("\t%s\n", "-h help menu");
    }


        
    return 0;
}
