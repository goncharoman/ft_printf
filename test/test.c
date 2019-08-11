#include <ft_printf.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	ft_printf("|% 03d|\n", 0);
	printf("|% 03d|\n", 0);
	printf("|% 04d|\n", 4);
	printf("|%0 4d|\n", 4);

	// ft_printf("|%5%|\n");
	// printf("|%5%|\n");

	return (0);
}

// int main()
// {
// 	char *c;

// 	c = malloc(sizeof(char) * )
// 	c = 0;
// 	printf("|%c|\tsizeof : %d\n", c, sizeof(&c));

// }
