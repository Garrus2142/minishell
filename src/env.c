/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thugo <thugo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/18 16:29:10 by thugo             #+#    #+#             */
/*   Updated: 2017/10/18 16:29:12 by thugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell.h"

static void	make_array(t_data *data)
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

char		*env_get(t_data *data, const char *name)
{
	t_list	*cur;

	cur = data->env;
	while (cur)
	{
		if (ft_strcmp(name, ((t_env *)cur->content)->name) == 0)
			return (((t_env *)cur->content)->value);
		cur = cur->next;
	}
	return (NULL);
}

void		env_set(t_data *data, const char *name, const char *value)
{
	t_list	*elem;
	t_env	envdata;

	elem = data->env;
	while (elem)
	{
		if (ft_strcmp(name, ((t_env *)elem->content)->name) == 0)
		{
			((t_env *)elem->content)->value = ft_strdup(value);
			return ;
		}
		elem = elem->next;
	}
	envdata.name = ft_strdup(name);
	envdata.value = ft_strdup(value);
	if (!(elem = ft_lstnew(&envdata, sizeof(envdata))))
		exit(EXIT_FAILURE);
	ft_lstadd(&(data->env), elem);
	make_array(data);
}

void		env_unset(t_data *data, const char *name)
{
	t_list *cur;
	t_list *prev;

	cur = data->env;
	prev = NULL;
	while (cur)
	{
		if (ft_strcmp(name, ((t_env *)cur->content)->name) == 0)
		{
			if (!prev)
				data->env = cur->next;
			else
				prev = cur->next;
			free(((t_env *)cur->content)->name);
			free(((t_env *)cur->content)->value);
			free(cur);
			break ;
		}
		prev = cur;
		cur = cur->next;
	}
	make_array(data);
}

void		env_init(t_data *data, char **environ)
{
	int		i;
	t_list	*new;
	t_env	envdata;

	i = -1;
	while (environ[++i])
	{
		if (!(envdata.name = ft_strndup(environ[i], ft_strchr(environ[i], '=')
				- environ[i])))
			exit(EXIT_FAILURE);
		if (!(envdata.value = ft_strdup(ft_strchr(environ[i], '=') + 1)))
			exit(EXIT_FAILURE);
		if (!(new = ft_lstnew(&envdata, sizeof(envdata))))
			exit(EXIT_FAILURE);
		ft_lstadd(&(data->env), new);
	}
	make_array(data);
}
