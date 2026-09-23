#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "test.h"

char *ft_strdup(const char *str);

static int	ft_strdup_test(const char *str)
{
	if (!str)
	{
		printf("TEST ERROR\n");
		return (0xFFFFFFFF);
	}
	char *lib_str = strdup(str);
	char *my_str = ft_strdup(str);
	bool	result = strcmp(lib_str, my_str);
	free(lib_str);
	free(my_str);
	return (test((result == 0)));
}

void	test_ft_strdup()
{
	int		error_count = 0;

	printf(ORANGE"ft_strdup:\t"RESET);
	error_count += ft_strdup_test("");
	error_count += ft_strdup_test("Hello, world!");
	error_count += ft_strdup_test("Hello\0, world!");
	error_count += ft_strdup_test("\0\0\0\0");
	error_count += ft_strdup_test("\xe4\xbd\xa0\xe5\xa5\xbd\0");
	printf("\n");

	check_error_count(error_count);
}
