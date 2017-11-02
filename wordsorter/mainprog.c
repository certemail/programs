#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include "wordsorter.h"

typedef struct global_args {
    char *c_num_sorted_words;           // -c <num> as string
    int num_sorted_words;               // -c <num>
    int reverse;                        // -r
    int sort_words_as_numbers;          // -n
    int sort_words_by_length;           // -l
    int sort_words_by_scrabble_score;   // -s
    int sort_words_lexicographically;   // -a
    int print_only_unique_words;        // -u
    int print_help_menu;                // -h
    int num_input_files;                // number of files specified on cmd line
    char **input_files;                 // input files
} CMD_LINE_ARGS;


void display_usage()
{
    printf("usage: %s", "<prog>");
    printf("\t%s\n", "-c <number_first_results_to_print>");
    printf("\t\t%s\n", "-r print in reverse order");
    printf("\t\t%s\n", "-n sort words as if numbers");
    printf("\t\t%s\n", "-l sort words by length");
    printf("\t\t%s\n", "-s sorts by scrabble score");
    printf("\t\t%s\n", "-a sorts lexicographically");
    printf("\t\t%s\n", "-u print only unique words");
    printf("\t\t%s\n", "-h help menu");
}

int main(int argc, char **argv)
{

    CMD_LINE_ARGS cmd_args;

    // initialize cmd line args
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
    cmd_args.input_files = NULL;                  // input files

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
                // XOR with 1 to turn off if even number of reverse options specified
                cmd_args.reverse ^= 1;
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
                    display_usage();
                }
                else if ( isprint ( optopt ) )
                {
                    fprintf( stderr, "unknown option -%c\n", optopt );
                    display_usage();
                }
                else
                {
                    fprintf( stderr, "unknown option character: %x\n", optopt );
                    display_usage();
                }
                exit(1);

            // default case
            default:
                exit (1);

        } // end switch

    } // end while


    
#ifdef DEBUG
    printf("%s\n", "***parsing command line options:");
#endif

    // [ -h ] display help menu
    if ( cmd_args.print_help_menu ) {
        display_usage();
        exit( EXIT_SUCCESS );
    }

    // [ -c ] print only first n results of sorted list
    else if ( cmd_args.c_num_sorted_words )
    {
        // convert to integer
        cmd_args.num_sorted_words = atoi(cmd_args.c_num_sorted_words);
#ifdef DEBUG
        printf("number of sorted words to display: %d\n", cmd_args.num_sorted_words );
#endif
    }

    // [ -r ] sort in reverse order
    if ( cmd_args.reverse )
    {
#ifdef DEBUG
        printf("reverse: %d\n", cmd_args.reverse );
#endif
    }




#ifdef DEBUG
    printf("\n%s\n", "***parsing command line arguments:");
#endif
    // get filenames to sort
    if (optind < argc)
    {
        for (; optind < argc; optind++){
            printf("processing file: %s\n", argv[optind]);

            process_file(argv[optind]);
        }
    } 
    else 
    {
        printf("Enter words to be sorted:\n");
            process_from_stdin();
    }

    
    // resolve what sorting algorithm to do and pass to sort_word_list()
    // TODO


    sort_word_list( cmd_args.reverse, SORT_LEX ); //reverse? which sort (lex? length?, etc.)



    print_word_list( cmd_args.num_sorted_words );

    free_word_list();
        
    return 0;
}
