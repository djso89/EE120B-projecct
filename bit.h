#ifndef __BIT_H__
#define __BIT_H__

#define uchar unsigned char
//bit access funcion
/*
x - target variable
k - bit location
*/
uchar GetBit (uchar x, uchar k)
{
	return ((x&(0x01<<k)) != 0);
}
//bit mutating function
/*x-target variable
k-bit location
b- one or zero
*/
uchar SetBit (uchar x,uchar k,uchar b)
{
	return (b ? x | (0x01<<k) : x & ~(0x01<<k));
}



#endif