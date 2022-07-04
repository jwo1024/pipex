/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwolee <jiwolee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 17:25:26 by jiwolee           #+#    #+#             */
/*   Updated: 2022/07/04 21:52:40 by jiwolee          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include	"pipex.h"

int	is_valid_files(char *file1, char *file2)
{
	if (access(file1, R_OK) != 0)
		return (error("ERROR : File1 is invalid ", -1));
	else if (access(file2, F_OK) == 0 && access(file2, W_OK) != 0)
		return (error("ERROR : File2 is invalid ", -1));
	return (1);
}

void	remove_linefeed(char **str)
{
	int	len;

	len = ft_strlen(*str);
	if ((*str)[len - 1] == '\n')
		(*str)[len - 1] = '\0';
}

int	error(char	*message, int exit_num)
{
	if (message)
		perror(message);
	else
		perror("ERROR ");
	return (exit_num);
}

void	set_info_pipex(t_info_pipex *info, int argc, char *argv[], char *envp[])
{
	info->argc = argc;
	info->argv = argv;
	info->envp = envp;
}

int	wait_exit_status(int status)
{
	return (status >> 8);
}
