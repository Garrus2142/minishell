/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thugo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/09 14:59:46 by thugo             #+#    #+#             */
/*   Updated: 2017/10/26 20:36:10 by thugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define ENV(elem) ((t_env *)elem->content)

# define STATS_EXIST	1
# define STATS_EXEC		2
# define STATS_DIR		4

# include "types.h"

void			env_init(t_data *data, char **environ);
void			env_unset(t_data *data, const char *name);
void			env_set(t_data *data, const char *name, const char *value);
char			*env_get(t_data *data, const char *name);
void			env_make_array(t_data *data);
void			env_destroy(t_data *data);
int				builtins(t_data *data, const char *cmd, int argc, char **argv);
void			loop(t_data *data);
void			ms_cerror(char *errmsg);
void			prompt(t_data *data);
char			*promptgit_get(const char *cwd);
void			parse_line(char ****cmds, char *line);
void			exec_execute(t_data *data, char **cmd);
int				builtin_execute(t_data *data, char **cmd);
char			stats_check(const char *path);
void			signal_init(void);

#endif
