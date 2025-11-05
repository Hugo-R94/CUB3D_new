/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrouchy <hrouchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 12:35:29 by hrouchy           #+#    #+#             */
/*   Updated: 2025/05/05 13:48:31 by hrouchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (!lst || !new)
		return ;
	new->next = *lst;
	*lst = new;
}

// int	main(void)
// {
// 	char	*middle = strdup("okokokok");
// 	char	*first_str = strdup("opppoppop");
// 	char	*last = strdup("wqqwqwwqqw");
// 	t_list	*first = ft_lstnew(middle);
// 	t_list	**list = &first;

// 	ft_lstadd_front(list, ft_lstnew(first_str));
// 	ft_lstadd_front(list, ft_lstnew(last));
// 	printf("Expect 3 elements, wqqwqwwqqw first\n");
// 	print_list(*list);
// 	return (0);
// }
