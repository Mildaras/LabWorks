/* Mildaras Karvelis milkar3 */
/* Failas: milkar3_fork01a.c */
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#define W(x) write(1, #x, sizeof #x)

int main() {
    fork();
	if(execlp("/bin/ls", "ls", NULL) != -1)
	{
		fork();
	}
	
}
