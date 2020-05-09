#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>

int main(void)
{
 DIR *dirp;

 if((dirp = opendir("trash")) == NULL){
	fprintf(stderr,"failed\n");
	exit(1);
		 }
printf("pass\n");

}
