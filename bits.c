#include <sys/types.h>
#define  BIT_WIDTH 32
int get_bit_val(unsigned int* src, int16_t seq)
{
        int x;
        x= src[seq/BIT_WIDTH];
        x &= 1<<(seq%BIT_WIDTH);
        return (x == 0)?0:1;
}


void set_bit_val(unsigned int* src, int16_t seq)
{
        int x;
        x= src[seq/BIT_WIDTH];
        x |= 1<<(seq%BIT_WIDTH);
        src[seq/BIT_WIDTH] = x;
}

void clear_bit_val(unsigned int *src, int16_t seq)
{
    int x,y;
    x = src[seq/BIT_WIDTH];
    y = ~(1<<(seq%BIT_WIDTH));
    x &= y;
    src[seq/BIT_WIDTH] = x;
}
       

int get_all_one(unsigned int n)
{
	unsigned int c =0 ;
	for (c =0; n; c++) {
		n &= (n -1) ; //mask the last bit
	}
	return c ;
}

int main()
{
	int src = 0xabcdef;
	printf("%x\n",get_bit_val(&src,10));
	set_bit_val(&src,10);
	printf("set %x\n",src);
	clear_bit_val(&src,10);
	printf("set %x\n",src);
	return 0 ;
}
