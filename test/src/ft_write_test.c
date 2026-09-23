#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "test.h"

#define TEST_FILE_NAME "temp"

ssize_t ft_write(int fd, const void *buf, size_t count);

/*
open file
write to file
save:
	bytes written
	contents
delete file
*/

ssize_t write_test_wrapper(ssize_t (*write_func)(int, const void *, size_t), int fd, const void *buf, size_t count, char out_buf[1024])
{
	lseek(fd, 0, SEEK_SET);
	ssize_t bytes_written = write_func(fd, buf, count);
	if (bytes_written < 0)
	{
		unlink(TEST_FILE_NAME);
		close(fd);
		return (bytes_written);
	}
	lseek(fd, 0, SEEK_SET);
	ssize_t bytes_read = read(fd, out_buf, 1024);
	out_buf[bytes_read] = '\0';
	if (bytes_read != bytes_written)
	{
		unlink(TEST_FILE_NAME);
		close(fd);
		printf("bytes written/read error");
		return (bytes_written);
	}
	lseek(fd, 0, SEEK_SET);
	return (bytes_written);
}

static int	ft_write_test_normal_string()
{
	const char *contents = "123456789blablabla1234123412341234\xe4\xbd\xa0\xe5\xa5\xbd\0\xe4\xbd\xa0\xe5\xa5\xbd\0\n\n\n\n\n\n\n\n\n\n\n\n\t\xe4\xbd\xa0\xe5\xa5\xbd\0bla123443213.1415926535hihihihihihihihihibyebyebyebyebye\n\n\n\xe4\xbd\xa0\xe5\xa5\xbd\0";
	const int	len = strlen(contents);
	char my_buf[1024];
	char lib_buf[1024];
	int fd = open(TEST_FILE_NAME,  O_RDWR | O_CREAT);
	if (fd < 0)
	{
		perror("open");
		printf("TEST ERROR\n");
		return (0xFFFFFFFF);
	}
	ssize_t	my_bytes_written = write_test_wrapper(ft_write, fd, contents, len, my_buf);
	if (my_bytes_written < 0)
	{
		perror("ft_write");
		return (test(false));
	}
	unlink(TEST_FILE_NAME);
	close(fd);
	fd = open(TEST_FILE_NAME,  O_RDWR | O_CREAT);
	if (fd < 0)
	{
		perror("open");
		printf("TEST ERROR\n");
		return (0xFFFFFFFF);
	}
	ssize_t	lib_bytes_written = write_test_wrapper(write, fd, contents, len, lib_buf);
	if (lib_bytes_written < 0)
	{
		perror("write");
		printf("TEST ERROR\n");
		return (0xFFFFFFFF);
	}
	unlink(TEST_FILE_NAME);
	close(fd);
	if (my_bytes_written != lib_bytes_written)
	{
		printf("my bytes: <%zd> lib bytes: <%zd>\n", my_bytes_written, lib_bytes_written);
		printf("bytes error\n");
		return (test(false));
	}
	return (test(strcmp(my_buf, lib_buf) == 0));
}

static int	ft_write_test_more_than_buf_size()
{
	const char *contents = "123456789";
	const int	len = strlen(contents);
	char my_buf[1024];
	char lib_buf[1024];
	int fd = open(TEST_FILE_NAME,  O_RDWR | O_CREAT);
	if (fd < 0)
	{
		perror("open");
		printf("TEST ERROR\n");
		return (0xFFFFFFFF);
	}
	ssize_t	my_bytes_written = write_test_wrapper(ft_write, fd, contents, len + 10, my_buf);
	if (my_bytes_written < 0)
	{
		perror("ft_write");
		return (test(false));
	}
	unlink(TEST_FILE_NAME);
	close(fd);
	fd = open(TEST_FILE_NAME,  O_RDWR | O_CREAT);
	if (fd < 0)
	{
		perror("open");
		printf("TEST ERROR\n");
		return (0xFFFFFFFF);
	}
	ssize_t	lib_bytes_written = write_test_wrapper(write, fd, contents, len + 10, lib_buf);
	if (lib_bytes_written < 0)
	{
		perror("write");
		printf("TEST ERROR\n");
		return (0xFFFFFFFF);
	}
	unlink(TEST_FILE_NAME);
	close(fd);
	if (my_bytes_written != lib_bytes_written)
	{
		printf("my bytes: <%zd> lib bytes: <%zd>\n", my_bytes_written, lib_bytes_written);
		printf("bytes error\n");
		return (test(false));
	}
	return (test(strcmp(my_buf, lib_buf) == 0));
}

static int	ft_write_test_less_than_buf_size()
{
	const char *contents = "123456789";
	const int	len = strlen(contents);
	char my_buf[1024];
	char lib_buf[1024];
	int fd = open(TEST_FILE_NAME,  O_RDWR | O_CREAT);
	if (fd < 0)
	{
		perror("open");
		printf("TEST ERROR\n");
		return (0xFFFFFFFF);
	}
	ssize_t	my_bytes_written = write_test_wrapper(ft_write, fd, contents, len - 5, my_buf);
	if (my_bytes_written < 0)
	{
		perror("ft_write");
		unlink(TEST_FILE_NAME);
		close(fd);
		return (test(false));
	}
	unlink(TEST_FILE_NAME);
	close(fd);
	fd = open(TEST_FILE_NAME,  O_RDWR | O_CREAT);
	if (fd < 0)
	{
		perror("open");
		printf("TEST ERROR\n");
		return (0xFFFFFFFF);
	}
	ssize_t	lib_bytes_written = write_test_wrapper(write, fd, contents, len - 5, lib_buf);
	if (lib_bytes_written < 0)
	{
		perror("write");
		printf("TEST ERROR\n");
		unlink(TEST_FILE_NAME);
		close(fd);
		return (0xFFFFFFFF);
	}
	unlink(TEST_FILE_NAME);
	close(fd);
	if (my_bytes_written != lib_bytes_written)
	{
		printf("my bytes: <%zd> lib bytes: <%zd>\n", my_bytes_written, lib_bytes_written);
		printf("bytes error\n");
		return (test(false));
	}
	return (test(strcmp(my_buf, lib_buf) == 0));
}

static int	ft_write_test_EBADF()
{
	const char *contents = "123456789";
	const int	len = strlen(contents);
	char buf[1024];
	int fd = 1024;
	int my_errno;
	int lib_errno;
	ssize_t	my_bytes_written = ft_write(fd, contents, len);
	my_errno = errno;
	if (my_bytes_written >= 0)
	{
		perror("ft_write");
		return (test(false));
	}
	unlink(TEST_FILE_NAME);
	close(fd);
	if (fd < 0)
	{
		perror("open");
		printf("TEST ERROR\n");
		return (0xFFFFFFFF);
	}
	ssize_t	lib_bytes_written = write(fd, contents, len);
	lib_errno = errno;
	if (lib_bytes_written >= 0)
	{
		printf("TEST ERROR\n");
		return (0xFFFFFFFF);
	}
	unlink(TEST_FILE_NAME);
	close(fd);
	if (my_bytes_written != lib_bytes_written)
	{
		printf("my bytes: <%zd> lib bytes: <%zd>\n", my_bytes_written, lib_bytes_written);
		printf("bytes error\n");
		return (test(false));
	}
	
	return (test(lib_errno == my_errno));
}

static int	ft_write_test_DIRECTORY()
{
	const char *contents = "123456789";
	const int	len = strlen(contents);
	char buf[1024];
	mkdir(TEST_FILE_NAME, 0777);
	int fd = open(TEST_FILE_NAME, O_RDONLY);
	if (fd < 0)
	{
		perror("open");
		printf("TEST ERROR\n");
		rmdir(TEST_FILE_NAME);
		close(fd);
		return (0xFFFFFFFF);
	}
	int my_errno;
	int lib_errno;
	ssize_t	my_bytes_written = ft_write(fd, contents, len);
	my_errno = errno;
	if (my_bytes_written >= 0)
	{
		perror("ft_write");
		rmdir(TEST_FILE_NAME);
		close(fd);
		return (test(false));
	}
	unlink(TEST_FILE_NAME);
	close(fd);
	if (fd < 0)
	{
		perror("open");
		printf("TEST ERROR\n");
		rmdir(TEST_FILE_NAME);
		close(fd);
		return (0xFFFFFFFF);
	}
	ssize_t	lib_bytes_written = write(fd, contents, len);
	lib_errno = errno;
	if (lib_bytes_written >= 0)
	{
		printf("TEST ERROR\n");
		rmdir(TEST_FILE_NAME);
		close(fd);
		return (0xFFFFFFFF);
	}
	if (my_bytes_written != lib_bytes_written)
	{
		printf("my bytes: <%zd> lib bytes: <%zd>\n", my_bytes_written, lib_bytes_written);
		printf("bytes error\n");
		return (test(false));
	}
	rmdir(TEST_FILE_NAME);
	close(fd);
	return (test(lib_errno == my_errno));
}

void	test_ft_write()
{
	int		error_count = 0;

	printf(ORANGE"ft_write:\t"RESET);
	error_count += ft_write_test_normal_string();
	error_count += ft_write_test_more_than_buf_size();
	error_count += ft_write_test_less_than_buf_size();
	error_count += ft_write_test_EBADF();
	error_count += ft_write_test_DIRECTORY();

	printf("\n");

	check_error_count(error_count);
}
