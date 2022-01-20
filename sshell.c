#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define CMDLINE_MAX 512

int main(void)
{
        char cmd[CMDLINE_MAX];
        while (1) {
                char *nl;

                /* Print prompt */
                printf("sshell$ ");
                fflush(stdout);

                /* Get command line */
                fgets(cmd, CMDLINE_MAX, stdin);
                
                /* Print command line if stdin is not provided by terminal */
                if (!isatty(STDIN_FILENO)) {
                        printf("%s", cmd);
                        fflush(stdout);
                }

                /* Remove trailing newline from command line */
                nl = strchr(cmd, '\n');
                if (nl)
                        *nl = '\0';
                
                char command[CMDLINE_MAX];
                strcpy(command, cmd);
                
                /* Built-in Commands */
                if (!strcmp(cmd, "")) {
                        continue;
                }
                if (!strcmp(cmd, "exit")) {
                        printf("Bye...\n");
                        fprintf(stderr, "+ completed 'exit' [0]\n");
                        break;
                }
                if (!strcmp(cmd, "pwd")) {
                        char* buf = getcwd(NULL, 0);
                        int ret = 0;
                        if (buf == NULL) ret = 1;
                        printf("%s\n", buf);
                        fprintf(stderr, "+ completed 'pwd' [%d]\n", ret);
                        continue;
                }
                

                /* Regular Commands */
                char* arguments[16];
                char* token= strtok(cmd, " ");
                int argc = 0;
                while (token != NULL) {
                        arguments[argc++] = token;
                        token = strtok(NULL, " ");
                }
                argc++;       
                char* argList[argc];
                for (int i = 0; i < argc-1; i++) {
                        argList[i] = arguments[i];
                }
                argList[argc-1] = NULL;

                if (!strcmp(cmd, "cd")) {
                      int ret = chdir(argList[1]);
                      fprintf(stderr, "+ completed '%s' [%d]\n", command, ret);
                      continue;
                }

                pid_t pid;
                pid = fork();
                if (pid == 0) {
                        execvp(cmd, argList);
                        perror("Error");
                        exit(1);
                } else if (pid > 0) {
                        int status;
                        waitpid(pid, &status, 0);
                        fprintf(stderr, "+ completed '%s' [%d]\n", command, WEXITSTATUS(status));
                } else {
                        perror("fork");
                        exit(1);
                }

        }

        return EXIT_SUCCESS;
}