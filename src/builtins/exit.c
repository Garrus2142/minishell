/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thugo <thugo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/25 02:35:33 by thugo             #+#    #+#             */
/*   Updated: 2017/11/01 22:13:40 by thugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "minishell.h"

int		builtin_exit(t_data *data, int argc, char **argv)
{
	int	i;

	if (argc == 1)
	{
		data->exit = 1;
		return (0);
	}
	else if (argc > 2)
	{
		ft_putstr_fd("exit: Too many arguments.\n", 2);
		return (1);
	}
	else
	{
		data->exit = 1;
		return (ft_atoi(argv[1]));
	}
	return (0);
}
