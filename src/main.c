/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thugo <thugo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/18 16:29:20 by thugo             #+#    #+#             */
/*   Updated: 2017/11/01 17:18:43 by thugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_data	data;

	(void)argv;
	(void)argc;
	ft_bzero(&data, sizeof(t_data));
	env_init(&data, env);
	cwd_init(&data);
	signal_init(&data);
	while (!data.exit)
		prompt(&data);
	cwd_destroy(&data);
	env_destroy(&data);
	return (0);
}
