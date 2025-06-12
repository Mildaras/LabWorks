/* Mildaras Karvelis milkar3 */
/* Failas: milkar3_sablonas.c */

#include <stdio.h>

int main( int argc, char * argv[] ){
	const char* dirname = "testdir";

    int status = mkdir(dirname, S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH);

    if (status == 0) {
        printf("Directory created successfully.\n");
    } else {
        printf("Unable to create the directory.\n");
    }
   printf( "(C) 2023 Mildaras Karvelis, %s\n", __FILE__ );
   return 0;
}