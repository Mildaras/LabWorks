/* Mildaras Karvelis milkar3 */
/* Failas: milkar3_sablonas.c */
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

#define MAX_FILE_SIZE 100 * 1024 * 1024 // 100MB

int main(int argc, char *argv[]) {
	printf( "(C) 2023 Mildaras Karvelis, %s\n", __FILE__ );
    if (argc < 3) {
        printf("Usage: %s <source_file> <destination_file>\n", argv[0]);
        return 1;
    }

    const char *source_file = argv[1];
    const char *destination_file = argv[2];

    // Atidaro šaltinio failą tik skaitymui
    int source_fd = open(source_file, O_RDONLY);
    if (source_fd == -1) {
        perror("Failed to open source file");
        return 1;
    }

    // Nuskaito šaltinio failo dydį su fstat()
    struct stat source_stat;
    if (fstat(source_fd, &source_stat) == -1) {
        perror("Failed to get source file size");
        close(source_fd);
        return 1;
    }
    off_t source_size = source_stat.st_size;

    // Patikrina, ar šaltinio failo dydis tinkamas
    if (source_size > MAX_FILE_SIZE) {
        printf("Source file size exceeds the limit of %d bytes\n", MAX_FILE_SIZE);
        close(source_fd);
        return 1;
    }

    // Atidaro paskirties failą tik rašymui
    int dest_fd = open(destination_file, O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    if (dest_fd == -1) {
        perror("Failed to open destination file");
        close(source_fd);
        return 1;
    }

    // Išplėčia paskirties failo dydį iki šaltinio failo dydžio
    if (ftruncate(dest_fd, source_size) == -1) {
        perror("Failed to resize destination file");
        close(source_fd);
        close(dest_fd);
        return 1;
    }

    // Atlieka pirmo failo mmap() skaitymui
    void *source_data = mmap(NULL, source_size, PROT_READ, MAP_SHARED, source_fd, 0);
    if (source_data == MAP_FAILED) {
        perror("Failed to mmap source file");
        close(source_fd);
        close(dest_fd);
        return 1;
    }

    // Atlieka antro failo mmap() rašymui
    void *dest_data = mmap(NULL, source_size, PROT_WRITE, MAP_SHARED, dest_fd, 0);
    if (dest_data == MAP_FAILED) {
        perror("Failed to mmap destination file");
        munmap(source_data, source_size);
        close(source_fd);
        close(dest_fd);
        return 1;
    }

    // Kopijuoja duomenis iš šaltinio į paskirties failą
    memcpy(dest_data, source_data, source_size);

    // Atjungia abu mmap() atvaizdus
    if (munmap(source_data, source_size) == -1) {
        perror("Failed to unmap source file");
    }
    if (munmap(dest_data, source_size) == -1) {
        perror("Failed to unmap destination file");
    }

    // Uždaro deskriptorius
    close(source_fd);
    close(dest_fd);

    printf("File copied successfully.\n");

    return 0;
}
