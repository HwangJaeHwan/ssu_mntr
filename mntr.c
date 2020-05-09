#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <dirent.h>
#include <time.h>
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
void erase_tree(struct finfo *head);
void make_tree(struct dirent **filelist, int count ,struct finfo *head);
void make_subtree(struct finfo *curr,char *filename);
void compare(struct dirent **filelist, int count, struct finfo *head);
void delete_file(char *filename);
void remove_file(char *filename);
int cal_time(char *day, char *hour );

char target_path[100];
char save_path[100];

int main(int argc, char *argv[])
{
	
	/*	char input[100];
	char save_input[5][100];
	char *ptr;
	int i;
	int tmp;

	getcwd(save_path,100);

	chdir("check");

	getcwd(target_path,1024);

	chdir(save_path);

	while(1){
	i = 0;
	memset(save_input,0,sizeof(save_input));
	memset(input,0,sizeof(input));
	
	printf("20162530>>");

	fgets(input,sizeof(input),stdin);

	ptr = strtok(input," ");

	while(ptr != NULL) {
	strcpy(save_input[i++],ptr);
	ptr = strtok(NULL," ");
	}
	
	printf("i = %d\n",i);
	printf("length : %ld\n",strlen(save_input[i-1]));
	save_input[i-1][strlen(save_input[i-1])-1] = 0;

	if(strlen(save_input[i-1]) == 0){//마지막에 공백을 입력했을 시,제거
		printf("in\n");
		i--;
	//	memset(save_input[i],0,sizeof(save_input[i]));
	}


	for(tmp = 0; tmp<i;tmp++)
		printf("save_input[%d] : %s\n",tmp,save_input[tmp]);
	
	
	printf("save_input[0] : %s\n",save_input[0]);
	printf("length1 : %ld\n",strlen(save_input[0]));
	printf("length2 : %ld\n",strlen("delete"));

	if(!strcmp("delete",save_input[0])){
		time_t t = time(NULL);
		time_t input_time;
		struct tm user;
		int dif_time = 0;
		
		if(i == 2){
			printf("only filename\n");
			delete_file(save_input[1]);
		}

		else if (i == 3){
			printf("hello moto\n");
			
			if(!strcmp(save_input[2],"-i"))
				remove_file(save_input[1]);

			else if(!strcmp(save_input[2],"-r"))
				printf("delete 출력\n");

			else
				break;



			printf("filename, option\n");//i remove
		}								 //r 

		else if (i == 4){
			pid_t pid;
		
			printf("filename, endtime\n");

			dif_time = cal_time(save_input[2],save_input[3]);
			
			printf("time : %d\n",dif_time);

			if((pid = fork()) < 0){
				fprintf(stderr, "fork error\n");
				exit(1);
			}

			else if(pid == 0){
				sleep(dif_time);
				delete_file(save_input[1]);
				exit(0);
			}

		}

		else if (i == 5){				
			printf("all\n");
		}

		else 
			printf("error\n");
	
	}
		
}*/




	mntr();

}

void mntr(){

struct dirent **filelist;
struct finfo *curr;
struct finfo *head =NULL,*head2=NULL;
int exist;
int count;
int idx;
char path[1024] = "/home/hwangjaehwan/P2/check";

chdir(path);


for(int i=0;i<4;i++){

	count = scandir(path,&filelist,NULL,alphasort);

	if(head == NULL){
		printf("make tree\n");
		head = malloc(sizeof(struct finfo));
		head2 = malloc(sizeof(struct finfo));
		
		make_tree(filelist,count,head);
		make_tree(filelist,count,head2);

		curr = head2->next;
		while(curr != NULL){
			printf("head2 : %s\n",curr->f_name);
			curr = curr->next;
		}
		
	/*for(idx = 2;idx < count; idx++){
		stat(filelist[idx]->d_name,&statbuf);
		addNode(curr,filelist[idx]->d_name,statbuf.st_mtime);
		printf("f_name : %s\n",(curr->next)->f_name);
		printf("add clear\n");
		if(S_ISDIR(statbuf.st_mode)) {
			printf("find DIR\n");
			//make_subtree(curr,filelist[idx]->d_name);
		}
		curr = curr->next;
	}*/

		curr = head->next;
		
		printf("head : %s\n",curr->f_name);

		while(curr != NULL){
			printf("first : %s\n",curr->f_name);
			printf("first2 : %d\n",curr->is_dir);
			curr = curr->next;
		}
	}
else{
	printf("exist tree\n");

	compare(filelist,count,head);	
	
	curr = head->next;
		
		while(curr != NULL){
			printf("second : %s\n",curr->f_name);
			printf("second2 : %d\n",curr->is_dir);
			curr = curr->next;
		}
	
//	if(i==2)
//		erase_tree(head);

	



}

for(idx = 0; idx < count;idx++)
		free(filelist[idx]);

	free(filelist);

sleep(3);
}



}

void make_tree(struct dirent **filelist, int count ,struct finfo *head){

	struct finfo *curr;
	int idx;
	char tmp_path[100];
	
	curr = head;

	for(idx = 2;idx < count; idx++){
		stat(filelist[idx]->d_name,&statbuf);
		addNode(curr,filelist[idx]->d_name,statbuf.st_mtime); 		
		if(S_ISDIR(statbuf.st_mode)) {
			printf("find DIR\n");
			make_subtree(curr,filelist[idx]->d_name);
		}
		curr = curr->next;
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
void erase_tree(struct finfo *head){

	struct finfo *tmp;
	struct finfo *save;
	
	tmp = head->next;

	while(tmp != NULL){
	save = tmp->next;
	
	printf("tmp->f_name : %s\n",tmp->f_name);

	
	free(tmp);
	tmp = save;
	}

head->next = NULL;

}

void make_subtree(struct finfo *curr,char *filename) {
printf("in2\n");
	
	char path[100];	
	struct finfo *tmp;
	struct dirent **sub_filelist;
	int count;
	int idx;

	getcwd(path,100);
	printf("filename : %s\n",filename);	
	printf("path : %s\n",getcwd(path,100));
	printf("curr->is_dir1 : %d\n",curr->is_dir);
	curr->is_dir = 99999;
	printf("curr->is_dir2 : %d\n",curr->is_dir);
	tmp = curr->low;
	

	if((count = scandir(filename,&sub_filelist,NULL,alphasort))==-1){
			fprintf(stderr,"scandir2 error\n");
			exit(1);
		}

	chdir(filename);

	make_tree(sub_filelist,count,tmp);
	
	curr->low = (curr->low)->next;
	tmp = curr->low;

		while(tmp != NULL){
			printf("subtree : %s\n",tmp->f_name);
			tmp = tmp->next;
		}

	for(idx = 0; idx < count;idx++)
		free(sub_filelist[idx]);

	free(sub_filelist);

	chdir(path);
}

void compare(struct dirent **filelist, int count ,struct finfo *head){

	struct finfo *curr;
	struct finfo *save;
	int idx;
	int exist;

	for(idx = 2; idx < count; idx++){
		exist = 0;
		//printf("idx : %d\n",idx);
		stat(filelist[idx]->d_name,&statbuf);
		//printf("filelist[idx]->d_name : %s\n",filelist[idx]->d_name);
		curr = head->next;

		if(S_ISDIR(statbuf.st_mode)){
			//find_tree
				}

		while(curr != NULL){
			//printf("curr->f_name : %s\n",curr->f_name);
		if(curr->is_dir != 0){
			save = curr;
			curr = curr->low;
				while(curr != NULL){
					if(!strcmp(filelist[idx]->d_name,curr->f_name)){
						exist = 1;
						printf("fall in love\n");
						if(statbuf.st_mtime != curr->mtime)
							printf("수정시간 출력\n");
		
						break;
					}
					curr = curr->next;
				}
			if(exist == 0)
				curr = save;
			else
				break;
		}
		
		if(!strcmp(filelist[idx]->d_name,curr->f_name)){
				exist++;
				printf("stat : %s, curr : %s\n",filelist[idx]->d_name,curr->f_name);
				printf("stat : %ld, curr : %ld\n",statbuf.st_mtime,curr->mtime);
			if(statbuf.st_mtime != curr->mtime)
			//	printf("수정시간 출력\n");
		
				break;
		}

		curr = curr->next;

		}
		if(exist == 0)
		printf("생성시간 출력\n");

	}

}

void find_sub(){






}

void delete_file(char *filename){
	
	DIR *dirp;
	char *files_path = "trash/files";
	char *info_path = "trash/info";
	char path_files[1024];
	char path_info[1024];
	char delete_file[1024];
	char trash_file[1024];
	char tmp[1024];
	char *save;

	printf("filename : %s\n",filename);

 	if((dirp = opendir("trash")) == NULL){
		mkdir("trash",0755);
		chdir("trash");
		mkdir("files",0755);
		mkdir("info",0755);
		printf("make trash\n");
		chdir(save_path);
	 }
	
	chdir(files_path);
	getcwd(path_files,1024);
	printf("path_files1 : %s\n",path_files);
	chdir(save_path);
	chdir(info_path);
	getcwd(path_info,1024);
	chdir(target_path);

	if(filename[0] != '/'){
		printf("홀리쉿\n");
		strcat(path_files,"/");
		strcat(path_files,filename);
		realpath(filename,delete_file);
	}
	else{
		printf("이잉 기모링\n");
	
		char *ptr = strtok(filename,"/");

		while(ptr != NULL) {
			save = ptr;
			chdir(ptr);
			ptr = strtok(NULL,"/");
		}
			
		getcwd(tmp,1024);
		printf("tmp2 : %s\n",tmp);
		
		strcat(path_files,"/");
		strcat(path_files,save);
		realpath(save,delete_file);
		printf("save : %s\n",save);
	}



	rename(delete_file,path_files);
	stat(delete_file,&statbuf);
	getcwd(tmp,1024);
	printf("getcwd : %s\n",tmp);
	printf("f_name : %s\n",filename);
	printf("stat_buf : %ld\n",statbuf.st_mtime);
	printf("buf :%s\n",delete_file);
	printf("path_files : %s\n",path_files);

	chdir(save_path);

}


int cal_time(char *day, char *hour ){

	time_t t = time(NULL);
	time_t input_time;
	struct tm user;
	int dif_time;

	char *ptr = strtok(day,"-");
						
	user.tm_year = atoi(ptr)-1900;
	ptr = strtok(NULL,"-");
	user.tm_mon = atoi(ptr)-1;
	ptr = strtok(NULL,"-");
	user.tm_mday = atoi(ptr);
	
	ptr = strtok(hour,":");
	
	user.tm_hour = atoi(ptr);
	ptr = strtok(NULL,":");
	user.tm_min = atoi(ptr);
	user.tm_sec = 0;
	user.tm_isdst = 0;

	input_time = mktime(&user);

	
	dif_time = (int)difftime(input_time,t);


return dif_time;

}

void remove_file(char *filename){

	char remove_file[1024];
	char path[1024];
	char *save;

	printf("inin\n");
	chdir(target_path);
	
	if(filename[0] != '/'){
		printf("홀리쉿\n");
		realpath(filename,remove_file);
	}
	else{
		printf("이잉 기모링\n");
	
		char *ptr = strtok(filename,"/");

		while(ptr != NULL) {
			save = ptr;
			chdir(ptr);
			ptr = strtok(NULL,"/");
		}
			
		strcat(path,"/");
		strcat(path,save);
		realpath(save,remove_file);
		printf("save : %s\n",save);
		printf("remove_file : %s\n",remove_file);
	}

	remove(remove_file);

}
