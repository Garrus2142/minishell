/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thugo <thugo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/25 01:55:07 by thugo             #+#    #+#             */
/*   Updated: 2017/11/01 03:22:36 by thugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include "libft.h"
#include "minishell.h"

pid_t	g_runpid = 0;

static int	execute(t_data *data, char *path, char **args)
{
	char	stats;
	int		stat_loc;

	stats = stats_check(path);
	if (!(stats & STATS_EXIST) || !(stats & STATS_EXEC) || (stats & STATS_DIR))
	{
		if (!(stats & STATS_EXIST))
			ft_dprintf(2, "minishell: no such file or directory: %s\n", path);
		else if ((stats & STATS_DIR))
			ft_dprintf(2, "minishell: is a directory: %s\n", path);
		else if (!(stats & STATS_EXEC))
			ft_dprintf(2, "minishell: permission denied: %s\n", path);
		return (127);
	}
	if (!(g_runpid = fork()))
		execve(path, args, data->envtab);
	waitpid(g_runpid, &stat_loc, 0);
	g_runpid = 0;
	if (WIFEXITED(stat_loc))
		return (WEXITSTATUS(stat_loc));
	else if (WIFSIGNALED(stat_loc))
		return (128 + WTERMSIG(stat_loc));
	return (0);
}

static char	*find_cmd(char *path, char *name)
{
	DIR				*dir;
	struct dirent	*dirent;
	char			stats;
	char			*cmdpath;

	stats = stats_check(path);
	cmdpath = NULL;
	if ((stats & STATS_EXIST) && (stats & STATS_EXEC) && (stats & STATS_DIR)
		&& (dir = opendir(path)))
	{
		while (!cmdpath && (dirent = readdir(dir)))
		{
			if (!ft_strcmp(dirent->d_name, name) && ft_strcmp(
				dirent->d_name, ".") && ft_strcmp(dirent->d_name, ".."))
			{
				if (!(cmdpath = ft_strfjoin(ft_strjoin(path, "/"), 1, name, 0)))
					exit(EXIT_FAILURE);
			}
		}
		closedir(dir);
	}
	return (cmdpath);
}

static char	*find_path(t_data *data, char *name)
{
	char			**paths;
	char			*path;
	int				i;

	if (!env_get(data, "PATH"))
		return (NULL);
	if (!(paths = ft_strsplit(env_get(data, "PATH"), ':')))
		exit(EXIT_FAILURE);
	path = NULL;
	i = 0;
	while (!path && paths[i])
		path = find_cmd(paths[i++], name);
	ft_tabptrfree((void ***)&paths);
	return (path);
}

void		exec_execute(t_data *data, char **cmd)
{
	char	*path;

	if (builtin_execute(data, cmd))
		return ;
	else if (ft_strchr(cmd[0], '/'))
		data->exec_stat = execute(data, cmd[0], cmd);
	else if ((path = find_path(data, cmd[0])))
	{
		data->exec_stat = execute(data, path, cmd);
		free(path);
	}
	else
		ft_dprintf(2, "minishell: command not found: %s\n", cmd[0]);
}
