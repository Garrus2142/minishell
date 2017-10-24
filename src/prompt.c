/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thugo <thugo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/23 19:48:01 by thugo             #+#    #+#             */
/*   Updated: 2017/10/25 01:28:50 by thugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <sys/param.h>
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

static void	print_prompt(t_data *data)
{
	char	cwd[MAXPATHLEN];
	char	*basename;
	char	*git;

	if (!(basename = ft_basename(getcwd(cwd, MAXPATHLEN))))
		exit(EXIT_FAILURE);
	if (!(git = promptgit_get(data, cwd)))
		exit(EXIT_FAILURE);
	ft_printf("%S  \e[1m%s\e[0m %s", L"\e[2m➜\e[0m", basename, git);
	free(basename);
	free(git);
}

void		prompt(t_data *data)
{
	char	*line;
	t_cmd	**cmds;

	line = NULL;
	print_prompt(data);
	if (ft_gnl(STDIN_FILENO, &line) < 1)
	{
		data->exit = 1;
		return ;
	}
	parse_line(&cmds, line);
	
	free_cmds(&cmds);
	free(line);
}

/*int i = 0;
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
	}*/
