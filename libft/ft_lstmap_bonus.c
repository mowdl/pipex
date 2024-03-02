/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-meka <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 16:56:01 by mel-meka          #+#    #+#             */
/*   Updated: 2023/11/11 16:56:08 by mel-meka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_list	*lstmap_back(t_list *lst, t_list *head,
				void *(*f)(void *), void (*del)(void *))
{
	t_list	*tail;
	void	*content;

	tail = head;
	while (lst != NULL)
	{
		content = f(lst->content);
		tail->next = ft_lstnew(content);
		if (tail->next == NULL)
		{
			del(content);
			ft_lstclear(&head, del);
			return (NULL);
		}
		lst = lst->next;
		tail = tail->next;
	}
	return (head);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*head;
	void	*content;

	if (lst == NULL || f == NULL || del == NULL)
		return (NULL);
	content = f(lst->content);
	head = ft_lstnew(content);
	if (head == NULL)
	{
		del(content);
		return (NULL);
	}
	lst = lst->next;
	return (lstmap_back(lst, head, f, del));
}
