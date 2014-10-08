/**
 * link:http://blog.csdn.net/heyangbin/article/details/3202435
 */
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

int my_atoi(const char *nptr)
{
	int c; /* current char */
	long total; /* current total */
	int sign; /* if ''-'', then negative, otherwise positive */
	/* skip whitespace */
	while ( isspace((int)(unsigned char)*nptr) )
		++nptr;
	c = (int)(unsigned char)*nptr++;
	sign = c; /* save sign indication */
	if (c == '-' || c == '+')
		c = (int)(unsigned char)*nptr++; /* skip sign */
	total = 0;
	while (isdigit(c)) {
		total = 10 * total + (c - '0'); /* accumulate digit */
		c = (int)(unsigned char)*nptr++; /* get next char */
	}
	if (sign == '-')
		return -total;
	else
		return total; /* return result, negated if necessary */
}
int main()
{
	char *ch = "12345";
	int after = 0;
	after = my_atoi(ch);
	printf("%d",after);
	return 0;
}