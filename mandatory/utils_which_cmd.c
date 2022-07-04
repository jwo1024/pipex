/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_which_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwolee <jiwolee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 17:25:35 by jiwolee           #+#    #+#             */
/*   Updated: 2022/07/04 18:58:57 by jiwolee          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include	"pipex.h"

char	*which_cmd(char *cmd, char *envp[], t_info_which *which)
{
	pid_t	pid;
	int		status;
	char	*cmd_path;

	if (pipe(which->pipe_fd) == -1)
		return (NULL);
	if (cmd == NULL)
		return (NULL);
	which->which_cmd[1] = cmd;
	pid = fork();
	if (pid == -1)
		return (NULL);
	else if (pid == 0) // 자식 프로세스일 경우에
		which_cmd_child(which, envp);
	else
	{
		close(which->pipe_fd[1]);
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
		{
			cmd_path = get_next_line(which->pipe_fd[0]);
			remove_linefeed(&cmd_path); // gnl 에 합치기 
			close(which->pipe_fd[0]);
			return (cmd_path);
		}
	}
	close(which->pipe_fd[0]);
	return (NULL);
}

void	which_cmd_child(t_info_which *which, char *envp[])
{
	close(which->pipe_fd[0]);
	dup2(which->pipe_fd[1], 1);
	execve("/usr/bin/which", which->which_cmd, envp);
	exit(EXIT_FAILURE);
}

int	which_cmd_parent()
{
	return (1);
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
