/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   promptgit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thugo <thugo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/24 19:44:56 by thugo             #+#    #+#             */
/*   Updated: 2017/10/25 03:34:26 by thugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include "minishell.h"
#include "libft.h"

static char	*get_branch(const char *path)
{
	int		gitfd;
	char	*gitpath;
	char	*gitbranch;
	char	buf[255];

	gitbranch = NULL;
	ft_bzero(buf, 255);
	if (!(gitpath = ft_strjoin(path, "/.git/HEAD")))
		exit(EXIT_FAILURE);
	if ((gitfd = open(gitpath, O_RDONLY)) < 0)
	{
		free(gitpath);
		return (NULL);
	}
	if (read(gitfd, buf, 255) >= 0)
	{
		if (!(gitbranch = ft_basename(buf)))
			exit(EXIT_FAILURE);
		gitbranch[ft_strlen(gitbranch) - 1] = '\0';
	}
	close(gitfd);
	free(gitpath);
	return (gitbranch);
}

static char	*path_get_back(char *cwd)
{
	char	*prev;
	char	*prevcwd;
	size_t	len;

	prevcwd = NULL;
	len = ft_strlen(cwd);
	prev = ft_strrchr(cwd, '/');
	if (!prev || (prev == cwd && len <= 1))
	{
		free(cwd);
		return (NULL);
	}
	if (!(prev - cwd) && !(prevcwd = ft_strdup("/")))
		exit(EXIT_FAILURE);
	if (!prevcwd && !(prevcwd = ft_strndup(cwd, prev - cwd)))
		exit(EXIT_FAILURE);
	free(cwd);
	return (prevcwd);
}

char		*promptgit_get(const char *cwd)
{
	char	*branch;
	char	*fbranch;
	char	*prevcwd;

	branch = get_branch(cwd);
	if (!(prevcwd = ft_strdup(cwd)))
		exit(EXIT_FAILURE);
	while (!branch && prevcwd)
	{
		ft_printf(">> %s$\n", prevcwd);
		if ((prevcwd = path_get_back(prevcwd)))
			branch = get_branch(prevcwd);
	}
	if (prevcwd)
		free(prevcwd);
	if (branch)
	{
		if (!(fbranch = ft_strfjoin("git:(\e[95;1m", 0, branch, 1)))
			exit(EXIT_FAILURE);
		if (!(fbranch = ft_strfjoin(fbranch, 1, "\e[0m) ", 0)))
			exit(EXIT_FAILURE);
		return (fbranch);
	}
	return (ft_strnew(0));
}
