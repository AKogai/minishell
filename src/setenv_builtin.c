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

int		find_env_var(char *var, t_sh *env)
{
	int		i;
	char	*tmp;

	i = -1;
	while (env->genvv[++i])
	{
		tmp = ft_strjoinch(var, '=');
		if (ft_strstartswith(env->genvv[i], tmp))
		{
			free(tmp);
			return (i);
		}
		free(tmp);
	}
	return (i);
}

char	*get_env_var(char *var, t_sh *env)
{
	int		i;
	char	*tmp;

	i = -1;
	while (env->genvv[++i])
	{
		tmp = ft_strjoinch(var, '=');
		if (ft_strstartswith(env->genvv[i], tmp))
		{
			free(tmp);
			return (ft_strchr(env->genvv[i], '=') + 1);
		}
		free(tmp);
	}
	return (NULL);
}

char	**realloc_envv(int new_size, t_sh *env)
{
	char	**new;
	int		i;

	new = (char **)ft_memalloc(sizeof(char *) * (new_size + 1));
	i = -1;
	while (env->genvv[++i] && i < new_size)
	{
		new[i] = ft_strdup(env->genvv[i]);
		free(env->genvv[i]);
	}
	free(env->genvv);
	new[i] = NULL;
	return (new);
}

void	set_env_var(char *key, char *value, t_sh *env)
{
	int		pos;
	char	*tmp;

	pos = find_env_var(key, env);
	tmp = ft_strjoin("=", value);
	if (env->genvv[pos])
	{
		free(env->genvv[pos]);
		if (value)
			env->genvv[pos] = ft_strjoin(key, tmp);
		else
			env->genvv[pos] = ft_strjoin(key, "=");
	}
	else
	{
		env->genvv = realloc_envv(pos + 1, env);
		if (value)
			env->genvv[pos] = ft_strjoin(key, tmp);
		else
			env->genvv[pos] = ft_strjoin(key, "=");
	}
	free(tmp);
}

int		setenv_builtin(char **args, t_sh *env)
{
	if (!args[0])
	{
		print_env(env->genvv);
		return (1);
	}
	if (args[1])
	{
		if (args[2])
		{
			ft_putendl("setenv: Too many arguments.");
			return (1);
		}
	}
	set_env_var(args[0], args[1], env);
	return (1);
}
