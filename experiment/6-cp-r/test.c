#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<dirent.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<string.h>

void cp_file(const char *src_path, const char *des_path)
{
    int src_f = open(src_path, O_RDONLY), des_f = open(des_path, O_CREAT | O_TRUNC | O_RDWR, 0777);
    if(src_f == -1 || des_f == -1){
        printf("fail to open the file!\n");
        return;
    }
    char buf[512];
    while(read(src_f, buf, 512) > 0){
        write(des_f, buf, strlen(buf));
    }
    close(src_f);
    close(des_f);
}

void cp_dir(const char* old_path, const char* new_path)
{
    DIR * op_dir = opendir(old_path);
	if(op_dir == NULL){
        printf("fail to open src_dir\n");
        return;
    }

    DIR * new_dir = opendir(new_path);
    if(new_dir == NULL){
        int res = mkdir(new_path, 0777);
        if(res == -1){
            printf("fail to create dir!\n");
            return;
        }
    }
    struct dirent * redir;
    while(redir = readdir(op_dir)){
        if(strcmp(redir->d_name, ".") == 0 || strcmp(redir->d_name, "..") == 0)continue;
        char next_old[128], next_new[128];
        strcpy(next_old, old_path);
        strcpy(next_new, new_path);
        strcat(next_old, "/"); strcat(next_old, redir->d_name);
        strcat(next_new, "/"); strcat(next_new, redir->d_name);
        if((redir->d_type & DT_REG) == DT_REG)//普通文件则复制
			cp_file(next_old, next_new);    
		else if((redir->d_type & DT_DIR) == DT_DIR)//目录则递归
			cp_dir(next_old, next_new);
    }
}

int main(int argc, char* argv[]){
    if(argc != 3)printf("wrong!\n");
    struct stat msg;
    stat(argv[1], &msg);
    if(S_ISDIR(msg.st_mode)) cp_dir(argv[1],argv[2]);
	else cp_file(argv[1],argv[2]);
}