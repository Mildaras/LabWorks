/* Mildaras Karvelis milkar3 */
/* Failas: milkar3_sablonas.c */
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

void print_file_info(const char *path) {
    struct stat file_info;

    // Gauti informaciją apie failą
    if (stat(path, &file_info) == -1) {
        perror("Klaida gaudant failo informaciją");
        return;
    }

    // Išvesti informaciją į ekraną
    printf("Failo informacija:\n");
    printf("Savininko ID: %d\n", file_info.st_uid);
    printf("Dydis: %ld baitai\n", file_info.st_size);
    printf("I-node numeris: %ld\n", file_info.st_ino);
    printf("Leidimai: %o\n", file_info.st_mode);
    printf("Failo tipas: ");

    if (S_ISREG(file_info.st_mode))
        printf("Failas\n");
    else if (S_ISDIR(file_info.st_mode))
        printf("Katalogas\n");
    else if (S_ISCHR(file_info.st_mode))
        printf("Charakterio įrenginys\n");
    else if (S_ISBLK(file_info.st_mode))
        printf("Blokinis įrenginys\n");
    else if (S_ISFIFO(file_info.st_mode))
        printf("Kanalas\n");
    else if (S_ISLNK(file_info.st_mode))
        printf("Simbolinė nuoroda\n");
    else if (S_ISSOCK(file_info.st_mode))
        printf("Soketas\n");
    else
        printf("Nežinomas\n");
}

int main(int argc, char *argv[]) {
	printf( "(C) 2023 Mildaras Karvelis, %s\n", __FILE__ );
    if (argc != 2) {
        printf("Naudojimas: %s <failas>\n", argv[0]);
        return 1;
    }

    const char *path = argv[1];
    print_file_info(path);

    return 0;
}
