#include <stdio.h>

/*
 * It looks like there really is _absolutely no way_
 * to express a truly generic function pointer, I.E.
 * a function pointer which is compatible with any
 * other function pointer the way that void* is
 * compatible with any object pointer.
 *
 * In the documentation for GCC's `-Wcast-function-type`
 * flag, it states "The function type 'void (*) (void)'
 * is special and matches everything, which can be used
 * to suppress this warning". However, that doesn't
 * suppress `-Wincompatible-pointer-types`, which in
 * this program still warns for the `step = step(i);`
 * line and _would_ warn on these returns without the
 * cast.
 */

typedef void step_fn(void);

step_fn *finish(int in)
{
	if (in == 8) {
		puts("Finishing");
	}
	return 0;
}

step_fn *expect_four(int in)
{
	if (in == 4) {
		puts("Got four");
		return (step_fn *)finish;
	}
	return 0;
}

step_fn *expect_two(int in)
{
	if (in == 2) {
		puts("Got two");
		return (step_fn *)expect_four;
	}
	return 0;
}

step_fn *expect_one(int in)
{
	if (in == 1) {
		puts("Got one");
		return (step_fn *)expect_two;
	}
	return 0;
}

int main()
{
	step_fn *(*step)(int) = expect_one;
	for (int i = 1; step; i *= 2) {
		// the pointer soup here is _actually recommended by POSIX_
		// to cast between function- and object-pointers
		// See the man page for dlopen(3)
		printf("%d: %p\n", i, *(void **)&step);
		step = step(i);
	}
}

