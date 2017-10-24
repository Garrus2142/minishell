/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thugo <thugo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/23 21:22:12 by thugo             #+#    #+#             */
/*   Updated: 2017/10/24 18:15:50 by thugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "minishell.h"

static void	parse_cmd(t_cmd *cmd, char *fullcmd)
{
	char	**cmdsplit;
	size_t	len;
	size_t	i;

	if (!(cmdsplit = ft_strsplit(fullcmd, ' ')))
		exit(EXIT_FAILURE);
	if ((len = ft_tabptrlen((void **)cmdsplit)))
	{
		if (!(cmd->name = ft_strdup(cmdsplit[0])))
			exit(EXIT_FAILURE);
		if (!(cmd->args = (char **)malloc(sizeof(char *) * len)))
			exit(EXIT_FAILURE);
		i = 0;
		while (i < len - 1)
		{
			if (!(cmd->args[i] = ft_strdup(cmdsplit[i + 1])))
				exit(EXIT_FAILURE);
			++i;
		}
		cmd->args[i] = NULL;
	}
	ft_tabptrfree((void ***)&cmdsplit);
}

void		parse_line(t_cmd ***cmds, char *line)
{
	char	**fullcmds;
	int		i;

	if (!(fullcmds = ft_strsplit(line, ';')))
		exit(EXIT_FAILURE);
	if (!(*cmds = (t_cmd **)malloc(sizeof(t_cmd *) *
		(ft_tabptrlen((void **)fullcmds) + 1))))
		exit(EXIT_FAILURE);
	i = -1;
	while (fullcmds[++i])
	{
		if (!((*cmds)[i] = (t_cmd *)malloc(sizeof(t_cmd))))
			exit(EXIT_FAILURE);
		parse_cmd((*cmds)[i], fullcmds[i]);
	}
	(*cmds)[i] = NULL;
	ft_tabptrfree((void ***)&fullcmds);
}
