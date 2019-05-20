#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include <string.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <sys/wait.h>

#define MAX_LEN_LINE 21
#define LEN_HOSTNAME 30

int main(void)
{
        char command[MAX_LEN_LINE];
        char *args[] = {command, NULL};
        int ret, status;
        pid_t pid, cpid;
        char *ptr;

        /* GET HOSTNAME */
        char hostname[LEN_HOSTNAME +1];
        memset(hostname, 0x00, sizeof(hostname));
        gethostname(hostname, LEN_HOSTNAME);

        while(true){
                char *s;
                int len;

                printf("%s@%s $ ", getpwuid(getuid()) -> pw_name, hostname);
                s = fgets(command, MAX_LEN_LINE, stdin);
                if(s == NULL){
                        fprintf(stderr, "fgets failed \n");
                        exit(1);
                }

                len = strlen(command);
                printf("%d\n", len);
                if(command[len - 1] == '\n'){
                        command[len - 1] = '\0';
                }


                /* printf("[%s] \n", command); */

                ptr = strtok(command, " ;");
                while(ptr){
                        pid = fork();
                        if(pid < 0){
                                fprintf(stderr, "fork failed \n");
                                exit(1);
                        }

                        if(pid != 0){ /* parent */
                                cpid = waitpid(pid, &status, 0);
                                if(cpid != pid){
                                        fprintf(stderr, "waitpid failed \n");
                                }
                                printf("Child process terminated \n");
                                if(WIFEXITED(status)){
                                        printf("Exit status is %d \n", WEXITSTATUS(stat
us));
                                }
                        }
                        else{ /* child */
                                args[0] = ptr;
                                ret = execve(args[0], args, NULL);
                        if(ret < 0){
                                fprintf(stderr, "execve failed \n");
                                return 1;

                                }

                        }
                        ptr = strtok(NULL, " ;");
                }
                if(strcmp(args[0], "exit") == 0){
                        return 0;
                }


        }
        return 0;
}


