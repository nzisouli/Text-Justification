//This program creates processes that open other programs, which communicate through pipes
//to justify fully a text

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <errno.h>


int main (int argc, char *argv[]) {
	int P1_P2_fd[2], P2_P3_fd[2];
	pid_t P1, P2, P3;
	
	//pipe creation
	pipe (P1_P2_fd);
	pipe (P2_P3_fd);
	
	//create P1 process
	P1 = fork();
	if (P1 == 0) {
		close(P1_P2_fd[0]);
		//Redirect P1 output to pipe
		if (dup2(P1_P2_fd[1], STDOUT_FILENO) < 0) {
			perror ("Problem in P1-P2 i/o redirecting");
			exit (1);
		}
		close(P1_P2_fd[1]);
		execlp("./P1","P1", NULL);
		return 1;
	}
	
	close(P1_P2_fd[1]);
	
	//create P2 process
	P2 = fork();
	if (P2 == 0) {
		//Redirect P2 input to pipe
		if (dup2(P1_P2_fd[0], STDIN_FILENO) < 0) {
			perror ("Problem in P1-P2 i/o redirecting");
			exit (1);
		}
		close(P1_P2_fd[0]);
		
		close(P2_P3_fd[0]);
		//Redirect P2 output to pipe
		if (dup2(P2_P3_fd[1], STDOUT_FILENO) < 0) {
			perror ("Problem in P2-P3 i/o redirecting");
			exit (1);
		}
		close(P2_P3_fd[1]);
		
		execlp("./P2", "P2", argv[1], NULL);
	}
	
	close(P1_P2_fd[0]);
	close(P2_P3_fd[1]);
	
	//create P3 process
	P3 = fork();
	if (P3 == 0) {
		///Redirect P3 input to pipe
		if (dup2(P2_P3_fd[0], STDIN_FILENO) < 0) {
			perror ("Problem in P2-P3 i/o redirecting");
			exit (1);
		}
		close(P2_P3_fd[0]);
		
		execlp("./P3", "P3", NULL);
	}
	
	waitpid(P1, NULL, 0);
	waitpid(P2, NULL, 0);
	waitpid(P3, NULL, 0);
	
	exit(0);
}