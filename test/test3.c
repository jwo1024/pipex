#include	<stdio.h>
#include	<fcntl.h>
#include	<unistd.h>
#include	<sys/wait.h>


int	p1(int pipe_fd[2], char **envp)
{
	int	file_fd;
	char *argv[3];
	char cmd[] = "ls";

	argv[0] = cmd;
	argv[1] = NULL;

	close(pipe_fd[0]);
	file_fd = open("./file13.txt", O_RDONLY);
	dup2(file_fd, 0);
	dup2(pipe_fd[1], 1);
	execve("/bin/ls", argv, envp);
	return (1);
}

int	p2(int pipe_fd[2], char **envp)
{
	int	file_fd;
	char *argv[3];
	char cmd[] = "cat";
	char	buf[100];

	argv[0] = cmd;
	argv[1] = NULL;
	close(pipe_fd[1]);

//	sleep(5);
//	read(pipe_fd[0], buf, 30);
//	printf("p2 buf %s\n", buf);

	
	file_fd = open("./file23.txt", O_WRONLY | O_CREAT | O_TRUNC);
	dup2(pipe_fd[0], 0);
	dup2(file_fd, 1);
	execve("/bin/cat", argv, envp);
	return (1);
}


int	main(int argc, char *argv[], char *envp[])
{
	int	pipe_fd[2][2];
	int	pipey_fd[2];
	int	pid1;
	int	pid2;
	int	status;
	char	buf[100];


	
	pipe(pipe_fd[0]); // pid1 -> parent 
//	pipe(pipe_fd[1]); // parent -> pid2

	
	pid1 = fork();
	if (pid1 == 0)
	{
		p1(pipe_fd[0],envp);
	}

	pid2 = fork();
	if (pid2 == 0)
	{
		p2(pipe_fd[0], envp);
	}
	
	close(pipe_fd[0][1]);
	close(pipe_fd[0][0]);

	waitpid(pid1, &status, 0);
	waitpid(pid2, &status, 0);

	return (0);
}