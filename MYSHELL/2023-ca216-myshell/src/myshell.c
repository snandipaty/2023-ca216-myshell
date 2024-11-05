//Name:Siri Nandipaty student id:21449384
#include <string.h>
#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#define MAX_BUFFER 1024                        // max line buffer
#define MAX_ARGS 64                            // max # args
#define SEPARATORS " \t\n"
#include "internal.c"
//#include "exec.c"                   // token separators

char prompt[MAX_BUFFER];
int main (int argc, char ** argv)
{{
    char buf[MAX_BUFFER];                      // line buffer
    char * args[MAX_ARGS];                     // pointers to arg strings
    char ** arg;                               // working pointer thru args                  // shell prompt
    /* keep reading input until "quit" command or eof of redirected input */

    while (!feof(stdin)) { 
        /* get command line from input */
        char cwd[MAX_BUFFER];
        if (getcwd(cwd, sizeof(cwd)) != NULL) {
            sprintf(prompt, "%s>", cwd, prompt);
        } else {
            sprintf(prompt, "%s>", prompt);
        }

        fputs(prompt, stdout); 

        if (fgets (buf, MAX_BUFFER, stdin )) { // read a line
            /* tokenize the input into args array */
            arg = args;
            *arg++ = strtok(buf,SEPARATORS);   // tokenise input

            while ((*arg++ = strtok(NULL,SEPARATORS)));

            // last entry will be NULL 
            if (args[0]) {                     // if there's anything there
                /* check for internal/external command */
                if (!strcmp(args[0],"clear")) { // "clear" command
                    internalclr(args);
                    continue;
                }

                if (!strcmp(args[0],"quit"))   // "quit" command
                    break;

                if (!strcmp(args[0],"pause")){
                    internalpause(args);
                    continue;
                }                    
                
                if (!strcmp(args[0], "dir")) {
                    internaldir(args);
                    continue;}


                if (!strcmp(args[0], "environ")){
                    internalenviron(args);
                    continue;        
                }

                if (!strcmp(args[0], "echo")){
                    internalecho(args);
                    continue;
                }
                if(!strcmp(args[0], "cd")){
                    internalcd(args);
                    continue;
                }

            }
        }
        else{
            execute_command(args);}

    }
    return 0; 
}}


