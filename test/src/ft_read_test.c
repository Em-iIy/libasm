#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "test.h"

#define TEST_FILE_NAME "temp"

ssize_t ft_read(int fd, void *buf, size_t count);

static int	ft_read_test_more_than_file_size()
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
	if (write(fd, contents, len) < 0)
	{
		perror("write");
		printf("TEST ERROR\n");
		unlink(TEST_FILE_NAME);
		close(fd);
		return (0xFFFFFFFF);
	}
	lseek(fd, 0, SEEK_SET);
	int lib_bytes_read = read(fd, lib_buf, len + 10);
	if (lib_bytes_read < 0)
	{
		perror("read");
		printf("TEST ERROR\n");
		unlink(TEST_FILE_NAME);
		close(fd);
		return (0xFFFFFFFF);
	}
	lib_buf[lib_bytes_read] = '\0';
	lseek(fd, 0, SEEK_SET);
	int my_bytes_read = ft_read(fd, my_buf, len + 10);
	if (my_bytes_read < 0)
	{
		perror("ft_read");
		unlink(TEST_FILE_NAME);
		close(fd);
		return (test(false));
	}
	my_buf[my_bytes_read] = '\0';
	unlink(TEST_FILE_NAME);
	close(fd);
	if (my_bytes_read != lib_bytes_read)
	{
		printf("my bytes: <%d> lib bytes: <%d>\n", my_bytes_read, lib_bytes_read);
		printf("bytes error\n");
		return (test(false));
	}
	return (test(strcmp(my_buf, lib_buf) == 0));
}

static int	ft_read_test_less_than_file_size()
{
	const char *contents = "123456789123456789";
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
	if (write(fd, contents, len) < 0)
	{
		perror("write");
		printf("TEST ERROR\n");
		unlink(TEST_FILE_NAME);
		close(fd);
		return (0xFFFFFFFF);
	}
	lseek(fd, 0, SEEK_SET);
	int lib_bytes_read = read(fd, lib_buf, len - 10);
	if (lib_bytes_read < 0)
	{
		perror("read");
		printf("TEST ERROR\n");
		unlink(TEST_FILE_NAME);
		close(fd);
		return (0xFFFFFFFF);
	}
	lib_buf[lib_bytes_read] = '\0';
	lseek(fd, 0, SEEK_SET);
	int my_bytes_read = ft_read(fd, my_buf, len - 10);
	if (my_bytes_read < 0)
	{
		perror("ft_read");
		unlink(TEST_FILE_NAME);
		close(fd);
		return (test(false));
	}
	my_buf[my_bytes_read] = '\0';
	unlink(TEST_FILE_NAME);
	close(fd);
	if (my_bytes_read != lib_bytes_read)
	{
		printf("my bytes: <%d> lib bytes: <%d>\n", my_bytes_read, lib_bytes_read);
		printf("bytes error\n");
		return (test(false));
	}
	return (test(strcmp(my_buf, lib_buf) == 0));
}

static int	ft_read_test_empty_file()
{
	const char *contents = "";
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
	if (write(fd, contents, len) < 0)
	{
		perror("write");
		printf("TEST ERROR\n");
		unlink(TEST_FILE_NAME);
		close(fd);
		return (0xFFFFFFFF);
	}
	lseek(fd, 0, SEEK_SET);
	int lib_bytes_read = read(fd, lib_buf, len);
	if (lib_bytes_read < 0)
	{
		perror("read");
		printf("TEST ERROR\n");
		unlink(TEST_FILE_NAME);
		close(fd);
		return (0xFFFFFFFF);
	}
	lib_buf[lib_bytes_read] = '\0';
	lseek(fd, 0, SEEK_SET);
	int my_bytes_read = ft_read(fd, my_buf, len);
	if (my_bytes_read < 0)
	{
		perror("ft_read");
		unlink(TEST_FILE_NAME);
		close(fd);
		return (test(false));
	}
	my_buf[my_bytes_read] = '\0';
	unlink(TEST_FILE_NAME);
	close(fd);
	if (my_bytes_read != lib_bytes_read)
	{
		printf("my bytes: <%d> lib bytes: <%d>\n", my_bytes_read, lib_bytes_read);
		printf("bytes error\n");
		return (test(false));
	}
	return (test(strcmp(my_buf, lib_buf) == 0));
}

static int	ft_read_test_EBADF()
{
	const int	len = 1;
	char my_buf[1024];
	char lib_buf[1024];
	int my_errno;
	int lib_errno;
	int fd = 1024; // invalid file descriptor
	int lib_bytes_read = read(fd, lib_buf, len);
	if (lib_bytes_read >= 0)
	{
		printf("TEST ERROR\n");
		return (0xFFFFFFFF);
	}
	lib_errno = errno;
	int my_bytes_read = ft_read(fd, my_buf, len);
	if (my_bytes_read >= 0)
	{
		perror("ft_read");
		return (test(false));
	}
	my_errno = errno;
	if (my_bytes_read != lib_bytes_read)
	{
		printf("my bytes: <%d> lib bytes: <%d>\n", my_bytes_read, lib_bytes_read);
		printf("bytes error\n");
		return (test(false));
	}
	return (test(lib_errno == my_errno));
}

static int	ft_read_test_EISDIR()
{
	const int	len = 1;
	char my_buf[1024];
	char lib_buf[1024];
	int my_errno;
	int lib_errno;
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
	int lib_bytes_read = read(fd, lib_buf, len);
	if (lib_bytes_read >= 0)
	{
		printf("TEST ERROR\n");
		rmdir(TEST_FILE_NAME);
		close(fd);
		return (0xFFFFFFFF);
	}
	lib_errno = errno;
	int my_bytes_read = ft_read(fd, my_buf, len);
	if (my_bytes_read >= 0)
	{
		perror("ft_read");
		rmdir(TEST_FILE_NAME);
		close(fd);
		return (test(false));
	}
	my_errno = errno;
	if (my_bytes_read != lib_bytes_read)
	{
		printf("my bytes: <%d> lib bytes: <%d>\n", my_bytes_read, lib_bytes_read);
		printf("bytes error\n");
		rmdir(TEST_FILE_NAME);
		close(fd);
		return (test(false));
	}
	rmdir(TEST_FILE_NAME);
	close(fd);
	return (test(lib_errno == my_errno));
}

static int	ft_read_test_PERMS()
{
	const int	len = 1;
	char my_buf[1024];
	char lib_buf[1024];
	int my_errno;
	int lib_errno;
	int fd = open(TEST_FILE_NAME, O_WRONLY | O_CREAT);
	if (fd < 0)
	{
		perror("open");
		printf("TEST ERROR\n");
		return (0xFFFFFFFF);
	}
	int lib_bytes_read = read(fd, lib_buf, len);
	if (lib_bytes_read >= 0)
	{
		printf("TEST ERROR\n");
		unlink(TEST_FILE_NAME);
		close(fd);
		return (0xFFFFFFFF);
	}
	lib_errno = errno;
	int my_bytes_read = ft_read(fd, my_buf, len);
	if (my_bytes_read >= 0)
	{
		printf("errno error\n");
		unlink(TEST_FILE_NAME);
		close(fd);
		return (test(false));
	}
	my_errno = errno;
	if (my_bytes_read != lib_bytes_read)
	{
		printf("my bytes: <%d> lib bytes: <%d>\n", my_bytes_read, lib_bytes_read);
		printf("bytes error\n");
		unlink(TEST_FILE_NAME);
		close(fd);
		return (test(false));
	}
	unlink(TEST_FILE_NAME);
	close(fd);
	return (test(lib_errno == my_errno));
}

void	test_ft_read()
{
	int		error_count = 0;

	printf(ORANGE"ft_read:\t"RESET);
	error_count += ft_read_test_more_than_file_size();
	error_count += ft_read_test_less_than_file_size();
	error_count += ft_read_test_empty_file();
	error_count += ft_read_test_EBADF();
	error_count += ft_read_test_EISDIR();
	error_count += ft_read_test_PERMS();

	printf("\n");

	check_error_count(error_count);
}
