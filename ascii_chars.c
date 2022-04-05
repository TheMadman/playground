#include <stdio.h>

int main()
{
	for (char i = ' '; i <= '~'; i++)
		printf("%c\t%d\t%x\n", i, i, i);
}
