# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jiwolee <jiwolee@student.42seoul.kr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/22 15:27:03 by jiwolee           #+#    #+#              #
#    Updated: 2022/07/06 02:15:38 by jiwolee          ###   ########seoul.kr   #
#                                                                              #
# **************************************************************************** #

NAME	= pipex

CC		= gcc
CFLAG	= -Wall -Wextra -Werror

HEADER	= ./includes
INCLUDES = -I$(HEADER)

SRCS_1	= mandatory/pipex.c\
		  mandatory/utils_which_cmd.c\
		  mandatory/utils.c

SRCS_2	= gnl_for_pipex/get_next_line.c\
		  gnl_for_pipex/get_next_line_utils.c

SRCS_3	= libft_for_pipex/ft_split.c\
		  libft_for_pipex/ft_strlcpy.c\
		  libft_for_pipex/ft_strlen.c\
		  libft_for_pipex/ft_substr.c\
		  libft_for_pipex/ft_strdup.c

SRCS	= $(SRCS_1) $(SRCS_2) $(SRCS_3)

OBJS	= $(SRCS:.c=.o)

%.o : %.c
	$(CC) $(CFLAG) $(INCLUDES) -c -o $@ $^

all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(CFLAG) $(INCLUDES) -o $@ $^

clean :
	rm -f $(OBJS)

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY : all clean fclean re
