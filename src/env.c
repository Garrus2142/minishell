/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thugo <thugo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/18 16:29:10 by thugo             #+#    #+#             */
/*   Updated: 2017/11/02 00:37:22 by thugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell.h"

void		env_make_array(t_data *data)
{
	t_list	*cur;
	size_t	i;
	size_t	len;

	if (data->envtab)
		ft_tabptrfree((void ***)&(data->envtab));
	if (!(data->envtab = (char **)malloc(sizeof(char *) *
		(ft_lstlen(data->env) + 1))))
		exit(EXIT_FAILURE);
	i = 0;
	cur = data->env;
	while (cur)
	{
		len = ft_strlen(ENV(cur)->name);
		if (!(data->envtab[i] = (char *)malloc(sizeof(char) *
			(len + ft_strlen(ENV(cur)->value) + 2))))
			exit(EXIT_FAILURE);
		ft_strcpy(data->envtab[i], ENV(cur)->name);
		data->envtab[i][len] = '=';
		ft_strcpy(data->envtab[i] + len + 1, ENV(cur)->value);
		cur = cur->next;
		++i;
	}
	data->envtab[i] = NULL;
}

void		env_init(t_data *data, char **environ)
{
	int		i;
	t_list	*new;
	t_env	envdata;

	i = -1;
	if (environ)
	{
		while (environ[++i])
		{
			if (!(envdata.name = ft_strndup(environ[i],
					ft_strchr(environ[i], '=') - environ[i])))
				exit(EXIT_FAILURE);
			if (!(envdata.value = ft_strdup(ft_strchr(environ[i], '=') + 1)))
				exit(EXIT_FAILURE);
			if (!(new = ft_lstnew(&envdata, sizeof(envdata))))
				exit(EXIT_FAILURE);
			ft_lstadd(&(data->env), new);
		}
	}
	env_make_array(data);
}

void		env_destroy(t_data *data)
{
	t_list	*cur;
	t_list	*next;

	cur = data->env;
	while (cur)
	{
		free(ENV(cur)->name);
		free(ENV(cur)->value);
		free(cur->content);
		next = cur->next;
		free(cur);
		cur = next;
	}
	ft_tabptrfree((void ***)&(data->envtab));
}
