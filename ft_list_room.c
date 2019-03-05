/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_room.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychufist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 18:24:33 by ychufist          #+#    #+#             */
/*   Updated: 2019/03/02 18:40:57 by ychufist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_list_room		*ft_list_room_new(t_room room)
{
	int			i;
	t_list_room	*res;

	i = 0;
	if (!(res = (t_list_room*)malloc(sizeof(t_list_room))))
		return (NULL);
	res->id = room.id;
	res->name = room.name;
	res->links_amount = room.links_amount;
	if (room.links_amount != 0)
	{
        res->links = (int *) malloc(sizeof(int) * room.links_amount);

        while (i < room.links_amount)
        {
            res->links[i] = room.links[i];
            i++;
        }
    }
	else
	    res->links = NULL;
	res->next = NULL;
	res->prev = NULL;
	res->color = NULL;
	res->size = 1;
	return (res);
}

int				ft_list_room_find(t_list_room *dop, int id)
{
	t_list_room *room_list;

	room_list = dop;
	while (room_list)
	{
		if (room_list->id == id)
			return (1);
		room_list = room_list->next;
	}
	return (0);
}

int				ft_list_size(t_list_room *dop)
{
	int			i;
	t_list_room *room_list;

	i = 0;
	room_list = dop;
	while (room_list)
	{
		room_list = room_list->next;
		i++;
	}
	return (i);
}

void			free_list(t_list_room **dop)
{
	t_list_room *tmp;

	while (*dop)
	{
		tmp = (*dop)->next;
		free((*dop)->links);
		free(*dop);
		*dop = tmp;
	}
}
