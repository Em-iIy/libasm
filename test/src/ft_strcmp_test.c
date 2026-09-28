#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "test.h"

static int	ft_strcmp_test(const char *s1, const char *s2)
{
	if (!s1 || !s2)
	{
		printf("TEST ERROR\n");
		return (0xFFFFFFFF);
	}
	int	result_lib = strcmp(s1, s2);
	int	result_mine = ft_strcmp(s1, s2);
	if (result_lib != result_mine)
		printf("lib: %d, mine: %d\n", result_lib, result_mine);
	return (test(result_lib == result_mine));
}

void	test_ft_strcmp()
{
	int		error_count = 0;

	printf(ORANGE"ft_strcmp:\t"RESET);
	error_count += ft_strcmp_test("", "");
	error_count += ft_strcmp_test("Hello, world!", "Hello, world!");
	error_count += ft_strcmp_test("Hello\0, world!", "Hello\0, world!");
	error_count += ft_strcmp_test("\0\0\0\0", "\0\0\0\0");
	error_count += ft_strcmp_test("\xe4\xbd\xa0\xe5\xa5\xbd\0", "\xe4\xbd\xa0\xe5\xa5\xbd\0");
	error_count += ft_strcmp_test("1234", "12345");
	error_count += ft_strcmp_test("12345", "1234");
	error_count += ft_strcmp_test("1224", "1234");
	error_count += ft_strcmp_test("1234", "1224");
	error_count += ft_strcmp_test("1234", "");
	error_count += ft_strcmp_test("", "1234");
	printf("\n");

	check_error_count(error_count);
}
