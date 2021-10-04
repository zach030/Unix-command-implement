#include <stdio.h>
#include <stdlib.h>
#define PAGELEN 24
#define LINELEN 512

void do_more(FILE * );
int see_more();

int main(int argc,char *argv[]){
    FILE *fp;
    if (argc==1)
        do_more(stdin);
    else
        while(argc--)
        if ((fp=fopen(*++argv,"r"))!=NULL)
        {
            do_more(fp);
            fclose(fp);
        }
        else
            exit(1);
    return 0;
}

void do_more(FILE *fp)
// read PAGELEN 
{
    char line[LINELEN];
    int num_of_lines=0;
    int see_more(),reply;
    // fgets 从文件流中读取一行，放到line字符串中
    while (fgets(line,LINELEN,fp))
    {
        if (num_of_lines==PAGELEN){
            reply = see_more();
            if (reply==0)
                break;
            num_of_lines -= reply;
        }
        // fputs 字符串写入到指定的流 stream
        if (fputs(line,stdout)==EOF)
            exit(1);
        num_of_lines++;
    }
}

int see_more()
{
    // show hint message
    int c;
    printf("\033[7m more? \033[m");
    while ((c=getchar())!=EOF)
    {
        if (c=='q')
            return 0;
        // 空格 看一页
        if (c==' ')
            return PAGELEN;
        // 回车 看一行
        if (c=='\n')
            return 1;
    }
    return 0;
}