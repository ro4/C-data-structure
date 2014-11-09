/**
 * link:http://blog.csdn.net/heyangbin/article/details/3202435
 */
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

int my_atoi(const char *nptr)
{
	int c;
	long total;
	int sign; /* 标识符 */
	/* 忽略空格*/
	while ( isspace((int)(unsigned char)*nptr) )
		++nptr;
	c = (int)(unsigned char)*nptr++;
	sign = c; /* 把标志转成int */
	if (c == '-' || c == '+')
		c = (int)(unsigned char)*nptr++; /* 忽略标志 */
	total = 0;
	while (isdigit(c)) {
		total = 10 * total + (c - '0');
		c = (int)(unsigned char)*nptr++;
	}
	if (sign == '-')
		return -total;
	else
		return total;
}
int main()
{
	char *ch = "12345";
	int after = 0;
	after = my_atoi(ch);
	printf("%d",after);
	return 0;
}