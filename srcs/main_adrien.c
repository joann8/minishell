/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_adrien.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calao <adconsta@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 14:37:01 by calao             #+#    #+#             */
/*   Updated: 2021/04/14 17:08:09 by calao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft.h"


char	*ft_relative_to_absolute(char *exec);
int		ft_path_is_relative(char *str);

t_list	*ft_lstfind_env(t_list *begin, char *content_ref, int (*cmp)())
{
	t_var *tmp;

	while (begin)
	{
		tmp = (t_var *)begin->content;

		if (!((*cmp)(tmp->name, content_ref)))
			return (begin);
		begin = begin->next;
	}
	return (NULL);
}


char	*ft_make_prompt(t_list *pwd_node)
{
	t_var *var;
	char *tmp;
	char *pwd;
	char *prompt;

	var = (t_var *)(pwd_node->content);
	pwd = var->value;

	prompt = ft_strjoin("minishell@jacher-adconsta:", pwd);
	if (prompt == NULL)
		return (NULL);
	tmp = prompt;
	prompt = ft_strjoin(prompt, "$ ");
	free(tmp);
	if (prompt == NULL)
		return (NULL);
	return (prompt);
}

int		ft_update_pwd(t_list *pwd_node, char *cwd)
{
//	t_var *var;

	free(((t_var *)(pwd_node->content))->value);
	if ((((t_var *)(pwd_node->content))->value = ft_strdup(cwd)) == NULL)
		return (-1);
	return (0);
}

int		main_adrien(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	//(void)envp;
	t_list	*env_lst;
	char *user_input;
	char *prompt;
	t_list	*pwd_node;

	env_lst = NULL;
	ft_make_envlst(&env_lst, envp);
	pwd_node = (ft_lstfind_env(env_lst, "PWD", ft_strcmp));
	while (1)
	{
		prompt = ft_make_prompt(pwd_node);
		printf("\n\nprompt = %s\n", prompt);
		if (prompt == NULL)
			return (-1);
		ft_get_userinput(&user_input, prompt);
		printf("user input = %s\n", user_input); 
		if (user_input == NULL)
			return (-1);
		char *cwd;
		cwd = ft_relative_to_absolute(user_input);
		printf("new cwd = %s\n", cwd);
		if (cwd == NULL)
			return (-1);
		ft_update_pwd(pwd_node, cwd);
		printf("new $PWD = %s\n", ((t_var *)(pwd_node->content))->value );
	//	if (ft_strcmp("/", cwd) == 0 || ft_strcmp("//", cwd) == 0)
	//		break;
		free(prompt);
		free(user_input);
		free(cwd);
		//user_input = NULL;
	}
	return (0);
}