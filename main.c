#include	<stdio.h>
#include	<unistd.h> // execve
#include	<stdlib.h>

int	pipex(char *envp[]);
int	pipe(char *envp[]);


int	main(int argc, char *argv[], char *envp[])
{
	// execve path 얻기 // which cmd 로도 찾을 수 있음 (무엇이 더 좋은가?)

	if (argc >= 5)
	{

		pipe(envp);
	}
	// argv cmd 파싱
	// argv[2] = file1, argv[argc-1] = file2;
	// argv[3 ~ argc-2] = cmd

	// file 유효성 검사
	// pipex()
	
	return (0);
}

int	which_cmd();

int	pipe(char *envp[])
{

	if (!execve(const char *path, char *const argv[], envp))
	{

	}

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

	// file2 에 저장

	return (0);
}

/*
while (*envp)
	{
		printf("%s\n", *envp);
		(envp)++;
	}
	return (0);
*/