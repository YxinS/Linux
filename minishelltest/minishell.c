#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<wait.h>
#include<fcntl.h>


int main(){
	while(1){
		printf("[syx@minishell]]$:");
		fflush(stdout);
		char buf[1024] = {0};
		fgets(buf,1023,stdin);
		buf[strlen(buf)-1] = '\0';
		int redirect_flag = 0;
		char* redirect_file = NULL;
		char *ptr = buf;
		while(*ptr !='\0'){
			if(*ptr == '>'){
				redirect_flag = 1;
				*ptr = '\0';
				ptr++;
				if(*ptr == '>'){
					redirect_flag = 2;
					ptr++;
				}
				while(*ptr == ' ' && *ptr != '\0'){
					ptr++;
				}
				redirect_file = ptr;
				while(*ptr != ' ' && *ptr != '\0'){
					ptr++;
				}
				*ptr = '\0';
			}
			ptr++;
		}
		
		char *argv[32] = {NULL};
		int argc = 0;
		ptr = buf;
		while(*ptr != '\0'){
			if(*ptr !=' '){
				argv[argc] = ptr;
				argc++;
				while(*ptr != ' '&& *ptr !='\0'){
					ptr++;
				}
				*ptr ='\0';
			}
			ptr++;
		}
		argv[argc] = NULL;
		pid_t pid = fork();
		if(pid==0){
			if(redirect_flag == 1){
				int fd = open(redirect_file,O_WRONLY | O_CREAT | O_TRUNC,0664);
				dup2(fd,1);
			}
			else if(redirect_flag == 2){
				int fd = open(redirect_file,O_WRONLY | O_CREAT | O_APPEND,0664);
				dup2(fd,1);
			}
			execvp(argv[0],argv);
			perror("execvp error\n");
			exit(0);
		}
		wait(NULL);
	}
	return 0;
}


