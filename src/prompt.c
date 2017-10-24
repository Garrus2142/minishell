/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thugo <thugo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/23 19:48:01 by thugo             #+#    #+#             */
/*   Updated: 2017/10/24 02:07:26 by thugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "libft.h"
#include "minishell.h"

static void	free_cmds(t_cmd ***cmds)
{
	int	i;

	i = 0;
	while ((*cmds)[i])
	{
		free((*cmds)[i]->name);
		ft_tabptrfree((void ***)&((*cmds)[i]->args));
		free((*cmds)[i]);
		++i;
	}
	free(*cmds);
}

void	prompt(t_data *data)
{
	char	*line;
	t_cmd	**cmds;

	line = NULL;
	ft_printf("$>");
	if (ft_gnl(STDIN_FILENO, &line) < 1)
	{
		data->exit = 1;
		return ;
	}
	parse_line(data, &cmds, line);
	int i = 0;
	int u = 0;
	while (cmds[i])
	{
		ft_printf("Name: %s Args: ", cmds[i]->name);
		u = 0;
		while (cmds[i]->args[u])
		{
			ft_printf("%s ", cmds[i]->args[u]);
			++u;
		}
		ft_printf("\n");
		++i;
	}
	free_cmds(&cmds);
	free(line);
}
