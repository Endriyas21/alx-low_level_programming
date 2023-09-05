#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <elf.h>

void print_error(char *msg)
{
    dprintf(2, "%s\n", msg);
    exit(98);
}

void read_elf_header(int fd)
{
    Elf64_Ehdr header;
    ssize_t bytes_read;

    bytes_read = read(fd, &header, sizeof(header));
    if (bytes_read == -1)
        print_error("Error: Can't read from file");

    if (bytes_read != sizeof(header) || header.e_ident[EI_MAG0] != ELFMAG0 ||
        header.e_ident[EI_MAG1] != ELFMAG1 || header.e_ident[EI_MAG2] != ELFMAG2 ||
        header.e_ident[EI_MAG3] != ELFMAG3)
        print_error("Error: Not an ELF file");

    printf("ELF Header:\n");
    printf("  Magic:   ");
    for (int i = 0; i < EI_NIDENT; i++)
        printf("%02x%c", header.e_ident[i], i == EI_NIDENT - 1 ? '\n' : ' ');

    printf("  Class:                             ");
    switch (header.e_ident[EI_CLASS])
    {
    case ELFCLASS32:
        printf("ELF32\n");
        break;
    case ELFCLASS64:
        printf("ELF64\n");
        break;
    default:
        printf("<unknown>\n");
        break;
    }

    printf("  Data:                              ");
    switch (header.e_ident[EI_DATA])
    {
    case ELFDATA2LSB:
        printf("2's complement, little endian\n");
        break;
    case ELFDATA2MSB:
        printf("2's complement, big endian\n");
        break;
    default:
        printf("<unknown>\n");
        break;
    }

    printf("  Version:                           %d (current)\n", header.e_ident[EI_VERSION]);
    printf("  OS/ABI:                            %s\n", header.e_ident[EI_OSABI] == 0 ? "UNIX - System V" : "<unknown>");
    printf("  ABI Version:                       %d\n", header.e_ident[EI_ABIVERSION]);
    printf("  Type:                              ");
    switch (header.e_type)
    {
    case ET_NONE:
        printf("NONE (Unknown type)\n");
        break;
    case ET_REL:
        printf("REL (Relocatable file)\n");
        break;
    case ET_EXEC:
        printf("EXEC (Executable file)\n");
        break;
    case ET_DYN:
        printf("DYN (Shared object file)\n");
        break;
    case ET_CORE:
        printf("CORE (Core file)\n");
        break;
    default:
        printf("<unknown>\n");
        break;
    }

    printf("  Entry point address:               0x%lx\n", header.e_entry);
}

int main(int argc, char *argv[])
{
    int fd;

    if (argc != 2)
    {
        dprintf(2, "Usage: %s elf_filename\n", argv[0]);
        return (98);
    }

    fd = open(argv[1], O_RDONLY);
    if (fd == -1)
        print_error("Error: Can't read from file");

    read_elf_header(fd);

    close(fd);
    return (0);
}
