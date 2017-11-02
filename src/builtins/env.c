/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thugo <thugo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/25 21:23:34 by thugo             #+#    #+#             */
/*   Updated: 2017/11/02 02:14:01 by thugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "minishell.h"

static void	exec_util(t_data *data, t_data *envdata, int argc, char **argv)
{
	int	i;

	i = 0;
	if (!argc)
	{
		while (envdata->envtab[i])
			ft_putendl(envdata->envtab[i++]);
		return ;
	}
	ft_strcpy(envdata->namesh, "env");
	exec_execute(envdata, argv, env_get(data, "PATH"));
}

static int	setup_env(t_data *data, t_data *envdata, int argc, char **argv)
{
	int		i;
	char	*chr;
	char	*name;

	env_init(envdata, data ? data->envtab : NULL);
	i = 0;
	while (i < argc)
	{
		if (!(chr = ft_strchr(argv[i], '=')))
			break ;
		if (chr == argv[i])
		{
			ft_dprintf(2, "env: setenv %s: Invalid argument.\n", argv[i]);
			envdata->exec_stat = 1;
			return (-1);
		}
		if (!(name = ft_strndup(argv[i], chr - argv[i])))
			exit(EXIT_FAILURE);
		env_set(envdata, name, chr + 1);
		free(name);
		++i;
	}
	return (i);
}

int			builtin_env(t_data *data, int argc, char **argv)
{
	t_data	envdata;
	char	*options;
	int		index;
	int		ret;

	ret = 0;
	ft_bzero(&envdata, sizeof(t_data));
	if ((index = ft_getopt(argc, argv, "i", &options)) == -1)
	{
		ft_dprintf(2, "env: illegal option -- %c\n", *options);
		ft_putstr_fd(
			"usage: env [-i] [name=value ...] [utility [argument ...]]\n", 2);
		return (1);
	}
	ret = setup_env(ft_strchr(options, 'i') ? NULL : data, &envdata,
		argc - index, argv + index);
	if (ret != -1)
		exec_util(data, &envdata, argc - (index + ret), argv + index + ret);
	ret = envdata.exec_stat;
	free(options);
	env_destroy(&envdata);
	return (ret);
}
