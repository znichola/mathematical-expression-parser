#include "eval.h"

t_value	parse_float(char **str)
{
	t_value	n;
	t_value	sign;
	t_value	weight;

	n = 0;
	sign = 1;
	if (**str == '-')
	{
		sign = -1;
		(*str)++;
	}
	while (isdigit(**str))
	{
		n = (n * 10) + (**str - '0');
		(*str)++;
	}
	if (**str == '.')
	{
		weight = 1;
		(*str)++;
		while (isdigit(**str))
		{
			weight *= 10;
			n += (**str - '0') * (1 / weight);
			(*str)++;
		}
	}
	return (n * sign);
}
