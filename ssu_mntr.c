#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>

struct stat statbuf;

struct finfo{

char *f_name;
//char * d_name;
time_t mtime;
struct finfo *next;
struct finfo *low;
int is_dir;
};


void mntr();
void addNode(struct finfo *target, char *f_name, time_t mtime);
void make_low(struct finfo *curr, char *filename);
int find_low(char *dir_name ,struct finfo *curr, char *find_name);
void find_name(struct dirent **filelist, int count, struct finfo *curr);
int find_tree(char *dir_name, char *find_name);

struct finfo *head = NULL, *tmp = NULL;
struct finfo *curr;

int main(int argc, char *argv[])
{


	mntr();






}


void mntr(){

struct dirent **filelist;
struct finfo *tmp;
//struct finfo *head = NULL, *tmp = NULL;
//struct finfo *curr;
int exist;
int count;
//int count2;
int idx;
//int idx2;
char path[1024] = "/home/hwangjaehwan/P2/check";


	while(1){
		
		count = scandir(path,&filelist,NULL,alphasort);
		
	if(head == NULL){
		printf("make tree\n");
		head = malloc(sizeof(struct finfo));
		curr = head;

			for(idx = 2;idx < count; idx++){
				stat(filelist[idx]->d_name,&statbuf);
				printf("file : %s\n",filelist[idx]->d_name);
				addNode(curr,filelist[idx]->d_name,statbuf.st_mtime); 
				
				if(S_ISDIR(statbuf.st_mode)) {
					make_low(curr,filelist[idx]->d_name);
				}
				curr = curr->next;
			}
		curr = head->next;

		while(curr != NULL){
			printf("rotoRl : %s\n",curr->f_name);
			curr = curr->next;
		}
	}
	else {
		curr = head->next;	
		while(curr != NULL){
			printf("tlqkfrotoRl : %s\n",curr->f_name);
			curr = curr->next;
		}

		printf("tlqkftoRlrk cuehfdkTsk\n");
		
			for(idx = 2; idx < count; idx++){
				printf("idx : %d\n",idx);
				exist = 0;
				stat(filelist[idx]->d_name,&statbuf);
				printf("filelist[idx]->d_name : %s\n",filelist[idx]->d_name);
				curr = head->next;

				printf("curr -> %s\n",curr->f_name);
				
				while(curr != NULL){
					//printf("in while\n");	
					if(curr->is_dir != 0){
						printf("maybe\n");
						find_low(filelist[idx]->d_name,curr,filelist[idx]->d_name);	
					}
					if(!strcmp(filelist[idx]->d_name,curr->f_name)){
						printf("tlqkf\n");
							
							if(statbuf.st_mtime != curr->mtime)
								printf("print mtime\n");
							
						break;
					}
						curr = curr->next;
				}	
					printf("print create time\n");
			}
				curr = head->next;
				printf("curr = head->next %s\n",curr->f_name);

				find_name(filelist,count,curr);

				for(idx = 2;idx < count; idx++){
					stat(filelist[idx]->d_name,&statbuf);
					addNode(curr,filelist[idx]->d_name,statbuf.st_mtime); 
				
					if(S_ISDIR(statbuf.st_mode)) {
						make_low(curr,filelist[idx]->d_name);
					}
						curr = curr->next;
				}

			}	

		/*curr = head->next;
		printf("curr = head->next %s\n",curr->f_name);

		find_name(filelist,count,curr);

		for(idx = 2;idx < count; idx++){
			stat(filelist[idx]->d_name,&statbuf);
			addNode(curr,filelist[idx]->d_name,statbuf.st_mtime); 
				
			if(S_ISDIR(statbuf.st_mode)) {
				make_low(curr,filelist[idx]->d_name);
			}
				curr = curr->next;
		}*/

	for(idx = 0; idx < count;idx++)
		free(filelist[idx]);

	free(filelist);
	printf("--------------\n");	
	sleep(3);
	}
	
}


void addNode(struct finfo *target, char *f_name, time_t mtime) {
printf("in1\n");
	struct finfo *newNode = malloc(sizeof(struct finfo));

	//newNode->next = target->next;
	newNode->next = NULL;
	newNode->low = NULL;
	newNode->f_name = f_name;
	newNode->mtime = mtime;
	newNode->is_dir = 0;
	//newNode->d_name = d_name;

	target->next = newNode;

}

void make_low(struct finfo *curr,char *filename) {
printf("in2\n");
	struct finfo *tmp;
	struct dirent **filelist;
	int count;
	int idx;
	
	curr->is_dir = 1;
	tmp = curr->low;
	
	if((count = scandir(filename,&filelist,NULL,alphasort))==-1){
			fprintf(stderr,"scandir2 error\n");
			exit(1);
		}
			for(idx = 2; idx < count;idx++) {
				stat(filelist[idx]->d_name,&statbuf);
				addNode(tmp,filelist[idx]->d_name,statbuf.st_mtime);
																		//filename + filelist[idx]->d_name
				if(S_ISDIR(statbuf.st_mode))
				make_low(tmp,filelist[idx]->d_name);
				
				tmp = tmp->next;
			}	

	for(idx = 0; idx < count;idx++)
		free(filelist[idx]);

	free(filelist);
}


int find_low(char *dir_name, struct finfo *curr, char *find_name){

	struct finfo *tmp;
	struct dirent **filelist;
	int count;
	int idx;
	
	tmp = curr->low;
	
	if((count = scandir(dir_name,&filelist,NULL,alphasort))==-1){
			fprintf(stderr,"scandir3 error\n");
			exit(1);
		}

			for(idx = 2; idx < count;idx++) {
				stat(filelist[idx]->d_name,&statbuf);
			
				if(!strcmp(filelist[idx]->d_name,find_name)){
					
					while(tmp != NULL){
			
						if(tmp->is_dir != 0){
							if(find_low(filelist[idx]->d_name,tmp,find_name) != 0){
								printf("d_name.mtime print\n");
								return 1;
							}
						}
							if(!strcmp(tmp->f_name,find_name)){
				
								if(tmp->mtime != statbuf.st_mtime)
									printf("change in find_low\n");
							
									return 1;
						}		
		
					tmp = tmp->next;
		
					}
				}
			}

	for(idx = 0; idx < count;idx++)
		free(filelist[idx]);

	free(filelist);

	return 0;
}



int find_tree(char *dir_name,char *find_name){


	struct dirent **filelist;
	int count;
	int idx;

	if((count = scandir(dir_name,&filelist,NULL,alphasort))==-1){
			fprintf(stderr,"scandir4 error\n");
			exit(1);
		}

			for(idx = 2; idx < count;idx++) {
				stat(filelist[idx]->d_name,&statbuf);
				
				if(!strcmp(filelist[idx]->d_name,find_name))
					return 1;
				
				if(S_ISDIR(statbuf.st_mode))
					if(find_tree(filelist[idx]->d_name,find_name) != 0)
						return 1;
	
			}
	for(idx = 0; idx < count;idx++)
		free(filelist[idx]);

	free(filelist);

return 0;
}


void find_name(struct dirent **filelist,int count,struct finfo *curr){


	struct finfo *next;
	int exist;
	int idx;
	struct finfo *tmp;
	

			for(idx = 2; idx < count;idx++) {
				
			printf("tlqkf : %s\n",filelist[idx]->d_name);
			
			}
	while(curr != NULL){
		
			next = curr->next;
			
			exist = 0;

				//printf("curr : %s\n",curr->f_name);
				if(curr->is_dir != 0){
					find_name(filelist, count, curr->low);
				}

			for(idx =2;idx < count; idx++){	
				stat(filelist[idx]->d_name,&statbuf);
				
				if(!strcmp(curr->f_name, filelist[idx]->d_name)){	
					exist = 1;
					break;
				}
			
		
				if(S_ISDIR(statbuf.st_mode)) {	
					exist =	find_tree(filelist[idx]->d_name,curr->f_name);
				
				}
			
			}

			if(exist == 0)
				printf("print delete time\n");

			free(curr);
			curr = next;
		}
	tmp = head->next;
	printf("head->next : %s\n",tmp->f_name);

}
