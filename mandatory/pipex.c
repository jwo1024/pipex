/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwolee <jiwolee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 17:25:09 by jiwolee           #+#    #+#             */
/*   Updated: 2022/07/04 19:31:53 by jiwolee          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include	"pipex.h"
#include	<stdio.h>
#include	<unistd.h> // execve
#include	<stdlib.h>
#include	<fcntl.h>

int	main(int argc, char *argv[], char *envp[])
{
	t_info_pipex	info;
	int				rtn;

	if (argc == 5)
	{
		set_info_pipex(&info, argc, argv, envp);
		if (set_info_which(&info.which) == NULL)
			; //	error(NULL, -1);
		rtn = pipex(&info);
		clear_info_which(&info.which);
	}
	else
		rtn = error("ERROR : Wrong number of argv ", 1);
//	system("leaks a.out");
	return (rtn);
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
			perror("Error : pipex() fail fork ");
		else if (info->pid[i] == 0)
			exit(pipex_child_process(info, i));
		i++;
	}
	close(info->fd.pipe[0]);
	close(info->fd.pipe[1]);
	waitpid(info->pid[0], &info->status[0], 0);
	waitpid(info->pid[1], &info->status[1], 0);
	if (info->status[0] == 0 && info->status[1] == 0)
		return (0);
	return (WEXITSTATUS(info->status[1]));
}

int	pipex_child_process(t_info_pipex *info, int cnt)
{
	char	**cmd_splited;
	char	*cmd_path;

	if (set_fd_dup(info, cnt) == 1)
		return (1);
	cmd_splited = ft_split(info->argv[cnt + 2], ' ');
	if (cmd_splited == NULL)
		return (error("ERROR : fail cmd split ", 1));
	cmd_path = which_cmd(cmd_splited[0], info->envp, &(info->which));
	if (cmd_path == NULL)
		return (error("ERROR : cmd path not found ", 127));
	execve(cmd_path, cmd_splited, info->envp);
	perror("ERROR : pipex_child_process() ");
	exit(EXIT_FAILURE);
}

int	set_fd_dup(t_info_pipex *info, int cnt)
{
	int	to_stdin;
	int	to_stdout;
	int	rtn_close;

	if (cnt == 0)
	{
		to_stdin = open(info->argv[1], O_RDONLY);
		to_stdout = info->fd.pipe[1];
		rtn_close = close(info->fd.pipe[0]); // close 실패도 처리 해주어야 할텐데 이렇게 하면 errno에 기록이 안될텐디..
	}
	else if (cnt == info->argc - 4)
	{
		to_stdin = info->fd.pipe[0];
		to_stdout = open(info->argv[info->argc - 1], \
					O_RDWR | O_CREAT | O_TRUNC, 0666);
		rtn_close = close(info->fd.pipe[1]);
	}
	else
		return (error("ERROR : set_fd_dup() wrong cnt ", -1));
	if (to_stdin != -1 && to_stdout != -1 && rtn_close != -1 \
		&& dup2(to_stdin, 0) != -1 && dup2(to_stdout, 1) != -1)
		return (0);
	return (error("ERROR : set_fd_dup() ", 1));
}
