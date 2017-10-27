/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thugo <thugo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/25 02:08:55 by thugo             #+#    #+#             */
/*   Updated: 2017/10/27 02:34:56 by thugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <sys/param.h>
#include "minishell.h"

int	builtin_pwd(t_data *data, int argc, char **argv)
{
	char	cwd[MAXPATHLEN];
	char	*options;

	if (ft_getopt(argc, argv, "LP", &options) == -1)
	{
		ft_dprintf(2, "pwd: bad option: -%c\n", *options);
		return (EXIT_FAILURE);
	}
	if (!ft_strchr(options, 'P') && env_get(data, "PWD"))
		ft_putendl(env_get(data, "PWD"));
	else
	{
		if (!getcwd(cwd, MAXPATHLEN))
			return (EXIT_FAILURE);
		ft_putendl(cwd);
	}
	free(options);
	return (EXIT_SUCCESS);
}
