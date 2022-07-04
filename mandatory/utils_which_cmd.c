#include	"pipex.h"

/* which utils */

// cmd 경로를 가져오는 함수. 
// which 파일은 항상 같은 곳에 위치하고 있는가 ? envp 사용해서 which 찾기 // 변수로 which_path 넣기
char	*which_cmd(char *cmd, char *envp[], t_info_which *which) // const char cmd ?
{
	pid_t	pid;
	int		status;
	char	*cmd_path;

	if (pipe(which->pipe_fd) == -1) //에러 처리 메시지 어떻게 할가요 ? 
		return (NULL);
	if (cmd == NULL)
		return (NULL);
	which->which_cmd[1] = cmd; // cmd 가 빈칸일때 처리
	pid = fork();
	if (pid == -1)
		return (NULL); // return 으로 처리
	else if (pid == 0) // 자식 프로세스일 경우에
	{	
		close(which->pipe_fd[0]);
		dup2(which->pipe_fd[1], 1);
		execve("/usr/bin/which", which->which_cmd, envp);
		perror("Error : which_cmd()");
		exit(EXIT_FAILURE);
	}
	else
	{

		close(which->pipe_fd[1]);
		waitpid(pid, &status, 0);
		if (status == 0) // 정상종료시 0 // status의 값과 $? 에대해서 알 필요가 있어 // 조건 다시 생각
		{
			cmd_path = get_next_line(which->pipe_fd[0]);
		
			remove_linefeed(&cmd_path); // gnl 에 합치기 
			close(which->pipe_fd[0]);
			return (cmd_path);
		}
		close(which->pipe_fd[0]);
		return (NULL); //
	}
}

t_info_which	*set_info_which(t_info_which	*info)
{
	info->which_cmd[0] = ft_strdup("which");
	if (info->which_cmd[0] == NULL)
		return (NULL);
	info->which_cmd[1] = NULL;
	info->which_cmd[2] = NULL;
	return (info);
}

void	clear_info_which(t_info_which *info)
{
	if (!info)
		return;
	free(info->which_cmd[0]);
}
