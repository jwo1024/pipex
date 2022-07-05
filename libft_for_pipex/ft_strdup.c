/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwolee <jiwolee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 17:23:23 by jiwolee           #+#    #+#             */
/*   Updated: 2022/07/06 01:35:31 by jiwolee          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include	"libft_pipex.h"

char	*ft_strdup(char *src)
{
	int		i;
	int		len;
	char	*new;

	len = ft_strlen(src);
	new = (char *)malloc(sizeof(char) * (len + 1));
	if (new == 0)
		return (NULL);
	i = 0;
	while (src[i] != 0)
	{
		new[i] = src[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}
