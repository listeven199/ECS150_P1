sshell : sshell.o
	gcc sshell.o -o sshell
sshell.o : sshell.c
	gcc -Wall -Werror -Wextra -c sshell.c
clean :
	-rm *.o sshell