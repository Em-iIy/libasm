#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "test.h"

char *ft_strcpy(char *dest, const char *src);

static int	ft_strcpy_test(const char *src)
{
	if (!src)
	{
		printf("TEST ERROR\n");
		return (0xFFFFFFFF);
	}
	char *dest = (char *)malloc(strlen(src) + 1);
	if (!dest)
	{
		printf("TEST ERROR\n");
		return (0xFFFFFFFF);
	}

	char *temp_dest = ft_strcpy(dest, src);

	// strcpy returns dest, fail test if this isn't the case
	if (temp_dest != dest)
		return (test(false));

	// Check if ft_strcpy added the null terminator
	if (dest[strlen(dest)] != '\0')
		return (test(false));

	int	result = strcmp(src, dest);
	free(dest);
	return (test(result == 0));
}

void	test_ft_strcpy()
{
	int		error_count = 0;

	printf(ORANGE"ft_strcpy:\t"RESET);
	error_count += ft_strcpy_test("");
	error_count += ft_strcpy_test("Hello, world!");
	error_count += ft_strcpy_test("Hello\0, world!");
	error_count += ft_strcpy_test("\0\0\0\0");
	error_count += ft_strcpy_test("\xe4\xbd\xa0\xe5\xa5\xbd\0");
	printf("\n");

	check_error_count(error_count);
}
