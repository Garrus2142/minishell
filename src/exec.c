/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thugo <thugo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/25 01:55:07 by thugo             #+#    #+#             */
/*   Updated: 2017/11/02 02:11:18 by thugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <signal.h>
#include "libft.h"
#include "minishell.h"

static int	print_signal(int sig)
{
	if (sig == SIGQUIT)
		ft_putstr_fd("Quit\n", 2);
	else if (sig == SIGILL)
		ft_putstr_fd("Illegal instruction\n", 2);
	else if (sig == SIGABRT)
		ft_putstr_fd("Abort\n", 2);
	else if (sig == SIGKILL)
		ft_putstr_fd("Killed\n", 2);
	else if (sig == SIGBUS)
		ft_putstr_fd("Bus error\n", 2);
	else if (sig == SIGSEGV)
		ft_putstr_fd("Segmentation fault\n", 2);
	else if (sig == SIGPIPE)
		ft_putstr_fd("Broken pipe\n", 2);
	else if (sig == SIGALRM)
		ft_putstr_fd("Alarm clock\n", 2);
	return (128 + sig);
}

static int	execute(t_data *data, char *path, char **args)
{
	char	stats;
	int		stat_loc;

	stats = stats_check(path);
	if (!(stats & STATS_EXIST) || !(stats & STATS_EXEC) || (stats & STATS_DIR))
	{
		ft_putstr_fd(data->namesh, 2);
		if (!(stats & STATS_EXIST))
			ft_dprintf(2, ": no such file or directory: %s\n", path);
		else if ((stats & STATS_DIR))
			ft_dprintf(2, ": is a directory: %s\n", path);
		else if (!(stats & STATS_EXEC))
			ft_dprintf(2, ": permission denied: %s\n", path);
		return (127);
	}
	if (!(data->runpid = fork()))
		execve(path, args, data->envtab);
	waitpid(data->runpid, &stat_loc, 0);
	data->runpid = 0;
	if (WIFEXITED(stat_loc))
		return (WEXITSTATUS(stat_loc));
	else if (WIFSIGNALED(stat_loc))
		return (print_signal(WTERMSIG(stat_loc)));
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

static char	*find_path(t_data *data, char *name, char *recoverpath)
{
	char			**paths;
	char			*path;
	char			*envpath;
	int				i;

	if (!(envpath = env_get(data, "PATH")))
		envpath = recoverpath;
	if (!envpath)
		return (NULL);
	if (!(paths = ft_strsplit(envpath, ':')))
		exit(EXIT_FAILURE);
	path = NULL;
	i = 0;
	while (!path && paths[i])
		path = find_cmd(paths[i++], name);
	ft_tabptrfree((void ***)&paths);
	return (path);
}

void		exec_execute(t_data *data, char **cmd, char *recoverpath)
{
	char	*path;

	if (builtin_execute(data, cmd))
		return ;
	else if (ft_strchr(cmd[0], '/'))
		data->exec_stat = execute(data, cmd[0], cmd);
	else if ((path = find_path(data, cmd[0], recoverpath)))
	{
		data->exec_stat = execute(data, path, cmd);
		free(path);
	}
	else
		ft_dprintf(2, "%s: command not found: %s\n", data->namesh, cmd[0]);
}
