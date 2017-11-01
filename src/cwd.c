/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thugo <thugo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/01 01:37:11 by thugo             #+#    #+#             */
/*   Updated: 2017/11/01 03:18:31 by thugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <sys/param.h>
#include "minishell.h"

static int	try(t_data *data, char *path)
{
	char	stats;

	ft_dprintf(2, "minishell: Trying to start from \"%s\"\n", path);
	stats = stats_check(path);
	if ((stats & STATS_EXIST) && (stats & STATS_EXEC) && (stats & STATS_DIR))
	{
		cwd_change(data, path);
		return (1);
	}
	return (0);
}

void		cwd_init(t_data *data)
{
	char	stats;

	stats = 0;
	if ((data->cwd = getcwd(NULL, 0)))
		stats = stats_check(data->cwd);
	if (!data->cwd || !(stats & STATS_EXEC) || (!stats & STATS_EXIST))
	{
		if (!(stats & STATS_EXIST))
			ft_putstr_fd("minishell: No such file or directory\n", 2);
		else
			ft_putstr_fd("minishell: Permission denied\n", 2);
		if (env_get(data, "HOME") && try(data, env_get(data, "HOME")))
			return ;
		else if (try(data, "/"))
			return ;
		exit(EXIT_FAILURE);
	}
	if (!stats_filecmp(data->cwd, env_get(data, "PWD")))
		env_set(data, "PWD", data->cwd);
	chdir(data->cwd);
}

void		cwd_change(t_data *data, const char *path)
{
	chdir(path);
	if (data->cwd)
		free(data->cwd);
	if (path[0] == '/')
	{
		env_set(data, "PWD", path);
		if (!(data->cwd = ft_strdup(path)))
			exit(EXIT_FAILURE);
	}
	else
	{
		data->cwd = getcwd(NULL, 0);
		if (data->cwd)
			env_set(data, "PWD", data->cwd);
	}
}

void		cwd_destroy(t_data *data)
{
	free(data->cwd);
}
