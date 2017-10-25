/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thugo <thugo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/25 21:23:34 by thugo             #+#    #+#             */
/*   Updated: 2017/10/25 21:42:56 by thugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

int		builtin_env(t_data *data, int argc, char **argv)
{
	int	i;

	i = 0;
	while (data->envtab[i])
		ft_putendl(data->envtab[i++]);
	return (0);
}
