/* Mildaras Karvelis milkar3 */
/* Failas: milkar3_sablonas.c */
#include <stdio.h>

int main() {
	printf( "(C) 2023 Mildaras Karvelis, %s\n", __FILE__ );
    const char* read_filename = "input.txt";
    const char* write_filename = "output.txt";

    // Atidaromas failas skaitymui
    FILE* read_file = fopen(read_filename, "rb");
    if (read_file == NULL) {
        perror("Failed to open read file");
        return 1;
    }

    // Atidaromas failas rašymui
    FILE* write_file = fopen(write_filename, "wb");
    if (write_file == NULL) {
        perror("Failed to open write file");
        fclose(read_file);
        return 1;
    }

    // Nuskaitomas ir rašomas failo turinys
    char buffer[1024];
    size_t bytes_read;
    while ((bytes_read = fread(buffer, 1, sizeof(buffer), read_file)) > 0) {
        size_t bytes_written = fwrite(buffer, 1, bytes_read, write_file);
        if (bytes_written != bytes_read) {
            perror("Failed to write to file");
            fclose(read_file);
            fclose(write_file);
            return 1;
        }
    }

    // Uždaromi failai
    if (fclose(read_file) != 0) {
        perror("Failed to close read file");
        return 1;
    }
    if (fclose(write_file) != 0) {
        perror("Failed to close write file");
        return 1;
    }

    return 0;
}
