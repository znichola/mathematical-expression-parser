//#include <stdio.h>

float	parse_float(char *str)
{
	float	n;
	float	sign;
	float	weight;

	n = 0;
	sign = 1;
	if (*str == '-')
	{
		sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		n *= 10;
		n += *str - '0';
		str++;		
	}
	if (*str == '.')
	{
		weight = 1;
		str++;
		while (*str >= '0' && *str <= '9')
		{
			weight *= 10;
			n += (*str - '0') * (1 / weight);
			str++;
		}
	}
	if (sign == -1)
		n *= -1;
	return (n);
}

/*
int main(int argc, char **argv)
{
	char	*s;

	s = argv[1];
	printf("%f\n", parse_float(s));
	return (0);
}
*/
