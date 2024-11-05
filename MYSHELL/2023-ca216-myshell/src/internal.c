//Name:Siri Nandipaty student id:21449384
#include <string.h>
#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#define MAX_BUFFER 1024                        
#define MAX_ARGS 64                            
#define SEPARATORS " \t\n"   

void internalclr(char **args);
void internalpause(char **args);
void internaldir(char **args);
void internalcd(char **args);
void internalecho(char **args);
void internalhelp(char **args);
void internalquit(char **args);
void internalenviron(char **args);


void internalclr(char **args){
    system("clear");
}


void internaldir(char **args){
    DIR *directory;
    struct dirent *dir;
    if (args[1] == NULL) {
        fprintf(stdout, "please include a directory\n");} 
    else {
        directory = opendir(args[1]);
        if (directory == NULL) {
            fprintf(stdout, "cannot open directory %s\n", args[1]);} 
        else {
            while ((dir = readdir(directory)) != NULL) {
                printf("%s\n", dir->d_name);
                                }
    closedir(directory);}}

}


void internalpause(char ** args){
    printf("Press Enter to continue...");
    fflush(stdout);  
    while (getchar() != '\n'); } 

void internalenviron(char ** args){
    extern char **environ;
    int i;
    for (i = 0; environ[i] != NULL; i++)
        printf("%s\n",environ[i]);
    exit(0); }



void internalecho(char ** args){
    while (*args) {
    fprintf(stdout,"%s ",*args++);
    fputs ("\n", stdout);}}

void internalcd(char ** args){
    if (args[1] == NULL) {
		printf("%s\n", getenv("PWD"));}
	
	else if (chdir(args[1]) != 0) {
		perror("cd");}
    else {
		char cwd[MAX_BUFFER];
		getcwd(cwd, sizeof(cwd));
		setenv("PWD", cwd, 1);
        printf("Current working directory: %s\n", cwd);
	}
}