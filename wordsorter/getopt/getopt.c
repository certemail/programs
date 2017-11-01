#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>

typedef struct global_args {
    char *c_num_sorted_words;            // -c <num> as string
    int num_sorted_words;               // -c <num>
    int reverse;                        // -r
    int sort_words_as_numbers;          // -n
    int sort_words_by_length;           // -l
    int sort_words_by_scrabble_score;   // -s
    int sort_words_lexicographically;   // -a
    int print_only_unique_words;        // -u
    int print_help_menu;                // -h
    int num_input_files;                // number of files specified on cmd line
    char **inputFiles;                  // input files
} CMD_LINE_ARGS;


void display_usage()
{
    printf("usage: %s\n", "<prog>");
    printf("\t%s\n", "-c <number_first_results_to_print>");
    printf("\t%s\n", "-r print in reverse order");
    printf("\t%s\n", "-n sort words as if numbers");
    printf("\t%s\n", "-l sort words by length");
    printf("\t%s\n", "-s sorts by scrabble score");
    printf("\t%s\n", "-a sorts lexicographically");
    printf("\t%s\n", "-u print only unique words");
    printf("\t%s\n", "-h help menu");
}

int main(int argc, char **argv)
{

    CMD_LINE_ARGS cmd_args;

    cmd_args.c_num_sorted_words = NULL;          // -c <num> as string
    cmd_args.num_sorted_words = 0;               // -c <num>
    cmd_args.reverse = 0;                        // -r
    cmd_args.sort_words_as_numbers = 0;          // -n
    cmd_args.sort_words_by_length = 0;           // -l
    cmd_args.sort_words_by_scrabble_score  = 0;  // -s
    cmd_args.sort_words_lexicographically = 0;   // -a
    cmd_args.print_only_unique_words = 0;        // -u
    cmd_args.print_help_menu = 0;                // -h
    cmd_args.num_input_files = 0;                // number of files specified on cmd line
    cmd_args.inputFiles = NULL;                  // input files

    int c;

    opterr = 0;

    while ( ( c = getopt( argc, argv, "c:rnlsauh") ) != -1 )
    {
        switch( c )
        {
            case 'c':
                cmd_args.c_num_sorted_words = optarg;
                break;

            case 'r':
                cmd_args.reverse = 1;
                break;

           case 'n':
                cmd_args.sort_words_as_numbers = 1;
                break;

            case 'l':
                cmd_args.sort_words_by_length = 1;
                break;

            case 's':
                cmd_args.sort_words_by_scrabble_score = 1;
                break;

            case 'a':
                cmd_args.sort_words_lexicographically = 1;
                break;

            case 'u':
                cmd_args.print_only_unique_words = 1;
                break;

            case 'h':
                cmd_args.print_help_menu = 1;
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

    // [ -h ] display help menu
    if ( cmd_args.print_help_menu ) {
        display_usage();
    }

    // [ -c ] print only first n results of sorted list
    else if ( cmd_args.c_num_sorted_words )
    {
        printf("cmd_args.c_value: %s\n", cmd_args.c_num_sorted_words );
        cmd_args.num_sorted_words = atoi(cmd_args.c_num_sorted_words);
        printf("cmd_args.num_sorted_words: %d\n", cmd_args.num_sorted_words );
    }
        
    return 0;
}
