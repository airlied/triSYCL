#include <stdio.h>
#include <stdbool.h>

char pick_char(bool xyzw, int idx)
{
	if (xyzw) return idx == 3 ? 'w' : 'x' + idx;
	switch (idx) {
	case 0: return 'r';
	case 1: return 'g';
	case 2: return 'b';
	case 3: return 'a';
	}
}

void print_swiz2(bool xyzw, int x, int y) {
	printf("GEN_SWIZ2(%c%c, %d, %d)\n", 
			pick_char(xyzw, x),
			pick_char(xyzw, y),
			x, y);
}

void print_swiz3(bool xyzw, int x, int y, int z) {
	printf("GEN_SWIZ3(%c%c%c, %d, %d, %d)\n", 
			pick_char(xyzw, x),
			pick_char(xyzw, y),
			pick_char(xyzw, z),
			x, y, z);
}
void print_swiz4(bool xyzw, int x, int y, int z, int w) {
	printf("GEN_SWIZ4(%c%c%c%c, %d, %d, %d, %d)\n", 
			pick_char(xyzw, x),
			pick_char(xyzw, y),
			pick_char(xyzw, z),
			pick_char(xyzw, w),
			x, y, z, w);
}

void do_swiz(bool xyzw) {
	int x, y, z, w;
	for (x = 0; x < 4; x++)
        for (y = 0; y < 4; y++)
		print_swiz2(xyzw, x, y);
	for (x = 0; x < 4; x++)
	for (y = 0; y < 4; y++)
	for (z = 0; z < 4; z++)
		print_swiz3(xyzw, x, y, z);
	for (x = 0; x < 4; x++)
	for (y = 0; y < 4; y++)
	for (z = 0; z < 4; z++)
	for (w = 0; w < 4; w++)
		print_swiz4(xyzw, x, y, z, w);
}
	
int main(void) {

	printf("// Generated using a simple C generator\n");
	printf("#ifdef SYCL_SIMPLE_SWIZZLES\n");
	do_swiz(true);
	do_swiz(false);
	printf("#endif\n");
}
