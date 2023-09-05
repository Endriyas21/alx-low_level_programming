#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

/**
 * main - Copy the content of a file to another file.
 * @ac: The number of arguments.
 * @av: An array of arguments.
 *
 * Return: 0 on success, or the appropriate error code on failure.
 */
int main(int ac, char *av[])
{
    int fd_from, fd_to, rd, wr;
    char buffer[1024];

    if (ac != 3)
    {
        dprintf(2, "Usage: %s file_from file_to\n", av[0]);
        return (97);
    }

    fd_from = open(av[1], O_RDONLY);
    if (fd_from == -1)
    {
        dprintf(2, "Error: Can't read from file %s\n", av[1]);
        return (98);
    }

    fd_to = open(av[2], O_WRONLY | O_CREAT | O_TRUNC, 0664);
    if (fd_to == -1)
    {
        dprintf(2, "Error: Can't write to %s\n", av[2]);
        close(fd_from);
        return (99);
    }

    while ((rd = read(fd_from, buffer, 1024)) > 0)
    {
        wr = write(fd_to, buffer, rd);
        if (wr != rd)
        {
            dprintf(2, "Error: Can't write to %s\n", av[2]);
            close(fd_from);
            close(fd_to);
            return (99);
        }
    }

    if (rd == -1)
    {
        dprintf(2, "Error: Can't read from file %s\n", av[1]);
        close(fd_from);
        close(fd_to);
        return (98);
    }

    if (close(fd_from) == -1)
    {
        dprintf(2, "Error: Can't close fd %d\n", fd_from);
        return (100);
    }

    if (close(fd_to) == -1)
    {
        dprintf(2, "Error: Can't close fd %d\n", fd_to);
        return (100);
    }

    return (0);
}
