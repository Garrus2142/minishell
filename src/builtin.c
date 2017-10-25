/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thugo <thugo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/25 02:04:04 by thugo             #+#    #+#             */
/*   Updated: 2017/10/25 21:44:20 by thugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "minishell.h"
#include "builtin.h"

static t_builtin	g_builtins[] = {
	{"pwd", builtin_pwd},
	{"exit", builtin_exit},
	{"cd", builtin_cd},
	{"env", builtin_env},
	{NULL, NULL}
};

int		builtin_execute(t_data *data, char **cmd)
{
	int	i;

	i = 0;
	while (g_builtins[i].name)
	{
		if (strcmp(cmd[0], g_builtins[i].name) == 0)
		{
			data->exec_stat = g_builtins[i].fn(data,
				ft_tabptrlen((void **)cmd), cmd);
			return (1);
		}
		++i;
	}
	return (0);
}
