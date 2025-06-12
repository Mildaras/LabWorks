/* Mildaras Karvelis milkar3 */
/* Failas: milkar3_sablonas.c */
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/resource.h>

#define ITERATIONS 1000000000

int main() {
	printf( "(C) 2023 Mildaras Karvelis, %s\n", __FILE__ );
    struct rlimit cpu_limit;
    cpu_limit.rlim_cur = 1;  // 1 sekundės limitas
    cpu_limit.rlim_max = 1;

    // Nustatome CPU limitą
    if (setrlimit(RLIMIT_CPU, &cpu_limit) != 0) {
        perror("Failed to set CPU limit");
        return 1;
    }

    int count = 0;
    while (1) {
        count++;

        if (count == ITERATIONS) {
            break;
        }
    }

    printf("Iterations: %d\n", count);

    return 0;
}
