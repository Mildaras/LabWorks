/* Mildaras Karvelis milkar3 */
/* Failas: milkar3_sablonas.c */
#define _XOPEN_SOURCE 500
#include <ftw.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int display_file(const char* filepath, const struct stat* filestat, int filetype, struct FTW* ftwbuf) {
    if (filetype == FTW_F) {
        printf("File: %s\n", filepath);
    }
    return 0;
}

int main(int argc, char* argv[]) {
	printf( "(C) 2023 Mildaras Karvelis, %s\n", __FILE__ );
    const char* home_directory = getenv("HOME");
    if (home_directory == NULL) {
        fprintf(stderr, "Error: Could not get home directory.\n");
        return 1;
    }

    int flags = FTW_PHYS;
    int result = nftw(home_directory, display_file, 10, flags);
    if (result == -1) {
        fprintf(stderr, "Error: Failed to traverse directory.\n");
        return 1;
    }

    return 0;
}
