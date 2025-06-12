/* Mildaras Karvelis milkar3 */
/* Failas: milkar3_sablonas.c */
#include <stdio.h>
#include <stdlib.h>

void func1() {
    printf("Func1 called\n");
}

void func2() {
    printf("Func2 called\n");
}

void func3() {
    printf("Func3 called\n");
}

int main(int argc, char *argv[]) {
	printf( "(C) 2023 Mildaras Karvelis, %s\n", __FILE__ );
    if (argc < 2) {
        printf("Usage: %s <exit_type>\n", argv[0]);
        return 1;
    }

    int exit_type = atoi(argv[1]);

    if (exit_type == 1) {
        printf("Exiting with _Exit()\n");
        _Exit(0);
    } else if (exit_type == 2) {
        printf("Exiting with exit()\n");
        exit(0);
    } else if (exit_type == 3) {
        printf("Exiting with return\n");
        return 0;
    } else if (exit_type == 4) {
        printf("Exiting with abort()\n");
        abort();
    }

    atexit(func1);
    atexit(func2);
    atexit(func3);

    printf("Program continues...\n");

    return 0;
}
