/* Mildaras Karvelis milkar3 */
/* Failas: milkar3_sablonas.c */
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <aio.h>
#include <errno.h>

#define BUFFER_SIZE 1024
#define DATA_SIZE (1024 * 1024)

int main() {
	printf( "(C) 2023 Mildaras Karvelis, %s\n", __FILE__ );
    const char* file_path = "/dev/random";
    const char* output_file = "output.txt";
    char buffer[BUFFER_SIZE];
    struct aiocb aio;
    int output_fd;
    off_t offset = 0;
    ssize_t bytes_read = 0;
    ssize_t total_bytes_read = 0;

    // Atidaromas failas rašymui
    output_fd = open(output_file, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    if (output_fd == -1) {
        perror("Failed to open output file");
        return 1;
    }

    // Nuskaitoma 1MB duomenų iš /dev/random
    while (total_bytes_read < DATA_SIZE) {
        // Nustatomas aio kontrolinis blokas
        aio.aio_fildes = open(file_path, O_RDONLY);
        aio.aio_buf = buffer;
        aio.aio_nbytes = BUFFER_SIZE;
        aio.aio_offset = offset;

        // Pradedamas asinchroninis skaitymas
        if (aio_read(&aio) == -1) {
            perror("Failed to start asynchronous read");
            close(output_fd);
            return 1;
        }

        // Laukiama kol skaitymas baigsis
        while (aio_error(&aio) == EINPROGRESS);

        // Patikrinama ar skaitymas baigtas sėkmingai
        bytes_read = aio_return(&aio);
        if (bytes_read == -1) {
            perror("Failed to read from file");
            close(output_fd);
            return 1;
        }

        // Rašomi nuskaityti duomenys į išvesties failą
        if (write(output_fd, buffer, bytes_read) == -1) {
            perror("Failed to write to output file");
            close(output_fd);
            return 1;
        }

        // Atnaujinamas visų nuskaitytų baitų skaičius
        total_bytes_read += bytes_read;

        // Padidinamas skaitymo offsetas
        offset += bytes_read;

        // Uždaromas pradinio failo deskriptorius
        close(aio.aio_fildes);
    }

    // Uždaromas išvesties failo deskriptorius
    if (close(output_fd) == -1) {
        perror("Failed to close output file");
        return 1;
    }

    return 0;
}
