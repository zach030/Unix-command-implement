#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>

void do_ls(char []);

int main(int ac,char *argv[]){
    if (ac==1)
        do_ls(".");
    else
        while(--ac){
            printf("%s:\n",*++argv);
            do_ls(*argv);
        }
}

void show_stat_info(char *fname, struct stat *buf)
{
    printf("  mode: %o\n",buf->st_mode);
    printf(" links: %ld\n",buf->st_nlink);
    printf("  user: %d\n",buf->st_uid);
    printf(" group: %d\n",buf->st_gid);
    printf("  size: %ld\n",buf->st_size);
    printf("modtime: %ld\n",buf->st_mtime);
    printf("  name: %s\n",fname);
}

void do_ls(char dirname[]){
    // list files in directory
    DIR *dir_ptr;
    struct dirent *direntp;
    if ((dir_ptr=opendir(dirname))==NULL)
        fprintf(stderr,"lsl: cannot open %s\n",dirname);
    else
    {
        while ((direntp = readdir(dir_ptr))!=NULL)
            printf("%s\n",direntp->d_name);
            struct stat buf;
            if (stat(direntp->d_name,&buf)!=-1){
                show_stat_info(direntp->d_name,&buf);
            }
            
        closedir(dir_ptr);
    }
}

