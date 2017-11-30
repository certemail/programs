#include <stdio.h>
#include <stdlib.h>



int fib( int num )
{
    printf("computing fibonacci(%d)...\n", num);
    

    // base case (first fibonacci number is : 0;
    if ( num == 0 )
    {
        printf("fibonacci of 0 is: 0\n");
        return 0;
    }

    if ( num == 1 )
    {
        printf("fibonacci of 1 is: 1\n");
        return 0;
    }

    if ( num == 2 )
    {
        printf("fibonacci of 2 is: 1\n");
        return 0;
    }

    printf("fibonacci of %3d is: %15d  ( 0x%016llx ) \n", 0, 0, (unsigned long long)0);
    printf("fibonacci of %3d is: %15d  ( 0x%016llx ) \n", 1, 1, (unsigned long long)1);
    printf("fibonacci of %3d is: %15d  ( 0x%016llx ) \n", 2, 1, (unsigned long long)1);

    unsigned long long f_0 = 1;
    unsigned long long f_1 = 1;
    unsigned long long result = 0;

    for( int i = 3; i <= num; i++ )
    {
        result = f_0 + f_1;

        printf("fibonacci of %3d is: %15llu  ( 0x%016llx ) \n", i, result, result);
        f_0 = f_1;
        f_1 = result;
    }
}

int main(int argc, char *argv[])
{

    int result = fib(atoi(argv[1]));

    return 0;
}
