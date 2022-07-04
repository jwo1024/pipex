
#include	"pipex.h"

#include	<stdio.h>
#include	<unistd.h> // execve
#include	<stdlib.h>
#include	<fcntl.h>

// ../pipex

// fork malloc free


// cmd가 입력 되었을 때 
// cmd 수가 적을때
// cmd 
// file1 이 없는 파일, 혹은 권한이 없는 파일
// 없는 cmd일 때
// 


// 에러 함수를 이용한 에러처리는 최대한 최상위 함수에서
// error() 함수 처리 /// 아니 errno 처리는
// 제외하는 곳은 자식 프로세스에서의 에러 함수..


int	main(int argc, char *argv[], char *envp[])
{
	t_info_pipex	info;
	int				rtn;

	if (argc == 5) // bonus 안할꺼면 argc == 5
	{
		if (is_valid_files(argv[1], argv[argc - 1]) == -1)
		{
			rtn = error("Invalid file", -1);
		}
		set_info_pipex(&info, argc, argv, envp);
		if (set_info_which(&info.which) == NULL)
			;
		//	error(NULL, -1);
		rtn = pipex(&info);

//		printf("parent finsih\n");
		clear_info_which(&info.which);
	}
	else
	{
		rtn = error("Too few argv", 1); // errno 에 해당하는 출력이 아니면 일반 에러를 출력해야 한다. 
	}
//	sleep(30);
//	system("leaks a.out");
	if (rtn != 0)
		return (1);
	return (0);
}


int	pipex(t_info_pipex *info)
{
	int	i;

	if (pipe(info->fd.pipe) == -1)
		return (error("Error : pipex() fail pipe ", -1));
	i = 0;
	while (i < 2)
	{
		info->pid[i] = fork();
		if (info->pid[i] == -1)
		{
			perror("Error : pipex() fail fork ");
			break;
		}
		else if (info->pid[i] == 0) // 자식프로세스
		{
			i = cmd_child_process(info, i);
			exit(i); // ? 
		}
		i++;
	}
	close(info->fd.pipe[0]);
	close(info->fd.pipe[1]);
	waitpid(info->pid[0], &info->status[i], 0);
	waitpid(info->pid[1], &info->status[i], 0); // 이것도 에러 처리 해야하나?
	fprintf(stderr, "status %d %d \n", WEXITSTATUS(info->status[0]),  WEXITSTATUS(info->status[1]));

	if (info->status[0] == 0 && info->status[1] == 0)
		return (0);

	fprintf(stderr, "status %d\n", info->status[1]);
	return (1);

	exit(info->status[1]);
}


int		cmd_child_process(t_info_pipex *info, int cnt) // child proccess
{
	char	**cmd_splited;
	char	*cmd_path;

	cmd_splited = ft_split(info->argv[cnt + 2], ' ');
	if (cmd_splited == NULL)
		return(error("ERROR : fail split ", 1)); // exit 로 설정해야하나?????
	cmd_path = which_cmd(cmd_splited[0], info->envp, &(info->which)); // 요 경우만 따로 처리해주어야 하나? undifined behaior 이니까 .
	if (cmd_path == NULL) // 여기서 중단시키는 것이 맞나? ? 
	{
		error("ERROR : cmd not found ", 127);
		exit(127);
		error("WORNG WORKING", -1);
		//return (error("ERROR : cmd not found ", -1)); // return error ; // 그래도 outfile을 새로 만들긴 해야한다. 
	}
	if (set_fd_dup(info, cnt) == 1) // 안에서 에러 메세지 띄움 /////// 
		return (1); // 여기도 return으로 바꿔야 할까 nono.... /??????////// // exit(1); 갈겨야 하지 않을까...
	execve(cmd_path, cmd_splited, info->envp);
	perror("ERROR : cmd_child_process() ");
	exit(EXIT_FAILURE);
}

int		set_fd_dup(t_info_pipex *info, int cnt)
{
	int	to_stdin;
	int	to_stdout;
	int	rtn_close; // ..

	if (cnt == 0)
	{
		to_stdin = open(info->argv[1], O_RDONLY);
		to_stdout = info->fd.pipe[1];
		rtn_close = close(info->fd.pipe[0]); // close 실패도 처리 해주어야 할텐데 이렇게 하면 errno에 기록이 안될텐디..
	}
	else if (cnt == info->argc - 4)
	{
		to_stdin = info->fd.pipe[0];
		to_stdout = open(info->argv[info->argc - 1], O_RDWR | O_CREAT | O_TRUNC, 0666); //
		rtn_close = close(info->fd.pipe[1]);
	}
	else
		return (error("ERROR : set_fd_dup()", -1));
	if (to_stdin != -1 && to_stdout != -1 && rtn_close != -1 \
		&& dup2(to_stdin, 0) != -1 && dup2(to_stdout, 1) != -1)
		return (0);
	return (error("ERROR : set_fd_dup()", 1));
}
