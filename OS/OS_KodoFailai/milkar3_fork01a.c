/* Mildaras Karvelis milkar3 */
/* Failas: milkar3_fork01a.c */
#include <stdio.h>
#include <unistd.h>

int main() {
    printf("Pradinis procesas (PID: %d)\n", getpid());

    pid_t child_pid = fork();

    if (child_pid == 0) {
        // Vaiko procesas
        printf("Vaiko procesas (PID: %d) tėvas (PPID: %d)\n", getpid(), getppid());

        pid_t grandchild_pid = fork();

        if (grandchild_pid == 0) {
            // Anūko procesas
            printf("Anūko procesas (PID: %d) tėvas (PPID: %d)\n", getpid(), getppid());
        }
    }

    return 0;
}
