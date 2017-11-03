#ifndef _WORDSORTER_H
#define _WORDSORTER_H

#define MAX_WORDS       10000
#define LINE_SIZE         500

enum algorithms { 
        SORT_LEX, 
        SORT_LENGTH, 
        SORT_SCRABBLE, 
        SORT_AS_NUMBERS 
};

typedef struct _word {
    char *word;
    int count;
    int scrabble_score;
} WORD, *PWORD;

PWORD word_list[MAX_WORDS];

char * remove_newline( char *line );

void sanitize_token( char * token );

void print_word_list( int num_items_to_print, int unique );

void add_word(char *w);

void process_line( char *line );

void process_from_stdin();

void process_file( const char * filename );

void free_word_list();

size_t get_num_words();

int sort_lexicographically(const void *left, const void *right);

int sort_lexicographically_reverse(const void *left, const void *right);

int sort_word_length(const void *left, const void *right);

int sort_word_length_reverse(const void *left, const void *right);

void sort_word_list( int reverse, int sorting_algorithm );



#endif // _WORDSORTER_H
