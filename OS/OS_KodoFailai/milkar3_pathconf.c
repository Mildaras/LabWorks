/* Mildaras Karvelis milkar3 */
/* Failas: milkar3_sablonas.c */

#include <stdio.h>
#include <unistd.h>

int main() {
    printf( "(C) 2023 Mildaras Karvelis, %s\n", __FILE__ );
    long name_max = pathconf("/", _PC_NAME_MAX);
    long path_max = pathconf("/", _PC_PATH_MAX);

    if (name_max != -1)
        printf("Maksimalus failo vardo ilgis: %ld\n", name_max);
    else
        printf("Nepavyko gauti maksimalaus failo vardo ilgio informacijos.\n");

    if (path_max != -1)
        printf("Maksimalus kelio ilgis: %ld\n", path_max);
    else
        printf("Nepavyko gauti maksimalaus kelio ilgio informacijos.\n");

    return 0;
}
