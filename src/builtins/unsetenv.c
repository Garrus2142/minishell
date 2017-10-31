/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsetenv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thugo <thugo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/01 00:02:59 by thugo             #+#    #+#             */
/*   Updated: 2017/11/01 00:06:20 by thugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_unsetenv(t_data *data, int argc, char **argv)
{
	if (argc < 2)
	{
		ft_dprintf(2, "usage: unsetenv [name]\n");
		return (1);
	}
	env_unset(data, argv[1]);
	return (0);
}
