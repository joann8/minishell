/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_cmd_by_cmd.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacher <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 13:31:53 by jacher            #+#    #+#             */
/*   Updated: 2021/04/17 13:13:05 by jacher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft.h"

char	*modify_str(char *str, t_list **var)
{
	char		*tmp;
	int			size;
	t_expansion	exp;

	exp.str = str;
	exp.tmp = NULL;
	exp.var_str = NULL;
	size = count_final_str(&exp, *var);
//	printf("size = %d\n", size);
	if (size == -1)//erreur malloc
		return (NULL);
	if (size == 0)
		return (ft_strdup(""));
	tmp = malloc(sizeof(char) * (size + 1));
	if (tmp == NULL)
		return (NULL);
	exp.tmp = tmp;
	tmp = assign_final_str(&exp, *var);
	return (tmp);
}

t_seq	*make_expansion_cmd_by_cmd(t_seq *tab_seq, t_list **var)
{
//	int		i;
	t_seq	*tmp_s;
	t_list	*tmp_w;
	char	*delete;

//	i = -1;
//	while (++i < seq_nb)
//	{
		tmp_s = tab_seq;
		while (tmp_s)
		{
			tmp_w = tmp_s->word;
			while (tmp_w)
			{
				delete = (char *)(tmp_w->content);
				printf("before modify : %s\n", delete);
				tmp_w->content = modify_str(delete, var);
				printf("after modify : %s\n", tmp_w->content);
				free(delete);
				if (tmp_w->content == NULL)
					return (NULL);
				tmp_w = tmp_w->next;
			}
			tmp_s = tmp_s->next_pipe;	
		}
//	}
	return (tab_seq);
}