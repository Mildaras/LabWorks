/* Mildaras Karvelis milkar3 */
/* Failas: milkar3_sablonas.c */
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFFER_SIZE 4096

int main(int argc, char* argv[]) {
	printf( "(C) 2023 Mildaras Karvelis, %s\n", __FILE__ );
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <source_file> <destination_file>\n", argv[0]);
        return 1;
    }

    const char* source_file = argv[1];
    const char* destination_file = argv[2];

    // Open the source file for reading
    int source_fd = open(source_file, O_RDONLY);
    if (source_fd == -1) {
        perror("Failed to open source file");
        return 1;
    }

    // Open the destination file for writing, create it if it doesn't exist, and truncate its contents if it exists
    int destination_fd = open(destination_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (destination_fd == -1) {
        perror("Failed to open destination file");
        close(source_fd);
        return 1;
    }

    // Copy data from the source file to the destination file
    char buffer[BUFFER_SIZE];
    ssize_t bytes_read, bytes_written;
    while ((bytes_read = read(source_fd, buffer, sizeof(buffer))) > 0) {
        bytes_written = write(destination_fd, buffer, bytes_read);
        if (bytes_written != bytes_read) {
            perror("Failed to write to destination file");
            close(source_fd);
            close(destination_fd);
            return 1;
        }
    }

    if (bytes_read == -1) {
        perror("Failed to read from source file");
        close(source_fd);
        close(destination_fd);
        return 1;
    }

    // Close the files
    if (close(source_fd) == -1) {
        perror("Failed to close source file");
        return 1;
    }

    if (close(destination_fd) == -1) {
        perror("Failed to close destination file");
        return 1;
    }

    return 0;
}
