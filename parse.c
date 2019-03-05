/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychufist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/18 14:24:19 by ychufist          #+#    #+#             */
/*   Updated: 2018/12/18 14:25:28 by ychufist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void room_init(t_farm *farm)
{
    farm->init->links_amount = 0;
    farm->init->next = (t_list_room*)malloc(sizeof(t_list_room));
    farm->init = farm->init->next;
    farm->init->color = NULL;
    farm->init->next = NULL;
    farm->init->prev = NULL;
    farm->room_amount++;
}

void init(t_farm *farm, char **av)
{
    int i;

    i = 0;
    if ((av[1] && av[1][0] == '-' && av[1][1] == 'c') || (av[2] && av[2][0] ==
                                                                   '-' && av[2][1] == 'c') || (av[3] && av[3][0] == '-' && av[3][1] == 'c'))
    {
        farm->colors = (char **) ft_memalloc(sizeof(char *) * 5);
        while (i < 5)
            farm->colors[i++] = (char *) ft_memalloc(sizeof(char) * 8);
        farm->colors[0] = ft_strcpy(farm->colors[0], "\e[91m");
        farm->colors[1] = ft_strcpy(farm->colors[1], "\e[92m");
        farm->colors[2] = ft_strcpy(farm->colors[2], "\e[93m");
        farm->colors[3] = ft_strcpy(farm->colors[3], "\e[94m");
        farm->colors[4] = ft_strcpy(farm->colors[4], "\e[95m");
        farm->col = 0;
    }
    else
    {
        farm->col = -1;
        farm->colors = NULL;
    }
    farm->flag = 0;
    farm->room_amount = 0;
    farm->ways_amount = 0;
    farm->start_room_id = -1;
    farm->end_room_id = -1;
    farm->init = (t_list_room*)malloc(sizeof(t_list_room));
    farm->init->next = NULL;
    farm->init->prev = NULL;
    farm->dop = farm->init;
}

void work(t_farm *farm, char **av)
{
    t_ant *ants;

    if (is_valid_map(*farm) && is_answer(*farm))
    {
        ft_printf("\n");
        farm->ways = (t_list_room**) malloc(sizeof(t_list_room*) *
                farm->rooms[farm->end_room_id].links_amount);
        find_ways(farm, 0);
        bonus_ways(*farm, av);
        ants = create_ants(farm->ants_amount);
        farm->lines = move_ants(*farm, ants);
        free(ants);
        bonus_lines(*farm, av);
    }
//    free_farm(farm);
}

int main(int ac, char **av)
{
    int i;
    int fd;
    char *line;
    t_farm farm;

    i = 0;
    usage();
    fd = open("/Users/ychufist/lem-in 6.14.32 PM/test", O_RDONLY);
    line = NULL;
    init(&farm, av);
    while (get_next_line(fd, &line) > 0)
    {
        if (ft_strlen(line) != 0)
        {
            write(1, line, ft_strlen(line));
            write(1, "\n", 1);
            if (ft_strchr(line, '#') && get_start_end(&farm, &line))
                continue;
            else if (!ft_strchr(line, '#') && !ft_strchr(line, '-'))
            {
                if (!get_info(&farm, line, &i))
                {
                    ft_strdel(&line);
                    system("leaks lem-in");
                    return (0);
                }
            }
            else if (!ft_strchr(line, '#') && ft_strchr(line, '-'))
            {
                if (farm.flag == 0)
                {
                    make_room(&farm);
                    farm.flag = 1;
                }
                if (!find_link(&farm, &line, 0))
                {
                    write_error("INVALID ROOM OR LINK. ERROR");
                    system("leaks lem-in");
                    return (0);
                }
            }
            else
            {
                write_error("ERROR");
                system("leaks lem-in");
                return (0);
            }
            ft_strdel(&line);
        }
        else
            {
                system("leaks lem-in");
                write_error("ERROR");
            return (0);
        }
    }
    work(&farm, av);
    the_end();
    system("leaks lem-in");
    return (0 * ac);
}