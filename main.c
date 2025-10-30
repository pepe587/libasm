#include <stdio.h>
#include <unistd.h>

//size_t ft_strlen(const char *s);
//int    ft_strcmp(const char *s1, const char *s2);
//char *ft_strcpy(const char *dest, const char *src);
int ft_write(int fd, const void *buf, size_t count);
int ft_read(int fd, void *buf, size_t count);

int main() {

    char buffer[100];
    ssize_t bytes_read;

    bytes_read = ft_read(0, buffer, 100);
    printf("Test for read: %s", buffer);
}