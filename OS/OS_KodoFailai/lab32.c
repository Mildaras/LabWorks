#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <signal.h>

#define FILE_SIZE 4096

void copy_file_contents(int source_fd, int destination_fd) {
    char buffer[1024];
    ssize_t bytes_read, bytes_written;

    while ((bytes_read = read(source_fd, buffer, sizeof(buffer))) > 0) {
        bytes_written = write(destination_fd, buffer, bytes_read);
        if (bytes_written == -1) {
            perror("Error writing to file");
            exit(EXIT_FAILURE);
        }
    }

    if (bytes_read == -1) {
        perror("Error reading from file");
        exit(EXIT_FAILURE);
    }
}

void handle_signal(int signal) {
    printf("Received signal %d. Exiting...\n", signal);
    exit(EXIT_SUCCESS);
}

int main(int argc, char *argv[]) {
	printf( "(C) 2023 Mildaras Karvelis, %s\n", __FILE__ );
    if (argc < 2 || argc > 3) {
        printf("Usage:\n");
        printf("  %s <filename>\n", argv[0]);
        printf("  %s <filename1> <filename2>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    if (argc == 2) {
        const char *file_path = argv[1];
        int file_fd;

        if (access(file_path, F_OK) == -1) {
            // File does not exist, create a new file with 4KB size
            file_fd = open(file_path, O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR);
            if (file_fd == -1) {
                perror("Error creating file");
                exit(EXIT_FAILURE);
            }

            if (ftruncate(file_fd, FILE_SIZE) == -1) {
                perror("Error truncating file");
                exit(EXIT_FAILURE);
            }

            printf("Created file '%s' with size 4KB.\n", file_path);
        } else {
            // File exists, modify the middle byte
            file_fd = open(file_path, O_RDWR);
            if (file_fd == -1) {
                perror("Error opening file");
                exit(EXIT_FAILURE);
            }

            off_t file_size = lseek(file_fd, 0, SEEK_END);
            if (file_size == -1) {
                perror("Error getting file size");
                exit(EXIT_FAILURE);
            }

            off_t middle_offset = file_size / 2;
            off_t middle_byte_offset = lseek(file_fd, middle_offset, SEEK_SET);
            if (middle_byte_offset == -1) {
                perror("Error seeking to middle byte");
                exit(EXIT_FAILURE);
            }

            unsigned char middle_byte;
            ssize_t bytes_read = read(file_fd, &middle_byte, sizeof(middle_byte));
            if (bytes_read == -1) {
                perror("Error reading middle byte");
                exit(EXIT_FAILURE);
            }

            if (file_size % 2 == 0) {
                // File size is even, increment the middle byte
                middle_byte++;
            } else {
                // File size is odd, replace the middle byte with 'S'
                middle_byte = 'S';
            }

            ssize_t bytes_written = pwrite(file_fd, &middle_byte, sizeof(middle_byte), middle_byte_offset);
            if (bytes_written == -1) {
                perror("Error writing middle byte");
                exit(EXIT_FAILURE);
            }

            printf("Modified middle byte in file '%s'.\n", file_path);
        }

        close(file_fd);
    } else {
        const char *file1_path = argv[1];
        const char *file2_path = argv[2];
        int file1_fd, file2_fd;

        // Set CPU time limit to 10 seconds
        struct rlimit cpu_limit;
        cpu_limit.rlim_cur = 5;
        cpu_limit.rlim_max = 5;
        if (setrlimit(RLIMIT_CPU, &cpu_limit) == -1) {
            perror("Error setting CPU time limit");
            exit(EXIT_FAILURE);
        }

        // Open file 1 for reading
        file1_fd = open(file1_path, O_RDONLY);
        if (file1_fd == -1) {
            perror("Error opening file 1");
            exit(EXIT_FAILURE);
        }

        // Open file 2 for reading and writing
        file2_fd = open(file2_path, O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
        if (file2_fd == -1) {
            perror("Error opening file 2");
            exit(EXIT_FAILURE);
        }

        // Map file 1 into memory for reading
        off_t file1_size = lseek(file1_fd, 0, SEEK_END);
        if (file1_size == -1) {
            perror("Error getting file 1 size");
            exit(EXIT_FAILURE);
        }

        void *file1_data = mmap(NULL, file1_size, PROT_READ, MAP_PRIVATE, file1_fd, 0);
        if (file1_data == MAP_FAILED) {
            perror("Error mapping file 1 into memory");
            exit(EXIT_FAILURE);
        }

        // Map file 2 into memory for reading and writing
        void *file2_data = mmap(NULL, file1_size, PROT_READ | PROT_WRITE, MAP_SHARED, file2_fd, 0);
        if (file2_data == MAP_FAILED) {
            perror("Error mapping file 2 into memory");
            exit(EXIT_FAILURE);
        }

        signal(SIGINT, handle_signal);  // Handle SIGINT signal (Ctrl+C)

        while (1) {
            if (memcmp(file1_data, file2_data, file1_size) != 0) {
                // File 1 contents changed, copy data from file 1 to file 2
                memcpy(file2_data, file1_data, file1_size);
                printf("File 2 contents updated.\n");
            }

            sleep(1);
        }

        munmap(file1_data, file1_size);
        munmap(file2_data, file1_size);
        close(file1_fd);
        close(file2_fd);
    }

    return 0;
}
