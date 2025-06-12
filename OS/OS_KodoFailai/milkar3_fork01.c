/* Mildaras Karvelis milkar3 */
/* Failas: milkar3_fork01a.c */
#include <stdio.h>
#include <unistd.h>

int main() {
    printf("Pradinis procesas (PID: %d)\n", getpid());

    fork();
    fork();

    printf("Procesas (PID: %d) tėvas (PPID: %d)\n", getpid(), getppid());

    return 0;
}
