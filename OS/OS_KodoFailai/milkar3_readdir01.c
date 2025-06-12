/* Mildaras Karvelis milkar3 */
/* Failas: milkar3_sablonas.c */
#include <stdio.h>
#include <dirent.h>

int main() {
	printf( "(C) 2023 Mildaras Karvelis, %s\n", __FILE__ );
    DIR *dir;
    struct dirent *entry;

    // Atidaryti einamąjį katalogą
    dir = opendir(".");
    if (dir == NULL) {
        perror("Klaida atidarant katalogą");
        return 1;
    }

    // Nuskaityti ir išvesti katalogo įrašus
    while ((entry = readdir(dir)) != NULL) {
        printf("I-node numeris: %ld, Failo vardas: %s\n", entry->d_ino, entry->d_name);
    }

    // Uždaryti katalogą
    closedir(dir);

    return 0;
}
