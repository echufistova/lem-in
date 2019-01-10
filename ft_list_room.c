//
// Created by Yevheniya CHUFISTOVA on 2019-01-10.
//

#include "lem_in.h"

//t_list	*ft_lstnew(void const *content, size_t content_size)
//{
//	t_list *res;
//
//	if (!(res = (t_list*)malloc(sizeof(t_list))))
//		return (NULL);
//	if (content == NULL)
//	{
//		res->content = NULL;
//		res->content_size = 0;
//	}
//	else
//	{
//		if (!(res->content = (void*)malloc(content_size)))
//		{
//			free(res);
//			return (NULL);
//		}
//		res->content = ft_memcpy(res->content, content, content_size);
//		res->content_size = content_size;
//	}
//	res->next = NULL;
//	return (res);
//}

//void	ft_lstadd(t_list **alst, t_list *new)
//{
//    if (alst && *alst)
//        new->next = *alst;
//    *alst = new;
//}

t_list_room *ft_list_room_new(t_room room)
{
    int i;
    t_list_room *res;

    i = -1;
    if (!(res = (t_list_room*)malloc(sizeof(t_list_room))))
		return (NULL);
    if (!(res->name = (void*)malloc(ft_strlen(room.name))))
    {
			free(res);
			return (NULL);
    }
    res->name = room.name;
    res->links_amount = room.links_amount;
    while (++i < room.links_amount)
        res->links[i] = room.links[i];
    res->next = NULL;
    return (res);
}

void ft_list_room_add(t_list_room **alst, t_list_room *new)
{
    if (alst && *alst)
        new->next = *alst;
    *alst = new;
}