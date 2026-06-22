#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

size_t	ft_strlen(const char *s);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strcpy(char *dest, const char *src);
int		ft_write(int fd, const void *buf, size_t count);
int		ft_read(int fd, void *buf, size_t count);
char	*ft_strdup(const char *s);

#define OK   "\033[32m[OK]\033[0m"
#define KO   "\033[31m[KO]\033[0m"
#define HDR  "\033[1;34m"
#define RST  "\033[0m"

#define CHECK(cond) ((cond) ? OK : KO)
#define SIGN(n)     ((n) < 0 ? -1 : (n) > 0 ? 1 : 0)

static void header(const char *name)
{
	printf("\n" HDR "=== %s ===" RST "\n", name);
}

static void test_strlen(void)
{
	header("ft_strlen");
	printf("%s  \"hello\"        ft=%zu  libc=%zu\n",
		CHECK(ft_strlen("hello") == strlen("hello")),
		ft_strlen("hello"), strlen("hello"));
	printf("%s  \"\"             ft=%zu  libc=%zu\n",
		CHECK(ft_strlen("") == strlen("")),
		ft_strlen(""), strlen(""));
	printf("%s  \"a\"            ft=%zu  libc=%zu\n",
		CHECK(ft_strlen("a") == strlen("a")),
		ft_strlen("a"), strlen("a"));
	printf("%s  \"hello world\"  ft=%zu  libc=%zu\n",
		CHECK(ft_strlen("hello world") == strlen("hello world")),
		ft_strlen("hello world"), strlen("hello world"));
}

static void test_strcmp(void)
{
	header("ft_strcmp");
	printf("%s  \"abc\" vs \"abc\"  ft=%d  libc=%d  (equal)\n",
		CHECK(SIGN(ft_strcmp("abc", "abc")) == SIGN(strcmp("abc", "abc"))),
		ft_strcmp("abc", "abc"), strcmp("abc", "abc"));
	printf("%s  \"abc\" vs \"abd\"  ft=%d  libc=%d  (s1 < s2)\n",
		CHECK(SIGN(ft_strcmp("abc", "abd")) == SIGN(strcmp("abc", "abd"))),
		ft_strcmp("abc", "abd"), strcmp("abc", "abd"));
	printf("%s  \"abd\" vs \"abc\"  ft=%d  libc=%d  (s1 > s2)\n",
		CHECK(SIGN(ft_strcmp("abd", "abc")) == SIGN(strcmp("abd", "abc"))),
		ft_strcmp("abd", "abc"), strcmp("abd", "abc"));
	printf("%s  \"\" vs \"\"        ft=%d  libc=%d  (both empty)\n",
		CHECK(SIGN(ft_strcmp("", "")) == SIGN(strcmp("", ""))),
		ft_strcmp("", ""), strcmp("", ""));
	printf("%s  \"a\" vs \"\"       ft=%d  libc=%d  (s2 empty)\n",
		CHECK(SIGN(ft_strcmp("a", "")) == SIGN(strcmp("a", ""))),
		ft_strcmp("a", ""), strcmp("a", ""));
	printf("%s  \"\" vs \"a\"       ft=%d  libc=%d  (s1 empty)\n",
		CHECK(SIGN(ft_strcmp("", "a")) == SIGN(strcmp("", "a"))),
		ft_strcmp("", "a"), strcmp("", "a"));
}

static void test_strcpy(void)
{
	header("ft_strcpy");
	char dst1[64];
	char dst2[64];

	char *ret = ft_strcpy(dst1, "hello");
	strcpy(dst2, "hello");
	printf("%s  content match      dst=\"%s\"\n", CHECK(strcmp(dst1, dst2) == 0), dst1);
	printf("%s  returns dst ptr    ret==%s\n", CHECK(ret == dst1), ret == dst1 ? "dst" : "other");

	ft_strcpy(dst1, "");
	strcpy(dst2, "");
	printf("%s  empty string       dst=\"%s\"\n", CHECK(strcmp(dst1, dst2) == 0), dst1);

	ft_strcpy(dst1, "a");
	strcpy(dst2, "a");
	printf("%s  single char        dst=\"%s\"\n", CHECK(strcmp(dst1, dst2) == 0), dst1);
}

static void test_write(void)
{
	header("ft_write");

	const char *msg = "ft_write printing this line\n";
	ssize_t ret = ft_write(1, msg, strlen(msg));
	printf("%s  success: returned %zd (expected %zu)\n",
		CHECK(ret == (ssize_t)strlen(msg)), ret, strlen(msg));

	errno = 0;
	ret = ft_write(-1, msg, strlen(msg));
	int saved = errno;
	printf("%s  bad fd: returned %zd  errno=%d (%s)\n",
		CHECK(ret == -1 && saved == EBADF), ret, saved, strerror(saved));
}

static void test_read(void)
{
	header("ft_read");

	int fds[2];
	char buf[32];
	const char *msg = "hello read";

	pipe(fds);
	write(fds[1], msg, strlen(msg));
	close(fds[1]);

	ssize_t ret = ft_read(fds[0], buf, strlen(msg));
	buf[ret > 0 ? ret : 0] = '\0';
	close(fds[0]);
	printf("%s  success: returned %zd  buffer=\"%s\"\n",
		CHECK(ret == (ssize_t)strlen(msg) && strcmp(buf, msg) == 0), ret, buf);

	errno = 0;
	ret = ft_read(-1, buf, sizeof(buf));
	int saved = errno;
	printf("%s  bad fd: returned %zd  errno=%d (%s)\n",
		CHECK(ret == -1 && saved == EBADF), ret, saved, strerror(saved));
}

static void test_strdup(void)
{
	header("ft_strdup");

	const char *src = "hello strdup";
	char *dup = ft_strdup(src);
	printf("%s  content match    dup=\"%s\"\n",
		CHECK(dup && strcmp(dup, src) == 0), dup ? dup : "(null)");
	printf("%s  different ptr    dup!=%s\n",
		CHECK(dup != src), dup != src ? "src" : "same!");
	free(dup);

	dup = ft_strdup("");
	printf("%s  empty string     dup=\"%s\"\n",
		CHECK(dup && strcmp(dup, "") == 0), dup ? dup : "(null)");
	free(dup);

	dup = ft_strdup("a");
	printf("%s  single char      dup=\"%s\"\n",
		CHECK(dup && strcmp(dup, "a") == 0), dup ? dup : "(null)");
	free(dup);
}

int main(void)
{
	test_strlen();
	test_strcmp();
	test_strcpy();
	test_write();
	test_read();
	test_strdup();
	printf("\n");
	return 0;
}
