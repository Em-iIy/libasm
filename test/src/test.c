#include <stdio.h>
#include <stdbool.h>

#include "color.h"

const char *TEST_OK = "["GREEN"OK"RESET"]";
const char *TEST_KO = "["RED"KO"RESET"]";

int	test(bool result)
{
	printf("%s ", result ? TEST_OK : TEST_KO);
	return (result ? 0 : 1);
}

void	check_error_count(int error_count)
{
	if (error_count == 0)
		printf(GREEN"All tests passed!\n\n"RESET);
	else
		printf("Failed %d tests.\n\n", error_count);
}
