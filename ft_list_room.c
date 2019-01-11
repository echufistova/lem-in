//
// Created by Yevheniya CHUFISTOVA on 2019-01-10.
//

#include "lem_in.h"

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
    res->links = (char**)malloc(sizeof(char*) * room.links_amount);
    while (++i < room.links_amount)
        res->links[i] = room.links[i];
    res->next = NULL;
    return (res);
}

int ft_list_room_find(t_list_room *room_list, char *name)
{
    while (room_list)
    {
        if (ft_strcmp(room_list->name, name) == 0)
            return (0);
        room_list = room_list->next;
    }
    return (1);
}

int ft_list_size(t_list_room *room_list)
{
    int i;

    i = 0;
    while (room_list)
    {
        room_list = room_list->next;
        i++;
    }
    return (i);
}

void ft_list_room_add(t_list_room **alst, t_list_room *new)
{
    if (alst && *alst)
        new->next = *alst;
    *alst = new;
}
//
//void	ft_lstdelone(t_list **alst, void (*del)(void *, size_t))
//{
//    t_list	*dop;
//
//    if (alst && *alst && del)
//    {
//        dop = (*alst)->next;
//        del((*alst)->content, (*alst)->content_size);
//        free(*alst);
//        *alst = NULL;
//    }
//}
//
//void	ft_lst_delone_room(t_list_room **alst, void (*del)(void *, size_t))
//{
//    t_list	*dop;
//
//    if (alst && *alst && del)
//    {
//        dop = (*alst)->next;
//        del((*alst)->name, (*alst)->ft_strlen((*alst)->name));
//        free(*alst);
//        *alst = NULL;
//    }
//}