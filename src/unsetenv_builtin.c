/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsetenv_builtin.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijanie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 17:20:44 by ijanie            #+#    #+#             */
/*   Updated: 2020/05/09 17:21:53 by ijanie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		ft_tablen(char **tab)
{
	int		len;

	len = 0;
	while (*(tab + len))
		len++;
	return (len);
}

static void		ft_free_array(char **arr)
{
	int i;
	int c;

	c = ft_tablen(arr);
	if (!arr)
		return ;
	i = 0;
	while (i < c)
	{
		free(arr[i]);
		arr[i] = NULL;
		i++;
	}
	free(arr);
	arr = NULL;
}

int				envv_len(char **envv)
{
	int		i;
	int		count;

	i = -1;
	count = 0;
	while (envv[++i])
		count++;
	return (count);
}

static int		pop_index(int index, t_sh *env)
{
	int		i;
	int		k;
	int		len;
	char	**tmp;

	i = -1;
	k = 0;
	len = 0;
	while (env->genvv[len])
		len++;
	if (!(tmp = (char**)ft_memalloc(sizeof(char*) * len)))
	{
		ft_putstr("malloc fail");
		ft_putchar_fd('\n', 2);
		return (0);
	}
	while (env->genvv[++i] && i < len)
		if (i != index)
			tmp[k++] = ft_strdup(env->genvv[i]);
	ft_free_array(env->genvv);
	tmp[k] = NULL;
	env->genvv = tmp;
	return (1);
}

int				unsetenv_builtin(char **args, t_sh *env)
{
	int	i;
	int	len;

	if (args[1])
	{
		i = -1;
		len = ft_strlen(args[1]);
		while (env->genvv[++i])
			if (ft_strnequ(env->genvv[i], args[1], len) \
			&& env->genvv[i][len] == '=')
			{
				pop_index(i, env);
				break ;
			}
	}
	else
	{
		ft_putendl("minishell: unsetenv: invalid arguments");
		return (0);
	}
	return (1);
}
