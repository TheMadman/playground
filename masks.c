#include <stdio.h>

#define first_bit (1 << 7)
#define second_bit (1 << 6)

enum UTF8_BITS {
	UTF8_SINGLE,
	UTF8_START,
	UTF8_CONT,
};

const char *enum_from_char(int c)
{
	switch (c & (first_bit | second_bit)) {
		case 0:
		case second_bit:
			return "UTF8_SINGLE";
		case first_bit:
			return "UTF8_CONT";
		case first_bit | second_bit:
			return "UTF8_START";
	}
	
	return "NONE";
}

void print_char(int c)
{
	printf("\\x%x -> %s\n", c & ((unsigned char)~0), enum_from_char(c));
}

int main()
{
	print_char('?');
	print_char("💩"[0]);
	print_char("💩"[1]);
	print_char("💩"[3]);
}
