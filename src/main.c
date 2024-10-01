#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
int main(int argc, char* argv[]) {
    
    printf("Welcome to the toolkit for geeks!\n");
    char* name = (char*)malloc(20 * sizeof(char));
    if (name == NULL) {
        printf("Error: could not allocate mem");
        exit(1);
    }
    if (argv[1] == NULL) {
        printf("Enter a name dummy\n");
    }
    strcpy(name, argv[1]);
    printf("name at %p \n", &name);
    while(1) {
        
        int opt;
        printf("Hey %s, What would you like to do?\n", name);
        printf("opts:\n 42 to quit\n 1 to draw ghost\n 2 run command\n192 to check syslog (linux)\n");
        printf(">>>");
        scanf("%i", &opt);
        if (opt == 42) {
            printf("goodbye %s. we are about to free the memory storing your name. goodbye\n", name);
            break;
        } else if (opt == 1) {
            printf("oo\n_\n||\n");
        } else if (opt == 2) {
            char* command;
            printf(">>>");
            scanf("%s", command);
            int status = system(command);
            if (status == -1) {
                printf("\033[0;31mSyscalls offline\033[0m\n");
            } else {
                printf("\033[0;32mSyscalls online.\033[0m\n");
            }
        } else if (opt == 192) {
            system("clear");
            FILE *fp = popen("journalctl", "r");
            if (fp == NULL) {
                perror("Failed to run journalctl");
                return EXIT_FAILURE;
            }

            char buffer[256];
            while (fgets(buffer, sizeof(buffer), fp) != NULL) {
                printf("%s", buffer);
            }

            pclose(fp);
    
        
        } else {
            printf("could not find command %i\n", opt);
        }
        
        
        
        
    }
    free(name);
    name = NULL;


}


