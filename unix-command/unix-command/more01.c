#include<stdio.h>
#define PAGELEN 24
#define LINELEN 512
void do_more(FILE *);
int see_more();
int main(int ac, char *av[]) {
	FILE *fp;
	if (ac == 1) 
		do_more(stdin);
	else
		while(--ac)
			if ((fp = fopen(*++av, "r") != NULL)) {
				do_more(fp);
				fclose(fp);
			}
			else
				exit(1);
	return 0;
}

void do_more(FILE *fp) {
	char line[LINELEN];
	int num_of_lines = 0;
	int see_more(), reply;
	while (fgets(line, LINELEN, fp)) {
		if (num_of_lines == PAGELEN) {//is full screen?
			reply = see_more();// ask user if see more
			if (reply == 0) 
				break;
			num_of_lines -= reply;
		}
		if (fputs(line, stdout) == EOF) 
			exit(1);
		num_of_lines++;
	}
}

int see_more() {
	int c;
	printf("\033[7m more?\033[m");
	while (c = getchar() != EOF) {
		if (c == 'q') // quit ,not see
			return 0;
		if (c == " ") // next page
			return PAGELEN;
		if (c == "\n") // next line
			return 1;
	}
	return 0;
}