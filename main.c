#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

size_t ft_strlen(const char *s);
int ft_strcmp(const char *s1, const char *s2);
char *ft_strcpy(char *dest, const char *src);
int ft_write(int fd, const void *buf, size_t count);
int ft_read(int fd, void *buf, size_t count);

static void test_strlen(void)
{
	const char *text = "hola libasm";

	printf("ft_strlen(\"%s\") = %zu | strlen = %zu\n",
		text, ft_strlen(text), strlen(text));
}

static void test_strcmp(void)
{
	const char *a = "abc";
	const char *b = "abd";

	printf("ft_strcmp(\"%s\", \"%s\") = %d | strcmp = %d\n",
		a, b, ft_strcmp(a, b), strcmp(a, b));
	printf("ft_strcmp(\"%s\", \"%s\") = %d | strcmp = %d\n",
		a, a, ft_strcmp(a, a), strcmp(a, a));
}

static void test_strcpy(void)
{
	char dest[64];
	char expected[64];
	const char *src = "copied text";

	printf("ft_strcpy result: %s\n", ft_strcpy(dest, src));
	printf("libc strcpy result: %s\n", strcpy(expected, src));
	printf("dest == expected: %s\n", strcmp(dest, expected) == 0 ? "yes" : "no");
}

static void test_write(void)
{
	const char *msg = "ft_write OK\n";

	errno = 0;
	printf("ft_write success returned: %d\n", ft_write(1, msg, strlen(msg)));

	errno = 0;
	printf("ft_write error returned: %d, errno = %d (%s)\n",
		ft_write(-1, msg, strlen(msg)), errno, strerror(errno));
}

static void test_read(void)
{
	int fd[2];
	char buffer[32];
	const char *msg = "read test";

	if (pipe(fd) == -1)
	{
		perror("pipe");
		return;
	}
	write(fd[1], msg, strlen(msg));
	close(fd[1]);

	errno = 0;
	buffer[0] = '\0';
	printf("ft_read success returned: %d, buffer = \"%s\"\n",
		ft_read(fd[0], buffer, sizeof(buffer) - 1), buffer);
	close(fd[0]);

	errno = 0;
	printf("ft_read error returned: %d, errno = %d (%s)\n",
		ft_read(-1, buffer, sizeof(buffer)), errno, strerror(errno));
}

int main(void)
{
	test_strlen();
	test_strcmp();
	test_strcpy();
	test_write();
	test_read();
	return 0;
}