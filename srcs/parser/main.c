/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroux-fo <jroux-fo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 14:10:11 by jroux-fo          #+#    #+#             */
/*   Updated: 2022/05/23 14:11:21 by ychibani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_status;

void	ft_garbage(t_list **bin)
{
	t_list	*to_suppr;

	while (*bin)
	{
		to_suppr = *bin;
		*bin = to_suppr->next;
		free(to_suppr->content);
		free(to_suppr);
	}
	*bin = NULL;
}

////// utils pour token

t_token	*ft_lstnew_token(t_list **bin, char *content, int type)
{
	t_token	*newcell;

	newcell = malloc(sizeof(t_token));
	ft_lstadd_back(bin, ft_lstnew(newcell));
	if (!newcell)
		return (NULL);
	newcell->content = content;
	newcell->type = type;
	newcell->next = NULL;
	return (newcell);
}

t_token	*ft_lstlast_token(t_token *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	ft_lstadd_back_token(t_token **alst, t_token *new)
{
	t_token	*temp;

	if (!*alst)
	{
		*alst = new;
		return ;
	}
	temp = ft_lstlast_token(*alst);
	temp->next = new;
}

void	ft_preparse(int argc, char **argv, char **env)
{
	(void)argv;
	(void)env;
	if (argc != 1)
	{
		printf("no need to put arguments, simply type: ./minishell\n");
		exit(1);
	}
	return ;
}

void	ft_print_token(t_token *token)
{
	int	i;

	printf("printing token list...\n");
	i = 1;
	while (token)
	{
		printf("---------------\n");
		printf("numero: %d\ntype: %d\ncontent:\e[38;5;196m->\033[0m%s\e[38;5;196m<-\033[0m\n", i, token->type, (char *)token->content);
		printf("---------------\n");
		i++;
		token = token->next;
	}
}

void	ft_clean_token(t_token **token)
{
	// t_token *to_suppr;

	// while (*token)
	// {
	// 	to_suppr = *token;
	// 	*token = to_suppr->next;
	// 	//free si pas | ou si pas $
	// 	free(to_suppr);
	// }
	*token = NULL;
}

void	ft_parse_operator(t_token **token, t_list **bin, char c)
{
	if (c == '|')
		ft_lstadd_back_token(token, ft_lstnew_token(bin, "|", OPERATOR));
	if (c == '$')
		ft_lstadd_back_token(token, ft_lstnew_token(bin, "$", OPERATOR));
}

void	ft_parse_ponct(t_token **token, t_list **bin, char c)
{
	if (c == 39)
		ft_lstadd_back_token(token, ft_lstnew_token(bin, "\'", PONCT));
	if (c == 34)
		ft_lstadd_back_token(token, ft_lstnew_token(bin, "\"", PONCT));
}

int	ft_parse_redir(t_token **token, t_list **bin, char c, char *str)
{
	if (c == 60)
	{
		if (str[1] == 60)
		{
			ft_lstadd_back_token(token, ft_lstnew_token(bin, "<<", REDIR));
			return (1);
		}
		else
			ft_lstadd_back_token(token, ft_lstnew_token(bin, "<", REDIR));
	}
	if (c == 62)
	{
		if (str[1] == 62)
		{
			ft_lstadd_back_token(token, ft_lstnew_token(bin, ">>", REDIR));
			return (1);
		}
		else
			ft_lstadd_back_token(token, ft_lstnew_token(bin, ">", REDIR));
	}
	return (0);
}

int	ft_parse_word(t_token **token, t_list **bin, char *str)
{
	int	i;
	int	j;
	char *dest;

	i = 0;
	// printf ("la str :%s\n", str);
	j = 0;
	while (str[i] != '|' && str[i] != '$' && str[i] != 39 && str[i] != 34
		&& str[i] != ' ' && str[i])
		i++;
	dest = (char *)malloc(sizeof(char) * i + 1);
	ft_lstadd_back(bin, ft_lstnew(dest));
	while (j < i)
	{
		dest[j] = str[j];
		j++;
	}
	dest[j] = '\0';
	ft_lstadd_back_token(token, ft_lstnew_token(bin, dest, WORD));
	return (i - 1);
}

void	ft_parse(t_token **token, t_list **bin, char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '|' || str[i] == '$')
			ft_parse_operator(token, bin, str[i]);
		else if (str[i] == 39 || str[i] == 34)
			ft_parse_ponct(token, bin, str[i]);
		else if (str[i] == 60 || str[i] == 62)
			i = i + ft_parse_redir(token, bin, str[i], str + i);
		else if (str[i] == ' ')
			ft_lstadd_back_token(token, ft_lstnew_token(bin, " ", SPACE));
		else
			i = i + ft_parse_word(token, bin, str + i);
		i++;
	}
	ft_print_token(*token);
	printf("fin du parsing\n");
}

void	ft_supspace(t_token *token)
{
	while (token)
	{
		while (!ft_strcmp(token->content, " ") && !ft_strcmp(token->next->content, " "))
			token->next = token->next->next;
		token = token->next;
	}
}

t_token	*ft_joincontent(t_token *temp, t_token *token, t_list **bin)
{
	char	*str;
	int		i;
	int		j;

	if (temp == NULL)
		return (ft_lstnew_token(bin, token->content, 5));
	str = malloc(sizeof(char) * (ft_strlen(temp->content) + ft_strlen(token->content)) + 1);
	ft_lstadd_back(bin, ft_lstnew(str));
	i = 0;
	j = 0;
	while (temp->content[i])
	{
		str[i] = temp->content[i];
		i++;
	}
	while (token->content[j])
	{
		// printf("on ajoute ce caractere a la sting ->%c<-\n",)
		str[i] = token->content[j];
		i++;
		j++;
	}
	str[i] = '\0';
	temp->content = str;
	return (temp);
}

t_token	*ft_find_quote(t_token *token)
{
	while (token)
	{
		if (!ft_strcmp(token->content, "\""))
			return(token);
		token = token->next;
	}
	return (token);
}

void	ft_doublequotes(t_token *token, t_list **bin)
{
	t_token *temp;
	t_token *stop;

	// (void)bin;
	temp = NULL;
	while (token)
	{
		printf("la boucle\n");
		if (!ft_strcmp(token->content, "\""))
		{
			stop = token;
			stop = stop->next;
			while (ft_strcmp(stop->content, "\""))
			{
				temp = ft_joincontent(temp, stop, bin);
				// printf("content = %s\n", temp->content);
				stop = stop->next;
			}
			token->next = temp;
			temp->next = ft_find_quote(token);
		}
		else
			token = token->next;
	}
}

void	ft_simplify(t_token **token, t_list **bin)
{
	ft_supspace(*token);
	ft_doublequotes(*token, bin);
}

// void	ft_catch(int sig)
// {
// 	(void)sig;
// 	printf("ptit ctrl c en legende\n");
// 	return ;
// }

// void	ft_prompt(t_token **token, t_list **bin)
// {
// 	char *str;
	
// 	str = NULL;
// 	// str = readline("\033[95mminishell$\033[0m ");
// 	while (ft_strcmp(str, "exit") && str != NULL)
// 	{
// 		// printf("la string ->%s<-\n", str);
// 		// if (str[0] != '\0')
// 		// 	add_history(str);

// 		//parsing pur et dur (division des elements en tokens)
// 		ft_parse(token, bin, str);
// 		//simplification des tokens
// 		ft_simplify(token, bin);
// 		ft_print_token(*token);

// 		// envoie des infos a Yassine
// 		ft_garbage(bin);
// 		ft_clean_token(token);
// 		free (str);
// 		str = readline("\033[95mminishell$\033[0m ");
// 	}
// 	free (str);
// }

int	main(int argc, char **argv, char **env)
{
	t_list	*bin;

	ft_preparse(argc, argv, env);
	bin = NULL;

	ft_printf("%d\n", ft_strlen(argv[0]));
	// signal(SIGINT, ft_catch);
	

	ft_garbage(&bin);
	exit(0);
}
