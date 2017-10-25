/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thugo <thugo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/25 01:55:07 by thugo             #+#    #+#             */
/*   Updated: 2017/10/25 21:17:39 by thugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "libft.h"
#include "minishell.h"

static int	execute(t_data *data, char **cmd)
{
	char	stats;
	pid_t	pid;
	int		stat_loc;

	stats = stats_check(cmd[0]);
	if (!(stats & STATS_EXIST) || !(stats & STATS_EXEC) || (stats & STATS_DIR))
	{
		if (!(stats & STATS_EXIST))
			ft_dprintf(2, "minishell: no such file or directory: %s\n", cmd[0]);
		else if ((stats & STATS_DIR))
			ft_dprintf(2, "minishell: is a directory: %s\n", cmd[0]);
		else if (!(stats & STATS_EXEC))
			ft_dprintf(2, "minishell: permission denied: %s\n", cmd[0]);
		return (127);
	}
	if (!(pid = fork()))
		execve(cmd[0], cmd, data->envtab);
	waitpid(pid, &stat_loc, 0);
	if (WIFEXITED(stat_loc))
		return (WEXITSTATUS(stat_loc));
	else if (WIFSIGNALED(stat_loc))
		return (128 + WTERMSIG(stat_loc));
	return (0);
}

void		exec_execute(t_data *data, char **cmd)
{
	if (builtin_execute(data, cmd))
		return ;
	else if (ft_strchr(cmd[0], '/'))
		data->exec_stat = execute(data, cmd);
}
