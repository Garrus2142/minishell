/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envaccess.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thugo <thugo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/24 17:25:41 by thugo             #+#    #+#             */
/*   Updated: 2017/10/24 17:35:48 by thugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell.h"

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
			if (!(((t_env *)elem->content)->value = ft_strdup(value)))
				exit(EXIT_FAILURE);
			return ;
		}
		elem = elem->next;
	}
	envdata.name = ft_strdup(name);
	envdata.value = ft_strdup(value);
	if (!envdata.name || !envdata.value ||
			!(elem = ft_lstnew(&envdata, sizeof(envdata))))
		exit(EXIT_FAILURE);
	ft_lstadd(&(data->env), elem);
	env_make_array(data);
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
	env_make_array(data);
}
