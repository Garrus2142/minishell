/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thugo <thugo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/25 02:43:07 by thugo             #+#    #+#             */
/*   Updated: 2017/10/25 20:03:50 by thugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "minishell.h"

static int	change_dir(char *path)
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
		return (1);
	}
	chdir(path);
	return (0);
}

int			builtin_cd(t_data *data, int argc, char **argv)
{
	char	*path;

	if (argc == 1)
	{
		if (!(path = env_get(data, "HOME")))
		{
			ft_dprintf(2, "cd: HOME not set\n");
			return (1);
		}
	}
	else
		path = argv[1];
	return (change_dir(path));
}
