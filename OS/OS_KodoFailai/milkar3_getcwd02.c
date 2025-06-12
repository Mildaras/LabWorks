/* Mildaras Karvelis milkar3 */
/* Failas: milkar3_sablonas.c */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <limits.h>

int main() {
	printf( "(C) 2023 Mildaras Karvelis, %s\n", __FILE__ );
    char current_dir[PATH_MAX];
    long path_max = pathconf(".", _PC_PATH_MAX);

    // Gauname einamojo katalogo vardą
    if (getcwd(current_dir, path_max) != NULL)
        printf("Einamasis katalogas: %s\n", current_dir);
    else {
        perror("Klaida gaudant einamojo katalogo vardą");
        return EXIT_FAILURE;
    }

    // Atidarome einamąjį katalogą
    int dir_fd = open(current_dir, O_RDONLY);
    if (dir_fd == -1) {
        perror("Klaida atidarant einamąjį katalogą");
        return EXIT_FAILURE;
    }

    // Spausdiname einamojo katalogo deskriptorių
    printf("Einamojo katalogo deskriptorius: %d\n", dir_fd);

    // Pereiname į /tmp katalogą
    if (chdir("/tmp") == -1) {
        perror("Klaida keičiant katalogą į /tmp");
        return EXIT_FAILURE;
    }

    // Gauname naują einamojo katalogo vardą
    if (getcwd(current_dir, path_max) != NULL)
        printf("Naujas einamasis katalogas: %s\n", current_dir);
    else {
        perror("Klaida gaudant naują einamojo katalogo vardą");
        return EXIT_FAILURE;
    }

    // Grįžtame į 2-ame žingsnyje atidarytą katalogą
    if (fchdir(dir_fd) == -1) {
        perror("Klaida grįžtant į anksčiau atidarytą katalogą");
        return EXIT_FAILURE;
    }

    // Patikriname ir spausdiname, kad grįžome į anksčiau atidarytą katalogą
    if (getcwd(current_dir, path_max) != NULL)
        printf("Grįžta į anksčiau atidarytą katalogą: %s\n", current_dir);
    else {
        perror("Klaida gaudant grįžto katalogo vardą");
        return EXIT_FAILURE;
    }

    close(dir_fd);

    return 0;
}
