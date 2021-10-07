#include <stdio.h>
#include <utmp.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#define SHOWHOST

void show_info(struct utmp *);

int main()
{
    struct utmp current_record; // read info to here
    int utmpfd;// utmp file descriptor
    int reclen = sizeof(current_record);
    // open utmp file
    if ((utmpfd=open(UTMP_FILE,O_RDONLY))==-1)
        perror(UTMP_FILE);
        exit(1);
    // read file
    while (read(utmpfd,&current_record,reclen)==reclen)
    {
        /* code */
        show_info(&current_record);
    }
    close(utmpfd);
    return 0;
    // show output
}

void show_info(struct utmp *utbupf)
{
    if (utbupf->ut_type!=USER_PROCESS)
        return;
    printf("% -8.8s",utbupf->ut_name);
    printf(" ");
    printf("% -8.8s",utbupf->ut_line);
    printf(" ");
    printf("%10ld",utbupf->ut_time);
    printf(" ");
    #ifdef SHOWHOST
    printf("(%s)",utbupf->ut_host);
    #endif
    printf("\n");    
}