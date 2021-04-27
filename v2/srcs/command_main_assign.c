/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_main_assign.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacher <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 09:42:47 by jacher            #+#    #+#             */
/*   Updated: 2021/04/27 19:02:13 by jacher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft.h"

int			assign_list_redir_2(t_redir *r, t_simple_cmd *cmd)
{
	if (r->e_type == OUT)
	{
		if (cmd->fd_out > 1)
			close(cmd->fd_out);//essayer READ ? QUID si c'est un dossier ?
		cmd->fd_out = open(r->file_name, O_WRONLY | O_CREAT | O_TRUNC, 0664);//664 a checker
		if (cmd->fd_out < 0)
			return (print_err(strerror(errno), NULL, NULL, 0));
	}
	else if (r->e_type == APPEND)
	{
		if (cmd->fd_out > 1)
			close(cmd->fd_out);//essayer de READ ? QUID si c'est un dossier ?
		cmd->fd_out = open(r->file_name, O_WRONLY | O_CREAT | O_APPEND, 0664);
		if (cmd->fd_out < 0)
			return (print_err(strerror(errno), NULL, NULL, 0));
	}
	return (0);
}

int			check_redir_expansion(t_simple_cmd *cmd, t_redir *r, t_list **env)
{
	char 	*new;

	//printf("r->file_name = %s\n", r->file_name);
	new = modify_str(r->file_name, env);
	//printf("r->file_name = %s\n", new);
	if (ft_strcmp(new, "") == 0)
	{
		cmd->on = 0;
		print_err("msh: ", r->file_name, " : redirection ambiguë\n", 0);
		free(new);
		return (-1);
	}
	else if ((r->file_name = ft_strdup(new)) == NULL)
	{	
		free(r->file_name);
		free(new);
		return (p_error(0, "malloc error\n", -1));
	}
	return (0);
}

int			assign_list_redir(t_list *tmp_l, t_simple_cmd *cmd, t_list **env)
{
	t_redir	*r;

	while (tmp_l)
	{
		r = (t_redir *)tmp_l->content;
		if (check_redir_expansion(cmd, r, env) == -1)
			return (0);
		if (r->e_type == IN)
		{
			if (cmd->fd_in > 0)
				close(cmd->fd_in);//essayer de READ ? QUID si c'est un dossier?
			cmd->fd_in = open(r->file_name, O_RDONLY);
			if (cmd->fd_in < 0)
			{
				cmd->on = 0;
				print_err("msh : ", r->file_name, ": ", 0);
				print_err(strerror(errno), "\n", NULL, 0);
				g.exit_status = 1;
				return (0);
			}
		}
		else if (assign_list_redir_2(r, cmd) == -1)
			return (p_error(0, "malloc error\n", -1));//(adrien) c'est 
		//quoi p_error?
		tmp_l = tmp_l->next;
	}
	return (0);
}
/*
int			expand_list_redir(t_list *begin, t_list **env)
{
	t_redir	*r;
	t_list	*tmp_l;
	char 	*new;

	tmp_l = begin;
	while (tmp_l)
	{
		r = (t_redir *)tmp_l->content;
		//printf("r->file_name = %s\n", r->file_name);
		new = modify_str(r->file_name, env);
		//printf("r->file_name = %s\n", new);
		if (ft_strcmp(new, "") == 0)
		{
			print_err("msh: ", r->file_name, " : redirection ambiguë\n", 0);
			free(new);
			printf("%s\n", r->file_name);
		}
		else if ((r->file_name = ft_strdup(new)) == NULL)
		{	
			free(r->file_name);
			free(new);
			return (p_error(0, "malloc error\n", -1));
		}
		tmp_l = tmp_l->next;
	}
	return (0);
}
*/
int			assign_list_word(t_seq *seq, t_simple_cmd *cmd)
{
	int		i;
	t_list	*tmp;

	tmp = seq->word;
	i = 0;
	while (tmp)
	{
		if (i == 0)
		{
			cmd->job = ft_strdup((char *)tmp->content);
			if (cmd->job == NULL)
				return (p_error(0, "malloc error\n", -1));
		}
		cmd->av[i] = ft_strdup(tmp->content);//recheker ce qu'il faut free ou pas
		if (cmd->av[i] == NULL)//erreur malloc // pas  besoin de free(cmd->job) je crois car free en sortant
			return (p_error(0, "malloc error\n", -1));
		tmp = tmp->next;
		i++;
	}
	cmd->av[i] = NULL;
	return (0);
}

void		assign_pipes(t_seq *seq, t_simple_cmd *cmd)
{
	cmd->fd_in = STDIN_FILENO;
	cmd->fd_out = STDOUT_FILENO;
	if (seq->pipe_total > 0)
		cmd->pipe_mod = 1;
	else
		cmd->pipe_mod = 0;
	if (seq->pipe_pos == seq->pipe_total)
		cmd->pipe_pos = 1;
	else if (seq->pipe_pos == 0)
		cmd->pipe_pos = -1;
	else
		cmd->pipe_pos = 0;
}
