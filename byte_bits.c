#include <stdio.h>

int main()
{
	unsigned char byte = ~0;
	int result = 0;
	for(; byte; byte = byte >> 1, result++) {
	}

	printf("%d\n", result);
}
