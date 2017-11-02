/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thugo <thugo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/23 21:22:12 by thugo             #+#    #+#             */
/*   Updated: 2017/11/02 02:46:09 by thugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "minishell.h"

static void	parse_cmd(char ***cmd, char *fullcmd)
{
	char	**cmdsplit;
	size_t	len;
	size_t	i;

	if (!(cmdsplit = ft_strsplits(fullcmd, " \t")))
		exit(EXIT_FAILURE);
	len = ft_tabptrlen((void **)cmdsplit);
	if (!(*cmd = (char **)malloc(sizeof(char *) * (len + 1))))
		exit(EXIT_FAILURE);
	i = 0;
	while (i < len)
	{
		if (!((*cmd)[i] = ft_strdup(cmdsplit[i])))
			exit(EXIT_FAILURE);
		++i;
	}
	(*cmd)[i] = NULL;
	ft_tabptrfree((void ***)&cmdsplit);
}

void		parse_line(char ****cmds, char *line)
{
	char	**fullcmds;
	int		i;

	if (!(fullcmds = ft_strsplit(line, ';')))
		exit(EXIT_FAILURE);
	if (!(*cmds = (char ***)malloc(sizeof(char **) *
		(ft_tabptrlen((void **)fullcmds) + 1))))
		exit(EXIT_FAILURE);
	i = -1;
	while (fullcmds[++i])
		parse_cmd(&((*cmds)[i]), fullcmds[i]);
	(*cmds)[i] = NULL;
	ft_tabptrfree((void ***)&fullcmds);
}
