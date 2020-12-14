/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijanie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 17:20:44 by ijanie            #+#    #+#             */
/*   Updated: 2020/05/09 17:21:53 by ijanie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		print_env(char **genvv)
{
	int		i;

	i = -1;
	while (genvv[++i])
		ft_putendl(genvv[i]);
}

t_sh		*init_envv(int ac, char **av, char **envv)
{
	int		i;
	t_sh	*env;

	(void)ac;
	(void)av;
	env = (t_sh*)malloc(sizeof(t_sh));
	env->genvv = (char **)ft_memalloc(sizeof(char *) * (envv_len(envv) + 1));
	i = -1;
	while (envv[++i])
	{
		if (!(env->genvv[i] = ft_strdup(envv[i])))
			exit_shell(env);
	}
	return (env);
}
