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

        printf("[%s]: Allocating memory...\n", __func__);
        pidbuf = (char *)malloc( MAX_PID_LEN + 1 );
        if ( NULL == pidbuf )
        {
            printf("malloc failed\n");
            goto EXIT;
        }
        printf("[%s]: Zeroizing buffer\n", __func__);
        memset( pidbuf, '\0', sizeof(pidbuf) + 1 );
        
        i = 0;
        while( 1 == read( fd, tmp_buf, 1 ) )
        {
            pidbuf[i] = tmp_buf[0];
            i++;
        }
        printf("[%s]: Closing fd\n", __func__);
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
