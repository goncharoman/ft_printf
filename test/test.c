#include <ft_printf.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	ft_printf("|@moulitest: %.10d|\n", -42);
	printf("|@moulitest: %.10d|\n", -42);
	getchar();

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
