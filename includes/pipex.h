/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwolee <jiwolee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 19:45:58 by jiwolee           #+#    #+#             */
/*   Updated: 2022/07/06 01:30:34 by jiwolee          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include	"./libft_pipex.h"
# include	"./get_next_line.h"

typedef struct s_info_fd
{
	int	file1;
	int	file2;
	int	pipe[2];
}	t_info_fd;

typedef struct s_info_which
{
	char	*which_cmd[3];
	int		pipe_fd[2];
}	t_info_which;

typedef struct s_info_pipex
{
	int				argc;
	char			**argv;
	char			**envp;
	pid_t			pid[2]; // pid_t 로 변경해야 한다.
	int				status[2];
	t_info_fd		fd;
	t_info_which	which;

}	t_info_pipex;

int				pipex(t_info_pipex *info);
int				pipex_child_process(t_info_pipex *info, int cnt);
int				set_fd_dup(t_info_pipex *info, int cnt);
char			*which_cmd(char *cmd, char *envp[], t_info_which *which);
t_info_which	*set_info_which(t_info_which *info);
void			clear_info_which(t_info_which *info);
void			which_cmd_child(t_info_which *which, char *envp[]);
char			*which_cmd_parent(pid_t pid, t_info_which *which);
int				is_valid_files(char *file1, char *file2);
int				error(char	*message, int exit_num);
void			set_info_pipex(t_info_pipex *info, \
							int argc, char *argv[], char *envp[]);
void			remove_linefeed(char **str);
int				wait_exit_status(int status);

#endif
