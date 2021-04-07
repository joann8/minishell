/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_joann.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacher <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 16:05:44 by jacher            #+#    #+#             */
/*   Updated: 2021/04/07 20:00:21 by jacher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft.h"

void	print_list(t_list *token)
{
	t_list	*tmp;
	t_token	*tmp2;
	int		tour;
	
	tour= 0;
	tmp = token;
	while (tmp)
	 {
		tmp2 = (t_token *)tmp->content;
		printf("%d.token->e_type = %d\n  token->tok_str=%s\n", tour, tmp2->e_type, tmp2->tok_str);
		tmp = tmp->next;
		tour++;
	}
}

int main(int ac, char **av)
{
	t_list	*token_list;
	t_seq	*tab_seq;

	tab_seq = NULL;

	(void)ac;
	token_list = NULL;
	token_list = ft_get_token_list(token_list,av[1]);
	if (token_list == NULL)
	{
		printf("pbm tokenize\n");
		return (0);
	}
	//printf("\n*** FIRST AFTER FUNCTION ***\n");
	//print_list(token_list);
	assign_type_1(token_list);
	//printf("\n*** AFTER ASSIGN 1 ***\n");
	//print_list(token_list);
	if (assign_type_2(token_list) == -1)
		return(printf("wrong inputs\n"));
	printf("\n*** AFTER ASSIGN 2 ***\n");
	print_list(token_list);
	create_sequence(tab_seq, token_list);

	return (0);
}
