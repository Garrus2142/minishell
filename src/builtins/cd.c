/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thugo <thugo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/25 02:43:07 by thugo             #+#    #+#             */
/*   Updated: 2017/10/25 16:59:40 by thugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "minishell.h"

int		builtin_cd(t_data *data, int argc, char **argv)
{
	char	access_stat;
	char	*path;

	(void)data;
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
	if (ft_strlen(path) && (access_stat = access_check(path)))
	{
		if (access_stat & ACCESS_EXIST)
			ft_dprintf(2, "cd: no such file or directory: %s\n", path);
		else if (access_stat & ACCESS_EXEC)
			ft_dprintf(2, "cd: permission denied: %s\n", path);
		return (1);
	}
	chdir(path);
	return (0);
}
