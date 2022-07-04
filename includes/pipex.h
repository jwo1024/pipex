
#ifndef PIPEX_H
# define PIPEX_H

 #include	"./libft_pipex.h"
 #include	"./get_next_line.h"


#include	<stdio.h>
#include	<unistd.h> // execve
#include	<stdlib.h>
#include	<fcntl.h>

typedef	struct s_info_fd
{
	int	file1;
	int	file2;
	int	pipe[2];
} t_info_fd ;

typedef struct s_info_which
{
	char	*which_cmd[3];
	int		pipe_fd[2];
} t_info_which;

typedef struct s_info_pipex
{
	int				argc;
	char			**argv;
	char			**envp;
	int				pid[2];
	int				status[2];
	t_info_fd		fd;
	t_info_which	which;

} t_info_pipex;

/* main */
int				pipex(t_info_pipex *info);
int				pipex_child_process(t_info_pipex *info, int cnt); // main
int				set_fd_dup(t_info_pipex *info, int cnt);


/*which _ utils*/
char			*which_cmd(char *cmd, char *envp[], t_info_which *which); // pipex main
t_info_which	*set_info_which(t_info_which *info);
void			clear_info_which(t_info_which *info);
void			remove_linefeed(char **str);
void			which_cmd_child(t_info_which *which, char *envp[]);

/*utils */
int				is_valid_files(char *file1, char *file2);
int				error(char	*message, int exit_num);
void			set_info_pipex(t_info_pipex *info , int argc, char *argv[], char *envp[]); // utils


#endif
