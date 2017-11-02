/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thugo <thugo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/23 19:48:01 by thugo             #+#    #+#             */
/*   Updated: 2017/11/02 02:04:43 by thugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <sys/param.h>
#include <signal.h>
#include "libft.h"
#include "minishell.h"

static void	free_cmds(char ****cmds)
{
	int	i;

	i = 0;
	while ((*cmds)[i])
	{
		ft_tabptrfree((void ***)&((*cmds)[i]));
		free((*cmds)[i]);
		++i;
	}
	free(*cmds);
}

void		prompt_print(t_data *data)
{
	char	cwd[MAXPATHLEN];
	char	*basename;
	char	*git;

	if (!data->cwd)
	{
		ft_printf("\e[%sm%S\e[0m  ", data->exec_stat ? "91" : "92", L"➜");
		return ;
	}
	if (!(basename = ft_basename(data->cwd)))
		exit(EXIT_FAILURE);
	if (!(git = promptgit_get(getcwd(cwd, MAXPATHLEN))))
		exit(EXIT_FAILURE);
	ft_printf("\e[%sm%S\e[0m  \e[1m%s\e[0m %s", data->exec_stat ?
		"91" : "92", L"➜", basename, git);
	free(basename);
	free(git);
}

void		prompt(t_data *data)
{
	char	*line;
	char	***cmds;
	int		i;

	line = NULL;
	prompt_print(data);
	if (ft_gnl(STDIN_FILENO, &line) < 1)
	{
		data->exit = 1;
		ft_putchar('\n');
		return ;
	}
	parse_line(&cmds, line);
	i = 0;
	while (cmds[i])
	{
		if (cmds[i][0])
			exec_execute(data, cmds[i], NULL);
		if (data->exec_stat == 128 + SIGINT)
			break ;
		++i;
	}
	free_cmds(&cmds);
	free(line);
}
