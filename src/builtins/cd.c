/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thugo <thugo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/25 02:43:07 by thugo             #+#    #+#             */
/*   Updated: 2017/10/27 04:15:55 by thugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
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

/*static char	logical_path(char *path)
{
	
}*/

int			builtin_cd(t_data *data, int argc, char **argv)
{
	char	*path;
	char	*options;
	int		index;

	if ((index = ft_getopt(argc, argv, "LP", &options)) == -1)
	{
		ft_dprintf(2, "cd: bad option: -%c\n", *options);
		return (EXIT_FAILURE);
	}
	if (index >= argc)
	{
		if (!(path = env_get(data, "HOME")))
		{
			ft_dprintf(2, "cd: HOME not set\n");
			return (1);
		}
	}
	else
		path = argv[index];
	if (!can_change(path))
		return (1);
	if (ft_strchr(options, 'P'))
		chdir(path);
	return (0);
}
