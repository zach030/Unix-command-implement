#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>

void do_ls(char []);
void dostat(char *);
void show_file_info(char *, struct stat *);
void mode_to_letters(int,char []);
char *uid_to_name(uid_t);
char *gid_to_name(gid_t);

int main(int ac,char *argv[]){
    if (ac==1)
    // 如果只有一个参数，则默认当前目录
        do_ls(".");
    else
        while(--ac){
            // 遍历所有输入参数
            printf("%s:\n",*++argv);
            do_ls(*argv);
        }
}

void do_ls(char dirname[]){
    // dir 结构体
    DIR *dir_ptr;
    struct dirent *direntp;
    if ((dir_ptr=opendir(dirname))==NULL)
        fprintf(stderr,"lsl: cannot open %s\n",dirname);
    else
    {
        while ((direntp = readdir(dir_ptr))!=NULL)
            // 展示当前目录下文件详细信息
            dostat(direntp->d_name);
        closedir(dir_ptr);
    }
}

void dostat(char * filename)
{
    struct stat info;
    if (stat(filename,&info)==-1)
        perror(filename);
    else
        show_file_info(filename,&info);
}

void show_file_info(char *filename, struct stat *info_p)
{
    char *uid_to_name(),*ctime(),*gid_to_name(),*filemode();
    void mode_to_letters();
    char modestr[11];

    // 进行字段的解码
    mode_to_letters(info_p->st_mode,modestr);

    // 权限：rwxrwxrwx
    printf(" %s ",modestr);
    // 链接数
    printf(" %4d ",(int)info_p->st_nlink);
    // 当前用户
    printf(" %-8s ",uid_to_name(info_p->st_uid));
    // 当前用户组
    printf(" %-8s ",gid_to_name(info_p->st_gid));
    // 文件大小
    printf(" %8ld ",(long)info_p->st_size);
    // 最近修改时间
    printf(" %.12s",4+ctime(info_p->st_mtime));
    // 文件名
    printf(" %s\n",filename);
}

void mode_to_letters(int mode, char str[])
{
    strcpy(str,"----------");
    // 是目录
    if (S_ISDIR(mode)) str[0]='d';
    // 是字符设备
    if (S_ISCHR(mode)) str[0]='c';
    // 是块设备
    if (S_ISBLK(mode)) str[0]='b';

    // 3 bit for user
    if (mode&S_IRUSR) str[1]='r';
    if (mode&S_IWUSR) str[1]='w';
    if (mode&S_IXUSR) str[1]='x';
    // 3 bit for group
    if (mode&S_IRGRP) str[1]='r';
    if (mode&S_IWGRP) str[1]='w';
    if (mode&S_IXGRP) str[1]='x';
    // 3 bit for other
    if (mode&S_IROTH) str[1]='r';
    if (mode&S_IWOTH) str[1]='w';
    if (mode&S_IXOTH) str[1]='x';
}

#include<pwd.h>

char *uid_to_name(uid_t uid)
{
    struct passwd * getpwuid(),*pw_ptr;
    static char numstr[10];
    if((pw_ptr=getpwuid(uid))==NULL){
        sprintf(numstr,"%d",uid);
        return numstr;
    }
    else
        return pw_ptr->pw_name;
}

#include<grp.h>
char *gid_to_name(gid_t gid)
{
    struct group * getgrgid(),*grp_ptr;
    static char numstr[10];
    if ((grp_ptr=getgrgid(gid))==NULL){
        sprintf(numstr,"%d",gid);
        return numstr;
    }
    else
        return grp_ptr->gr_name;
}