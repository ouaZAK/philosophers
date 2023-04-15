/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouaraqa <zouaraqa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 16:47:39 by zouaraqa          #+#    #+#             */
/*   Updated: 2023/03/04 16:15:29 by zouaraqa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	*ft_lstnew(int i)
{
	t_philo	*new;
	
	new = malloc(sizeof(t_philo));
	new->id_philo = i;
	new->next = NULL;
	return (new);
}

t_philo	*ft_lstlast(t_philo *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	ft_lstaddback(t_philo **lst, t_philo *new)
{
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	ft_lstlast(*lst)->next = new;
}

// int	ft_lstsize(t_list *lst, t_vars *ancr)
// {
// 	t_list	*tmp;
// 	int	i;

// 	i = 0;
// 	tmp = lst;
// 	while (tmp != ancr->end)
// 	{
// 		printf("tz\n");
// 		i++;
// 		tmp = tmp->next;
// 	}
// 	return (i);
// }

// void	circular_list(t_list **lst, t_list *new)
// {
// 	static int	count;
// 	t_list		*start;
// 	t_list		*end;

// 	if (!*lst)
// 	{
// 			printf(">1\n");
// 		count++;
// 		*lst = new;
// 		new->next = new;
// 		new->prev = new;
// 		return ;
// 	}
// 	start = *lst;
// 	end = *lst;
// 	if (count == 1)
// 	{
// 		printf(">2\n");
// 		count++;
// 		start = *lst;
// 		end = new;
// 		(*lst)->next = end;
// 		(*lst)->prev = end;
// 		end = start;
// 		end = start;
// 	}
// 	else
// 		{
// 			printf(">3\n");
// 			*lst = (*lst)->prev;
// 			(*lst)->next = end;
// 			start->prev = end;
// 			end->next = start;
// 			end->prev = *lst;
// 		}
	
// 	while (*lst)
// 	{
// 		printf("hm %d\n",(*lst)->nbr_philo);
// 		sleep(1);
// 		(*lst) = (*lst)->prev;
// 	}
// }
