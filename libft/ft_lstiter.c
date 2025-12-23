/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtangalv <mtangalv@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 18:35:07 by mtangalv          #+#    #+#             */
/*   Updated: 2024/12/26 10:13:00 by mtangalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list	*node_ptr;

	if (!lst)
		return ;
	node_ptr = lst;
	while (node_ptr != NULL)
	{
		(*f)(node_ptr->content);
		node_ptr = node_ptr->next;
	}
}
