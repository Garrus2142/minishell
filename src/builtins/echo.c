/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thugo <thugo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/01 19:05:57 by thugo             #+#    #+#             */
/*   Updated: 2017/11/02 02:48:30 by thugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_echo(t_data *data, int argc, char **argv)
{
	int	i;
	int	nonl;

	(void)data;
	i = 1;
	nonl = 0;
	while (i < argc)
	{
		if (i == 1 && !ft_strcmp(argv[i], "-n"))
			nonl = 1;
		else
		{
			ft_putstr(argv[i]);
			if (i + 1 < argc)
				ft_putchar(' ');
		}
		++i;
	}
	ft_putchar(' ');
	if (!nonl)
		ft_putchar('\n');
	return (0);
}
