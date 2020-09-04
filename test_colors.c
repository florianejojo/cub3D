#include <stdio.h>
int create_rgb(int r, int g, int b)
{
    return (r << 16 | g << 8 | b);
}

int create_r(int num)
{
    return(num >> 16);
}

int create_g(int num)
{
    return(num << 8 & 0xFF);
}

int create_b(int num)
{
    return(num  & 0xFF);
}

int main(void)
{
    int num;
    int r;
    int g;
    int b;
    double x = 0.2;
    int texx = x * 64;

    num = create_rgb(255,0,102);
    printf("num = %d\n", num);
    r = create_r(num);
    g = create_g(num);
    b = create_b(num);
    printf("r = %d, g = %d, b =%d\n", r, g, b);
    printf("texx = %d\n", texx);

    return (1);
}