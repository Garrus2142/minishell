/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thugo <thugo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/25 02:43:07 by thugo             #+#    #+#             */
/*   Updated: 2017/11/01 03:19:40 by thugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <sys/param.h>
#include "minishell.h"

static int	can_change(char *path)
{
	char	stats;

	stats = stats_check(path);
	if (ft_strlen(path) && (!(stats & STATS_EXIST) || !(stats & STATS_EXEC) ||
		!(stats & STATS_DIR)))
	{
		if (!(stats & STATS_EXIST))
			ft_dprintf(2, "cd: no such file or directory: %s\n", path);
		else if (!(stats & STATS_DIR))
			ft_dprintf(2, "cd: not a directory: %s\n", path);
		else if (!(stats & STATS_EXEC))
			ft_dprintf(2, "cd: permission denied: %s\n", path);
		return (0);
	}
	return (1);
}

static char	*get_lpath(t_data *data, char *path)
{
	char	**splitpath;
	char	*lpath;
	int		i;

	splitpath = ft_strsplit(path, '/');
	if (path[0] == '/')
		lpath = ft_strnew(0);
	else if (env_get(data, "PWD"))
		lpath = ft_strdup(env_get(data, "PWD"));
	else
		lpath = getcwd(NULL, 0);
	if (!splitpath || !lpath)
		exit(EXIT_FAILURE);
	i = 0;
	while (splitpath[i])
	{
		if (!ft_strcmp(splitpath[i], "..") && ft_strlen(lpath) > 1)
			lpath = ft_strnfdup(lpath, ft_strrchr(lpath, '/') - lpath);
		else if (ft_strcmp(splitpath[i], ".") && ft_strcmp(splitpath[i], ".."))
			lpath = ft_strfjoin(lpath, 1, ft_strjoin("/", splitpath[i]), 1);
		if (++i && !lpath)
			exit(EXIT_FAILURE);
	}
	ft_tabptrfree((void ***)&splitpath);
	return ((lpath = ft_strlen(lpath) ? lpath : ft_strfjoin(lpath, 1, "/", 0)));
}

static int	changedir(t_data *data, char *path, char *cmd)
{
	char	cwd[MAXPATHLEN];

	if (!can_change(cmd ? cmd : path))
		return (1);
	if (!env_get(data, "PWD"))
		env_set(data, "OLDPWD", getcwd(cwd, MAXPATHLEN));
	else
		env_set(data, "OLDPWD", env_get(data, "PWD"));
	cwd_change(data, path);
	return (0);
}

static char	*resolve_path(t_data *data, int argc, char **argv, int index)
{
	char	*path;

	if (index >= argc)
	{
		if (!(path = env_get(data, "HOME")))
		{
			ft_dprintf(2, "cd: HOME not set\n");
			return (NULL);
		}
	}
	else if (!ft_strcmp(argv[index], "-"))
	{
		if (!(path = env_get(data, "OLDPWD")))
		{
			ft_dprintf(2, "cd: OLDPWD not set\n");
			return (NULL);
		}
	}
	else
		path = argv[index];
	return (path);
}

int			builtin_cd(t_data *data, int argc, char **argv)
{
	char	*path;
	char	*lpath;
	char	*options;
	int		index;
	int		ret;

	if ((index = ft_getopt(argc, argv, "LP", &options)) == -1)
	{
		ft_dprintf(2, "cd: bad option: -%c\n", *options);
		return (EXIT_FAILURE);
	}
	if (!(path = resolve_path(data, argc, argv, index)))
		return (1);
	if (ft_strchr(options, 'P'))
		ret = changedir(data, path, NULL);
	else
	{
		lpath = get_lpath(data, path);
		ret = changedir(data, lpath, path);
		free(lpath);
	}
	free(options);
	return (ret);
}
