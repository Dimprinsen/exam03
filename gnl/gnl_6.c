#ifndef BUFFER_SIZE
# define BUFFER_SIZE 42
#endif

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

char    *get_next_line(int fd)
{
    static char buffer[BUFFER_SIZE];
    static int  bytes_read = 0;
    static int  buffer_index = 0;
    char    *line = NULL;
    char    *temp;
    int line_len = 0;

    if (fd < 0 || BUFFER_SIZE <= 0)
        return NULL;

    while (1)
    {
        if (buffer_index >= bytes_read)
        {
            bytes_read = read(fd, buffer, BUFFER_SIZE);
            if (bytes_read <= 0)
                break;
            buffer_index = 0;
        }
        temp = malloc(line_len + 2);
        if (!temp)
        {
            free(line);
            return NULL;
        }
        int i = 0;
        while (i < line_len)
        {
            temp[i] = line[i];
            i++;
        }
        temp[line_len] = buffer[buffer_index];
        temp[line_len + 1] = '\0';
        free (line);
        line = temp;
        line_len++;
        if (buffer_index[buffer] == '\n')
        {
            buffer_index++;
            return (line);
        }
        buffer_index++;
    }
    if (line_len == 0)
        return NULL;
    return (line);
}