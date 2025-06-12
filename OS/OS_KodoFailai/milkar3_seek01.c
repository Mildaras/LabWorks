/* Mildaras Karvelis milkar3 */
/* Failas: milkar3_sablonas.c */
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

#define FILE_SIZE 1048576 // 1 MB

int main() {
	printf( "(C) 2023 Mildaras Karvelis, %s\n", __FILE__ );
    const char* filename = "output.txt";

    // Sukuriamas failas arba atidaromas esamas ir jei neegzistuoja
    // tai yra sukuriamas naujas.
    int file_fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (file_fd == -1) {
        perror("Failed to create/open file");
        return 1;
    }

    // Nueinama į 1 MB gilyn į failą
    if (lseek(file_fd, FILE_SIZE - 1, SEEK_SET) == -1) {
        perror("Failed to seek file");
        close(file_fd);
        return 1;
    }

    // Įrašomas 1 baitas
    char data = 'A';
    ssize_t bytes_written = write(file_fd, &data, sizeof(data));
    if (bytes_written == -1) {
        perror("Failed to write to file");
        close(file_fd);
        return 1;
    }

    // Uždaromas failas
    if (close(file_fd) == -1) {
        perror("Failed to close file");
        return 1;
    }

    return 0;
}
