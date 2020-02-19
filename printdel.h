#ifndef __PRINTDEL__

#define __PRINTDEL__

#include <stdio.h>//printf
#include <string.h>//strlen
#include <unistd.h>//sleep

#define ANSI_COLOR_RED "\x1b[31m"

#define ANSI_COLOR_GREEN "\x1b[32m"

#define ANSI_COLOR_YELLOW "\x1b[33m"

#define ANSI_COLOR_BLUE "\x1b[34m"

#define ANSI_COLOR_MAGENTA "\x1b[35m"

#define ANSI_COLOR_CYAN "\x1b[36m"

#define ANSI_COLOR_RESET "\x1b[0m"

void textAlligner(int spaces){
	int i;
	for(i=0;i<spaces;i++)
		printf(" ");
}

void print(char word[],int t){//string and typing delay in miliseconds
	int i;
	for(i=0;strlen(word)>i;i++){
		printf("%c",word[i]);
		fflush(stdout);
		usleep(t);
	}
}
void del(int n,int t){//how many chars and typing delay
	int i;
	for(i=0;n>i;i++){
		printf("\b \b");
		fflush(stdout);
		usleep(t);
	}
}

void red(char *str)
{
printf(ANSI_COLOR_RED);
printf("%s",str);
printf(ANSI_COLOR_RESET);
}

void green(char *str)
{
printf(ANSI_COLOR_GREEN);
printf("%s",str);
printf(ANSI_COLOR_RESET);
}

void yellow(char *str)
{
printf(ANSI_COLOR_YELLOW);
printf("%s",str);
printf(ANSI_COLOR_RESET);
}

void blue(char *str)
{
printf(ANSI_COLOR_BLUE);
printf("%s",str);
printf(ANSI_COLOR_RESET);
}

void magenta(char *str)
{
printf(ANSI_COLOR_MAGENTA);
printf("%s",str);
printf(ANSI_COLOR_RESET);
}

void cyan(char *str)
{
printf(ANSI_COLOR_CYAN);
printf("%s",str);
printf(ANSI_COLOR_RESET);
}

#endif

