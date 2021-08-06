#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void read_file(char **line);


void read_file(char **pp_line)
{
    if( *pp_line != NULL)
    {
        free(*pp_line);
    }

    //read line
    // size = read(fd, line, etc.)

    malloc( *pp_line, size+1)

    memset(*pp_line, '\0', size+1);

    memcpy(*pp_line, line, size);
}

int main(void)
{
    char *line = NULL;
    read_file(&line);

    // need to free line here when done

    return 0;
}
