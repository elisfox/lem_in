/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo_bfs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjessi <fjessi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 14:39:19 by fjessi            #+#    #+#             */
/*   Updated: 2020/11/06 22:13:00 by fjessi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	find_id_room_two(t_anthill *anthill, int id, int j)
{
	anthill->parent[j] = id;
	anthill->path_len[j] = anthill->path_len[id] + 1;
	anthill->used[j] = 1;
	anthill->table_links[j][id] = 0;
}

t_queue		*find_id_room(t_anthill *anthill, t_queue *queue, int id)
{
	int j;

	j = 0;
	while (j < anthill->num_of_rooms)
	{
		if (anthill->used[j] != -1 && anthill->table_links[id][j] == 1)
		{
			queue = push_queue(queue, j);
			if (j != anthill->end)
				find_id_room_two(anthill, id, j);
			else if (j == anthill->end && \
					anthill->path_len[j] > anthill->path_len[id] + 1)
				find_id_room_two(anthill, id, j);
			else if (j == anthill->end && anthill->path_len[j] == -1)
			{
				anthill->parent[j] = id;
				anthill->path_len[j] = anthill->path_len[id] + 1;
				anthill->used[j] = 1;
				anthill->table_links[j][id] = 0;
			}
		}
		j++;
	}
	return (queue);
}

void		algo_bfs(t_anthill *anthill)
{
	t_queue *queue;
	int		id_room;

	queue = NULL;
	queue = push_queue(queue, anthill->start);
	anthill->path_len[anthill->start] = 0;
	anthill->used[anthill->start] = 1;
	while (!empty_queue(queue))
	{
		id_room = queue->num;
		queue = pop_queue(queue);
		if (id_room == anthill->end)
			continue ;
		queue = find_id_room(anthill, queue, id_room);
	}
	while (!empty_queue(queue))
	{
		queue = pop_queue(queue);
	}
}
