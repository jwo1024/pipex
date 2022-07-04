#include	"pipex.h"

// access, perror

int	is_valid_files(char *file1, char *file2)
{
	if (access(file1, R_OK) != 0) // access 함수는 성공시 0 반환 
		return (error("File1 is invalid ", -1));
	else if (access(file2, F_OK) == 0 && access(file2, W_OK) != 0)
		return (error("File2 is invalid ", -1));
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
		perror("Error");
	return (exit_num);
}

void	set_info_pipex(t_info_pipex *info , int argc, char *argv[], char *envp[])
{
	info->argc = argc;
	info->argv = argv;
	info->envp = envp;
}
