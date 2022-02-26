#include <stdio.h>
#include <wchar.h>
#include <string.h>
#include <locale.h>

const char usage[] = "Usage: %s <unicode string>\n";

int main(int argc, char **argv)
{
	if (argc < 2) {
		printf(usage, argv[0]);
		return 1;
	}

	setlocale(LC_ALL, "");

	for (int current_arg = 1; current_arg < argc; current_arg++) {
		const char *arg = argv[current_arg];
		mbstate_t ps = { 0 };
		size_t byte_len = strlen(arg);
		for (
			size_t result = 0;
			(result = mbrlen(arg, byte_len, &ps)) && *arg;
			arg += result, byte_len -= result
		) {
			if (result == (size_t)-1)
				return 2;
			if (result == (size_t)-2)
				return 3;
	
			if (result == 1)
				printf("%c", *arg);
			else
				for (size_t current_byte = 0; current_byte < result; current_byte++) {
					printf("\\x%x", arg[current_byte] & (unsigned char)~0);
				}
		}
		printf(" ");
	}
	printf("\n");

	return 0;
}
