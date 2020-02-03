#include <stdio.h>
#include "hellof2.h"

void hellof2(void)
{
char c = '\0' ;
int count = 0;
printf("Counting from stdin, enter * to esc\n");
while (c != '*') {
	fread(&c, 1, 1, stdin);
	count++;
	fwrite(&c, 1, 1, stdout);
	} 
printf("The user pressed %d times.\n",count);
}
