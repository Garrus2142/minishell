/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thugo <thugo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/31 22:59:08 by thugo             #+#    #+#             */
/*   Updated: 2017/11/01 00:10:41 by thugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

static int	check_errors(char *name)
{
	int	i;

	if (!ft_isalpha(name[0]))
	{
		ft_dprintf(2, "setenv: Variable name must begin with a letter.\n");
		return (1);
	}
	i = 0;
	while (name[i])
	{
		if (!ft_isalnum(name[i++]))
		{
			ft_dprintf(2,
			"setenv: Variable name must contain alphanumeric characters.\n");
			return (1);
		}
	}
	return (0);
}

int			builtin_setenv(t_data *data, int argc, char **argv)
{
	int	err;

	err = 0;
	if (argc < 2)
	{
		ft_dprintf(2, "usage: setenv [name] [value]\n");
		return (1);
	}
	if (check_errors(argv[1]))
		return (1);
	env_set(data, argv[1], argc > 2 ? argv[2] : "");
	return (0);
}
