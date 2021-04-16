/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacher <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 15:28:48 by jacher            #+#    #+#             */
/*   Updated: 2021/04/16 15:48:13 by jacher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft.h"

int		find_built_in(t_simple_cmd *cmd, t_pipe *p, t_list **error, t_list **env)
{
	(void)error;
	(void)env;
	if (ft_strcmp(cmd->job, "echo") == 0)
	{
		printf("ECHO FOUND!\n");
		ft_echo(cmd, p);
		return (1);
	}
/*	if (ft_strcmp(cmd->job, "cd") == 0)//ADRIEN
		return (2);
	if (ft_strcmp(cmd->job, "pwd") == 0)//JOANN
		return (3);
	if (ft_strcmp(cmd->job, "export") == 0)//ADRIEN
		return (4);
	if (ft_strcmp(cmd->job, "unset") == 0)//ADRIEN
		return (5);
	if (ft_strcmp(cmd->job, "env") == 0)//ADRIEN
		return (6);
	if (ft_strcmp(cmd->job, "exit") == 0)//JOANN
		return (7);*/
	return (0);
}
