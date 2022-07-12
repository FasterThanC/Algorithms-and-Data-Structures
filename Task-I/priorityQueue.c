#include <stdio.h>
#include <stdlib.h>
#include "headers.h"

const int cikluSkaicius = 5;

int main()
{
	Queue x = createPQ();
	if( x == NULL)
	{
		printf("failed at creating\n");
		return 0;
	}
		pop(x);
		top(x);
		push(x, 1, 5); printf("%d\n", top(x));
		push(x, 2, 8);printf("%d\n", top(x));
		push(x, 3, 7);printf("%d\n", top(x));

		push(x, 4, 10);printf("%d\n", top(x));
		push(x, 5, 6);printf("%d\n", top(x));
		push(x, 6, 11);printf("%d\n", top(x));

		printf("pop1: %d \n", pop(x));
		printf("pop2: %d \n", pop(x));
		printf("pop3: %d \n", pop(x));
		printf("pop4: %d \n", pop(x));
		printf("pop5: %d \n", pop(x));
		printf("pop6: %d \n", pop(x));

		push(x, 100, 15); printf("%d\n", top(x));
		printf("pop1.2: %d \n", pop(x));
		for(int i=0; i< cikluSkaicius; i++)
		{
			push(x, (i+1)*10, i); printf("%d \n", top(x));
		}
		printf("----------------------\n");
		for(int i=0; i< cikluSkaicius; i++)
		{
			printf("%d\n",pop(x));
		}
		push(x, -1, 1000000);
		push(x, -2, -1000000);
		// printf("%d\n", top(x));




	return 0;
}
