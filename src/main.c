/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thugo <thugo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/18 16:29:20 by thugo             #+#    #+#             */
/*   Updated: 2017/11/01 18:47:02 by thugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell.h"

static void	shlvl(t_data *data)
{
	int		shlvl;
	char	*shlvlstr;

	if (!env_get(data, "SHLVL"))
		env_set(data, "SHLVL", "1");
	else
	{
		shlvl = ft_atoi(env_get(data, "SHLVL"));
		if (shlvl <= 0)
			env_set(data, "SHLVL", "1");
		else
		{
			if (!(shlvlstr = ft_itoa(++shlvl)))
				exit(EXIT_FAILURE);
			env_set(data, "SHLVL", shlvlstr);
			free(shlvlstr);
		}
	}
}

int	main(int argc, char **argv, char **env)
{
	t_data	data;

	(void)argv;
	(void)argc;
	ft_bzero(&data, sizeof(t_data));
	env_init(&data, env);
	cwd_init(&data);
	signal_init(&data);
	shlvl(&data);
	while (!data.exit)
		prompt(&data);
	cwd_destroy(&data);
	env_destroy(&data);
	return (0);
}
