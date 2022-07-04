#include	<stdio.h>
#include	<fcntl.h>
#include	<unistd.h>
#include	<sys/wait.h>

/*
int	main(void)
{
	int	fd;

	fd = open("./newfile.txt", O_RDWR); // 안됨
	write(fd, "hello\n", 10);
	printf("fd %d\n", fd);
	close(fd);
	return (0);
}
*/


int	main(int argc, char *argv[], char *envp[])
{
	int		pid[2];
	int		fd[2];
	int		pipe_fd[2];
	int		status;

	char	*cmd_argv[3];
	char	*cmd = "head";
	char	*file = "test.txt";
	int		fileout;
	int		filein;

	if (1) //
	{
		
		
		pipe(pipe_fd);
	
	//	dup2(pipe_fd[1], 1);
	//	fprintf(pipe_fd[1], "hellow world\nnice to meet you\n");
		write(pipe_fd[1], "hellow world\nlonely world\n", 30);
		
		char buf[50];

		//read(pipe_fd[0], buf, 30);
		//printf("buf %s", buf);
		cmd_argv[0] = cmd;
		cmd_argv[1] = NULL;
	//	cmd_argv[1] = NULL;

		pid[0] = fork();
		if (pid[0] == 0)
		{
			fileout = open("test.txt", O_RDWR | O_CREAT | O_TRUNC, 0777);
			filein = open("test2.txt", O_RDWR);
			dup2(filein, 0);
			dup2(fileout, 1);
		//	printf("aaa\n");
			close(pipe_fd[1]);
			execve("/bin/head", cmd_argv, envp);
		}
		else
		{
			close(pipe_fd[0]);
			close(pipe_fd[1]);

		
		//while(wait(NULL) != -1)
		//	printf("wait\n");
	/*	int r = 1;
		while (r != -1)
		{
			r = waitpid(0, &status, WNOHANG | WUNTRACED);
			if (r > 0)
			{
				printf("wait status%d r %d\n", status, r);
				printf("wexitstatus %d\n", WEXITSTATUS(status));
			}
		}*/		close(pipe_fd[0]);

			waitpid(pid[0], &status, 0);
			printf("catch %d\n", pid[0]);
		}
	//	waitpid(pid[1], &status, 0);
	//	printf("catch pid2 %d\n", pid[1]);

	
	}


//	system("leaks a.out");
	return (0);
}
