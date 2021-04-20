/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sequence.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacher <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 17:27:19 by jacher            #+#    #+#             */
/*   Updated: 2021/04/20 13:41:58 by jacher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft.h"

int		assign_redir(t_seq *tmp, t_list *lst_tok, t_token *tok)
{
	t_redir *redir;
	t_list	*new;

	redir = malloc(sizeof(t_redir));
	if (redir == NULL)
		return (print_error(0, "malloc error\n", -1));
	redir->e_type = tok->e_type;
	lst_tok = lst_tok->next;
	redir->file_name = ft_strdup(((t_token*)(lst_tok->content))->tok_str);
	new = ft_lstnew((void *)(redir));
	if (new == NULL)
	{
		free(redir);
		return (print_error(0, "malloc error\n", -1));
	}
	ft_lstadd_back(&tmp->redir, new);
	return (0);
}

int		assign_pipe(t_seq **tmp, int *pipe_pos)
{
	*pipe_pos += 1;
	(*tmp)->next_pipe = malloc(sizeof(t_seq));
	if ((*tmp)->next_pipe == NULL)
		return (print_error(0, "malloc error\n", -1));
	(*tmp) = (*tmp)->next_pipe;
	(*tmp)->pipe_pos = *pipe_pos;
	(*tmp)->word = NULL;
	(*tmp)->redir = NULL;
	(*tmp)->next_pipe = NULL;
	return (0);
}

int		assign_sequence(t_seq **tmp, t_list **lst_tok, int *pipe_pos)
{
	t_token		*tok;
	char		*tmp_c;
	t_list		*new;

	tok = (t_token*)(*lst_tok)->content;
	if (tok->e_type == WORD)
	{
		tmp_c = ft_strdup(tok->tok_str);
		if (tmp_c == NULL)
			return (print_error(0, "malloc error\n", -1));
		new = ft_lstnew(tmp_c);
		if (new == NULL)
		{
			free(tmp_c);
			return (print_error(0, "malloc error\n", -1));
		}
		ft_lstadd_back(&(*tmp)->word, new);
	}
	else if (tok->e_type == IN || tok->e_type == OUT || tok->e_type == APPEND)
	{
		if (assign_redir(*tmp, *lst_tok, tok) == -1)
			return (-1); //erreur gérée dans assign_redir
	}
	else if (tok->e_type == PIPE)
	{
		if (assign_pipe(tmp, pipe_pos) == -1)
			return (-1);//erreur gérée dans assign pipe
	}
	else if (tok->e_type == SEPARATOR)
	{
		*lst_tok = (*lst_tok)->next;
		return (1);
	}
	*lst_tok = (*lst_tok)->next;
	return (0);
}

t_seq	*create_sequence(t_seq *tab_seq, t_list *token_list, int seq_nb)
{
	t_list		*lst_tok;
	t_seq		*tmp;
	int			cmd_nb;
	int			pipe_pos;
	int			res;

	if ((tab_seq = malloc(sizeof(t_seq) * (seq_nb + 1))) == NULL)
	{
		print_error(0, "malloc error\n", -1);
		return (NULL); //erreur malloc
	}
	cmd_nb = 0;
	lst_tok = token_list;
	while (cmd_nb < seq_nb)
	{
		init_setup(tab_seq, &tmp, &pipe_pos, cmd_nb);
		while (lst_tok)
		{
			res = assign_sequence(&tmp, &lst_tok, &pipe_pos);
			if (res == 1)
				break ; //separator
			if (res == -1) //erreur malloc gérée dans assign sequence
			{
				ft_free_tab_seq(tab_seq, cmd_nb);
				return (NULL); //erreur malloc
			}
		}
		set_up_pipe_number(tab_seq, cmd_nb, pipe_pos);
		cmd_nb++;
	}
	return (tab_seq);
}
