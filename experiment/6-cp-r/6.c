#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>
#include <utime.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>
#include <sys/types.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>

int FileToFile(char *source,char *dest,struct stat *pstat);
int DirToDir(char *source,char *dest);

int main(int argc, char *argv[])
{
	struct stat sourcestat;
	struct stat deststat;
	char destbuf[500];
	int ret = 0;

	if(argc!=3){
		printf("input error\n");
		return -1;
	}else{
		printf("src_file: %s\n", argv[1]);
		printf("dest_file: %s\n", argv[2]);
		if(lstat(argv[1],&sourcestat) == -1){
			printf("get argv[1] stat error\n"); 
			return -1;
		}
		if(S_ISDIR(sourcestat.st_mode)){
			if(access(argv[2], F_OK)!=0) {
				ret = mkdir(argv[2],sourcestat.st_mode);
				printf("mkdir the ret is %d\n", ret);
			}
			else{
				if(lstat(argv[2],&deststat) == -1){
					printf("ERROR:get argv[1] stat error\n"); 
					return -1;
				}
				if(!S_ISDIR(deststat.st_mode))
				{
					printf("ERROR:the dest is exist file\n");
					return -1;
				}			
				else
				{
					int len;
					char *pSrc;

					len = strlen(argv[1]);			
					pSrc = argv[1] + (len-1); //last character
					/*先找出源文件的文件名*/
					while (pSrc >= argv[1] && *pSrc != '/')
					{
						pSrc--;
					}
					pSrc++;//指向源文件名
					printf("the dest file is %s\n",pSrc);
					memset(destbuf,0,500);
					sprintf(destbuf,"%s/%s",argv[2],pSrc);
					printf("the dest path is %s\n",destbuf);

					if(access(destbuf, F_OK)!=0) 
					{
						ret = mkdir(destbuf,0755);
						printf("mkdir the ret is %d\n",ret);
					}					
					ret = DirToDir(argv[1],destbuf);
					return ret;							
				}
			}
			ret = DirToDir(argv[1],argv[2]);
			return ret;		
		}
		else
		{
			if(access(argv[2], F_OK)==0) 
			{	
				printf("dest file exist\n");
				if(lstat(argv[2],&deststat) == -1)
				{
					printf("ERROR:get argv[1] stat error\n"); 
					return -1;
				}
				if(S_ISDIR(deststat.st_mode))
				{
					int len;
					char *pSrc;

					len = strlen(argv[1]);			
					pSrc = argv[1] + (len-1); //指向最后一个字符
					/*先找出源文件的文件名*/
					while (pSrc >= argv[1] && *pSrc != '/')
					{
						pSrc--;
					}
					pSrc++;//指向源文件名
					printf("the dest file is %s\n",pSrc);
					memset(destbuf,0,500);
					sprintf(destbuf,"%s/%s",argv[2],pSrc);
					printf("the dest path is %s\n",destbuf);					
					ret = FileToFile(argv[1],destbuf,&sourcestat);
					return ret;		
				}	
				else
				{
					ret = FileToFile(argv[1],argv[2],&sourcestat);
					return ret;							
				}
			}
			else
			{
				int len;
				char *pSrc;

				ret = mkdir(argv[2],0755);
				printf("mkdir the ret is %d\n",ret);

				len = strlen(argv[1]);			
				pSrc = argv[1] + (len-1); //指向最后一个字符
				/*先找出源文件的文件名*/
				while (pSrc >= argv[1] && *pSrc != '/')
				{
					pSrc--;
				}
				pSrc++;//指向源文件名
				printf("the dest file is %s\n",pSrc);
				memset(destbuf,0,500);
				sprintf(destbuf,"%s/%s",argv[2],pSrc);
				printf("the dest path is %s\n",destbuf);					
				ret = FileToFile(argv[1],destbuf,&sourcestat);
				return ret;
			}				
		}
	}
}

int FileToFile(char *source, char *dest, struct stat *pstat){
  printf("source file: %s\n",source);
  int sourcefd = open(source,O_RDONLY);
  if(sourcefd == -1){
    printf("open source file fail!\n");
    exit(0);
  }
  printf("sourcefd:%d\n",sourcefd);
  int datacount = (int)pstat->st_size;
  int readcount = 1024,writecount;
  printf("dest:%s\n",dest);
  int destfd = open(dest,O_WRONLY|O_CREAT|O_TRUNC,pstat->st_mode);
  printf("destfd:%d\n",destfd);
  char buf[2000] = {0};

  printf("datacount:%d\n",datacount);
  while(datacount > 0){ 
    printf("%d\t%d\n",datacount,readcount);
    if(datacount < readcount){
      readcount = datacount;
    }

    if((writecount = read(sourcefd,buf,readcount)) == readcount){
      printf("%s\n",buf);
      int ret = write(destfd,buf,writecount);
      if(ret == -1){
        printf("fail to write!\n");
        exit(0);
      }
    }else{
      writecount = read(sourcefd,buf,readcount);
      printf("writecount:%d\n",writecount);
      printf("string:%s\n",buf);
      printf("read error!\n");
      exit(EXIT_FAILURE);
    }
    
    datacount -= writecount;
  }
  printf("Successful to write!\n");
  close(sourcefd);
  printf("close sourcefd successfully!\n");
  close(destfd);
  printf("close destfd successfully!\n");

  return 0;
}



int DirToDir(char *source, char* dest){
  DIR *currentdir = NULL;
  struct dirent *currentdp = NULL;
  struct stat currentstat;
  char sourcebuf[500], destbuf[500];
  currentdir = opendir(source);//open
  memset(&currentstat,0,sizeof(currentdir));//intialize

  while((currentdp = readdir(currentdir)) != NULL){
    if(currentdp->d_name[0] != '.'){//pass 
      sprintf(sourcebuf,"%s/%s",source,currentdp->d_name);//写入目标路径
      printf("the source dir is %s\n",sourcebuf);
      if(lstat(sourcebuf,&currentstat) == -1){
        printf("get stat error\n");
        exit(EXIT_FAILURE);
      }
      sprintf(destbuf,"%s/%s",dest,currentdp->d_name);
      printf("the dest dir is %s\n",destbuf);
      if(S_ISDIR(currentstat.st_mode)){//判断是否为目录文件
        if(access(destbuf,F_OK) == -1){//文件是否存在
          mkdir(destbuf,currentstat.st_mode);
        }
        DirToDir(sourcebuf,destbuf);
      }else if(!S_ISDIR(currentstat.st_mode)){
        FileToFile(sourcebuf,destbuf,&currentstat);
      }
    }
  }
  closedir(currentdir);
  return 0;
}
