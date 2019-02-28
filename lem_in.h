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
    int         id;
    char		*name;
    t_point		coord;
    int         *links;
    int         links_amount;
    int         flag;
}					t_room;

typedef struct      s_list_room
{
    int         id;
    char		*name;
    t_point		coord;
    int         *links;
    int         links_amount;
    int         size;
    char        *color;
    struct s_list_room	*prev;
    struct s_list_room	*next;
}                   t_list_room;

typedef struct		s_farm
{
    int				ants_amount;
    int             room_amount;
    int             ways_amount;
    int             flag;
    int             col;
    int             lines;
    int             start_room_id;
    int             end_room_id;
    char            **colors;
    t_list_room		*init;
    t_list_room		*dop;
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

void add_link(t_farm *farm, char *line, int i);
int is_room(t_farm farm, char *name);
//int is_room(t_farm farm, int id);
int find_link(t_farm *farm, char *line, int k);
t_list_room *ft_list_room_new(t_room room);
int ft_list_room_find(t_list_room *room_list, int id);
int ft_list_size(t_list_room *room_list);
int is_valid_name(t_farm farm, const char *name);
void get_way(t_farm *farm, t_list_room *way, int flag);
void find_ways(t_farm *farm, int flag);
t_ant *create_ants(int ants_amount);
int move_ants(t_farm farm, t_ant *ants);
void print_ways(t_farm farm);
int is_valid_map(t_farm farm);
int is_coord(t_farm farm, t_list_room *room);
void write_error(char *s);
void free_links(int size, int *links);
void	ft_lstrm_del(t_list_room **alst);
void bonus_ways(t_farm farm, char **av);
void bonus_lines(t_farm farm, char **av);
void the_end(void);

#endif