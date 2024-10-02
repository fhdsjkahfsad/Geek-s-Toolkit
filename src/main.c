#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
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
        printf("opts:\n 42 to quit\n 1 to draw ghost\n 2 run command\n192 to check syslog (linux)\n242 to enter root terminal\n246 to dump memory\n119 to read mem at address\n");
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
    
        
        } else if (opt == 242) {
            int ynroot;
            printf("You are about to enter root shell. Continue? (y: 1/n: 2) >>>");
            scanf("%i", &ynroot);
            if (ynroot == 1) {
                system("/bin/sh");
            } else {
                printf("will not enter shell\n");
            }
        }
        else if (opt == 246) {
            uintptr_t *stack_ptr;
            uintptr_t base_address;
    
   
            __asm__ volatile ("mov %%rsp, %0" : "=r"(stack_ptr));

            printf("Stack pointer: %p\n", (void *)stack_ptr);

    
            printf("Dumping stack memory:\n");
            for (int i = -10; i <= 10; i++) {
                printf("Address %p: ", (void *)(stack_ptr + i));
                // Cast to uintptr_t to avoid type issues
                printf("%lx\n", *(uintptr_t *)(stack_ptr + i));
            }
            
        } 
        else if (opt == 119) {
            uintptr_t address;
            printf("Enter address (only can read string values): ");
            scanf("%lx", &address);
            char *ptr = (char*)address;

            // Read the memory safely
            char buffer[100];  // Buffer to store the string
            memset(buffer, 0, sizeof(buffer)); // Clear the buffer

            // Attempt to read a string from the given address
            for (int i = 0; i < sizeof(buffer) - 1; i++) {
                // Attempt to read each byte
                if (ptr[i] == '\0') break; // Stop at null terminator
                buffer[i] = ptr[i]; // Copy the byte
            }

            printf("Data at %lx: %s\n", (unsigned long)address, buffer);

        } else {
            printf("could not find command %i\n", opt);
        }
        
        
        
        
    }
    free(name);
    name = NULL;


}


