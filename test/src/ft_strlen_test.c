#include <stdio.h>
#include <string.h>

#include "test.h"

static int	ft_strlen_test(const char *test_str)
{
	if (!test_str)
	{
		printf("TEST ERROR\n");
		return (0xFFFFFFFF);
	}
	return (test((ft_strlen(test_str) == strlen(test_str))));
}

void	test_ft_strlen()
{
	int		error_count = 0;

	printf(ORANGE"ft_strlen:\t"RESET);
	error_count += ft_strlen_test("");
	error_count += ft_strlen_test("Hello, world!");
	error_count += ft_strlen_test("Hello\0, world!");
	error_count += ft_strlen_test("\0\0\0\0");
	error_count += ft_strlen_test("\xe4\xbd\xa0\xe5\xa5\xbd\0");
	printf("\n");

	check_error_count(error_count);
}
