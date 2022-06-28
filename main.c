#include	"main.h"

#include	<stdio.h>
#include	<unistd.h> // execve
#include	<stdlib.h>

//int	pipex(char *envp[]);
//int	pipe(char *envp[]);

int	which_cmd(char *cmd, char *envp[]);

int	main(int argc, char *argv[], char *envp[])
{
	char **split_arr;
	// execve path 얻기 // which cmd 로도 찾을 수 있음 (무엇이 더 좋은가?)

	if (argc >= 5)
	{
		which_cmd(argv[1], envp);
	}
	// argv cmd 파싱
	// argv[2] = file1, argv[argc-1] = file2;
	// argv[3 ~ argc-2] = cmd

	// file 유효성 검사
	// pipex()
	
	return (0);
}

int	which_cmd(char *cmd, char *envp[]) 	// which 파일은 항상 같은 곳에 위치하고 있는가 ? envp 사용해서 which 찾기
{
	char	**split_str;
	pid_t	pid;
	int		fd[2];
	int		status;
	// cmd 나누기
	split_str = ft_split_pipex(cmd, ' ');

/*
	int	i = 0;
	while (split_str[i])
	{
		printf("> %s\n", split_str[i]);
		i++;
	}
*/

//	pipe();

	pid = fork(); 
	// fork 실패시 별도 에러 처리

	if (pid == 0)
	{
		if (!execve("/usr/bin/which", split_str, envp)) //
			printf("fail execve");
	}

	wait(&status);

	printf("\n finish , status %d \n", status);

	return (0);
}

/*

int	pipe(char *envp[])
{

//	if (!execve(const char *path, char *const argv[], envp))
//	{

//	}
	return (0);
}

// file1을 표준 입력으로 만든다.
// cmd로 file1(표준입력)으로 입력을 받고, 

int	pipex(char *envp[])
{
	int	fd[2];
	int	file_fd;

	// fd = file1 열기

	while (0) // cmd count 
	{
		// fd 닫기
		// 새 pipe 만들기
		pipe(fd);


	//	fork -> cmd용 자식 프로세스

		dup2(1, fd[1]);
	//	dup 표준 출력을 pipe입력으로
	//	dup 표준 입력을 pipe출력으로 

	//	if (pid >= 0 cmd 자식프로세스일때)
	//	{
			// 해당 cmd의 argv 설정
	//		if (!execve(cons char *path, char *const argv[], envp))

			// cmd 가 유효하지 않으면 ? 
	//	}
	//	else if(pid = 0 부모 프로레스일때)


	//	pipe 닫기
	}

	//	wait 자식 프로세스 모두 종료될때까지
	// 오류로 (ex 입력이 필요한 프로세스에 입력이 없을때, 프로세스가 종료하지 않는다면 어떻게 처리를 해주어야 하는가?)
	// file2 에 저장

	return (0);
}

*/


/*
while (*envp)
	{
		printf("%s\n", *envp);
		(envp)++;
	}
	return (0);
*/