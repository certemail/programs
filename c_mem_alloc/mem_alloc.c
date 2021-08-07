#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define MAX_PID_LEN     5

char *read_pid(char *filename)
{
    int fd;
    int i;
    char tmp_buf[1];
    char *pidbuf = NULL;


    fd = open( filename, O_RDONLY );
    if( fd >= 0 )
    {
        printf("[%s]: Opened \"%s\", fd=%d\n", __func__, filename, fd);

        printf("alloc memory...\n");
        pidbuf = (char *)malloc( MAX_PID_LEN + 1 );
        if ( NULL == pidbuf )
        {
            printf("malloc failed\n");
            goto EXIT;
        }
        printf("zeroing buffer\n");
        memset( pidbuf, '\0', sizeof(pidbuf) + 1 );
        
        i = 0;
        while( read( fd, tmp_buf, 1 ) == 1 )
        {
            pidbuf[i] = tmp_buf[0];
            i++;
        }
        printf("closing fd\n");
        close(fd);
        /* printf("[%s]: pidbuf = %s\n", __func__, pidbuf); */
    }
    else
    {
        printf( "[%s]:  Failed to open \"%s\"\n", __func__, filename );
        goto EXIT;
    }

EXIT:
    return pidbuf;
}

int main(void)
{
    char *filename = "myfile.pid";
    char *pbuf= NULL;
    pbuf = read_pid(filename);
    if (NULL == pbuf)
    {
        printf("[%s]: failed to get PID\n", __func__);
    }
    printf( "[%s]: pbuf = %s (num chars is = %lu)\n", __func__, pbuf, strlen(pbuf) );

    if( NULL != pbuf )
    {
        free( pbuf );
        pbuf = NULL;
    }
    return 0;
}


/*
void read_file(char *filename)
{
    int fd;
    char buf[1];

    errno = 0;

    fd = open( filename, O_RDONLY );
    if( fd >= 0 )
    {
        printf("[%s]: Opened \"%s\", fd=%d\n", __func__, filename, fd);
        while( read( fd, buf, 1 ) == 1 )
        {
            printf("%c", buf[0]);
        }
        close(fd);
    }
    else
    {
        perror( __func__ );
    }
}
*/

/*
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
*/
