/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calao <adconsta@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 09:56:23 by calao             #+#    #+#             */
/*   Updated: 2021/04/17 18:38:52 by calao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft.h"

void	ft_print_str_table(char **av)
{
	while (*av)
	{
		ft_putstr(*av);
		ft_putchar('\n');
		av++;
	}
}
void	ft_print_str_lst(t_list *head)
{
	t_list *tmp;

	tmp = head;
	while (tmp)
	{
		printf("[%s] --> ", (char *)tmp->content);
		tmp = tmp->next;
	}
	printf("\n");
}

void	ft_print_envtlst_fd(t_list *env_head, int fd)
{
	t_var	*var;
	t_list	*tmp;

	tmp = env_head;
	while (tmp)
	{
		var = (t_var*)(tmp->content);
		if (var->on == 1)
		{
			write(fd, var->name, ft_strlen(var->name));
			write(fd, "=", 1);
			write(fd, var->value, ft_strlen(var->value));
			write(fd, "\n", 1);
		}
		tmp = tmp->next;
	}
}

void	ft_print_exportlst_fd(t_list *env_head, int fd)
{
	t_var	*var;
	t_list	*tmp;

	tmp = env_head;
	while (tmp)
	{
		var = (t_var*)(tmp->content);
		write(1, "declare -x ", 11); 
		write(fd, var->name, ft_strlen(var->name));
		write(fd, "=\"", 2);
		write(fd, var->value, ft_strlen(var->value));
		write(fd, "\"\n", 2);
		tmp = tmp->next;
	}
}

