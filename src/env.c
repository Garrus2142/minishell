/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thugo <thugo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/18 16:29:10 by thugo             #+#    #+#             */
/*   Updated: 2017/10/24 01:47:04 by thugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell.h"

char		**env_getarray(t_data *data)
{
	t_list	*cur;
	size_t	i;
	size_t	len;
	char	**envtab;

	if (!(envtab = (char **)malloc(sizeof(char *) *
			(ft_lstlen(data->env) + 1))))
		exit(EXIT_FAILURE);
	i = 0;
	cur = data->env;
	while (cur)
	{
		len = ft_strlen(ENV(cur)->name);
		if (!(envtab[i] = (char *)malloc(sizeof(char) *
				(len + ft_strlen(ENV(cur)->value) + 2))))
			exit(EXIT_FAILURE);
		ft_strcpy(envtab[i], ENV(cur)->name);
		envtab[i][len] = '=';
		ft_strcpy(envtab[i] + len + 1, ENV(cur)->value);
		cur = cur->next;
		++i;
	}
	envtab[i] = NULL;
	return (envtab);
}

char		*env_getset(t_data *data, const char *name, const char *value)
{
	t_list	*elem;
	t_env	envdata;

	elem = data->env;
	while (elem)
	{
		if (ft_strcmp(name, ((t_env *)elem->content)->name) == 0)
		{
			if (value)
			{
				free(((t_env *)elem->content)->value);
				((t_env *)elem->content)->value = ft_strdup(value);
			}
			return (((t_env *)elem->content)->value);
		}
		elem = elem->next;
	}
	if (!value)
		return (NULL);
	envdata.name = ft_strdup(name);
	envdata.value = ft_strdup(value);
	if (!(elem = ft_lstnew(&envdata, sizeof(envdata))))
		exit(EXIT_FAILURE);
	ft_lstadd(&(data->env), elem);
	return (envdata.value);
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
}

void	env_destroy(t_data *data)
{
	//Free chained list
}
