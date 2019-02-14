/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychufist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/18 14:33:27 by ychufist          #+#    #+#             */
/*   Updated: 2018/12/18 14:33:30 by ychufist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "libft/libft.h"
# include "libft/get_next_line.h"
# include "libft/ft_printf.h"

typedef struct 		s_point
{
	int x;
	int y;
}					t_point;

typedef struct		s_room
{
	char		*name;
	t_point		coord;
	char		**links;
	int         links_amount;
	int         flag;
}					t_room;

typedef struct      s_list_room
{
    char		*name;
    t_point		coord;
    char		**links;
    int         links_amount;
    int         size;
    struct s_list_room	*prev;
    struct s_list_room	*next;
}                   t_list_room;

typedef struct		s_farm
{
    int				ants_amount;
    int             room_amount;
    int             ways_amount;
    int             flag;
    int             start_room_id;
    int             end_room_id;
    t_room			*rooms;
    t_list_room     **ways;
}					t_farm;

typedef struct		s_ant
{
	int number;
	t_list_room     *way;
	int way_size;
	int currnet_index;
}					t_ant;

void add_room(t_farm *farm);
void add_link(t_farm *farm, char *line, int i);
int is_room(t_farm farm, char *name);
t_list_room *ft_list_room_new(t_room room);
t_list_room find_parent(char *room_name, t_list_room *way);
void ft_list_room_add(t_list_room **alst, t_list_room *new);
int ft_list_room_find(t_list_room *room_list, char *name);
int ft_list_size(t_list_room *room_list);
void print_list(t_list_room *room_list);
int is_valid_name(const char *name);
void get_way(t_farm *farm, t_list_room *way);
t_list_room *find_ways(t_farm *farm);
t_ant *create_ants(int ants_amount);

#endif