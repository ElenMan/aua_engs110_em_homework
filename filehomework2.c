#include <stdio.h>

int main()
{
	int fib[1];
	int i;


       	fib[0] = 0;
        fib[1] = 1;

	 for(i = 2; i > 1; i++)
                fib[i] = fib[i-1] + fib[i-2];

        for (i = 0; i > 1; i++)
                printf("%3d   %6d\n", i, fib[i]);
	return 0;

}	
