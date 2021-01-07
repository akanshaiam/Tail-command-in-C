#include "types.h"
#include "stat.h"
#include "user.h"

char buffer1[1024]={'\\'};
char buffer2[1024]={'\\'};

void tail(int fd,char *name, int num_of_lines)
{
	int i,n,m,l;
	int lines_num;
	lines_num=0;
	int start;

	while((n=read(fd,buffer1,sizeof(buffer1)))>0){
		for(i=0;i<=n ;i++){
			if(buffer1[i]=='\n'){
				lines_num++;
				if(strcmp(name,"")==0){
					printf(1,"\n");
			 	}
			} else{
				if(strcmp(name,"")==0){
					if(buffer1[i] =='\0') {
						exit();
					}
					if(buffer1[i]!='\n') {
				 		printf(1,"%c",buffer1[i]);
					} else {
				 		printf(1,"\n");
					}
				}
			}
		}
	}
	close(fd);
	start = lines_num-num_of_lines;
	l=0;
	int fd2 = open(name,0);
	while((m=read(fd2,buffer2,sizeof(buffer2)))>0) {
		for(i=0;i<=m;i++) {
			if(buffer2[i] == '\n') {
				l++;
			}
			if(l>=start) {
				if(buffer2[i] !='\n' && l>=start) {
					printf(1,"%c",buffer2[i]);
				} else {
					printf(1,"\n");
					l++;
				}
		   	}
		}
	}
	close(fd2);
	if(n<0) {
		printf(1,"tail: couldn't read file \n");
		exit();
	}
}

int main(int argc,char *argv[]) {
	int fd,i;

	if(argc<=1) {
		tail(0,"",10);
		exit();
	} else if(argc==2) {
		for(i=1;i<argc;i++) {
			if((fd=open(argv[i],0))<0) {
				printf(1,"Error in reading file");
				exit();
			}
			tail(fd,argv[i],10);
			close(fd);
		}
	} else if(argc==3) {
		char c[1024];
		strcpy(c,argv[1]);
		char *str_num=c;
		str_num=str_num+1;
		int num_of_lines= atoi(str_num);

		for(i=2;i<argc;i++) {
			if((fd=open(argv[i],0))<0) {
				printf(1,"tail:error opening the file %s\n",argv[i]);
				exit();
			}
			tail(fd,argv[i],num_of_lines);
			close(fd);
		}
	} else {
		printf(1,"tail- error in syntax");
	}
	exit();
}
