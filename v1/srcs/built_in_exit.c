/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacher <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 16:26:23 by jacher            #+#    #+#             */
/*   Updated: 2021/04/20 18:55:26 by jacher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft.h"

int		ft_exit_help(t_simple_cmd *cmd, t_list **error, int i)
{
	while (cmd->av[1][i])
	{
		if (i == 0)
		{
			if (cmd->av[1][0] == '-' || cmd->av[1][0] == '+')
				i++;
		}
		if (ft_isdigit(cmd->av[1][i]) == 1)
			i++;
		else
		{
			if (add_err_lst(error, "msh: exit: ", cmd->av[1],
				" : argument numérique nécessaire\n") == -1)
				return (-1);
			return (2);//error code
		}
	}
	if (cmd->ac > 2)
	{
		if (add_err_lst(error, "msh : exit: trop d'arguments.\n",
			NULL, NULL) == -1)
			return (-1);
		return (1);
	}
	return (0);
}

int		ft_exit(t_simple_cmd *cmd, t_pipe *p, t_list **error)
{
	int				res;
	unsigned char	c;

	ft_putstr_fd("exit\n", p->fd_out_to_use);
	if (cmd->ac > 1)
	{
		res = ft_exit_help(cmd, error, 0);
		if (res != 0)
			return (res);
		c = ft_atoi(cmd->av[1]);
		return (c);
	}
	return (0);
}