#include <stdio.h>
struct test {
	unsigned int x : 2;
	unsigned int y : 2;
	unsigned int z : 2;
};

struct spi_packet {
	unsigned char address: 6;
	unsigned char rw: 2;
	unsigned short int data: 16;
};
int main()
{
	struct test t;
	t.x = 5;
	printf("%d", t.x);

	struct spi_packet p1 = {0x20, 0x01, 0x0AFD};
	printf("\nSize: %lu\n", sizeof(p1));
	printf("Addr: 0x%x, RW: 0x%x, Data: 0x%x\n", p1.address, p1.rw, p1.data);
	printf("Bit1: 0x%x, Bit2: 0x%x, Bit3: 0x%x\n", (p1.address<<2) | (p1.rw<<1), (p1.data >> 8), (p1.data & 0xff));
	return 0;
}