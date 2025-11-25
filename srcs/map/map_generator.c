/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_generator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugz <hugz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 12:26:31 by hrouchy           #+#    #+#             */
/*   Updated: 2025/11/21 16:36:52 by hugz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "../includes/cub3d.h"

#ifdef BONUS
// Vérifie si une position est valide dans la map
int is_valid_pos(int x, int y, int map_w, int map_h)
{
    return (x >= 0 && x < map_w && y >= 0 && y < map_h);
}

char **alloc_map(int map_w, int map_h)
{
    char **map = calloc(map_h + 1, sizeof(char *)); // +1 pour NULL final
    for (int y = 0; y < map_h; y++)
    {
        map[y] = calloc(map_w + 1, sizeof(char));
        for (int x = 0; x < map_w; x++)
            map[y][x] = '1'; // murs par défaut
        map[y][map_w] = '\0';
    }
    map[map_h] = NULL;
    return map;
}



typedef struct {
    int x, y;
} t_point;

// // Fonction pour vérifier si une case est valide pour BFS
int is_valid(int x, int y, char **map, int **visited, int map_w, int map_h)
{
    return (x >= 0 && x < map_w && y >= 0 && y < map_h
            && (map[y][x] == '0' || map[y][x] == 'D' || map[y][x] == 'E')
            && visited[y][x] == -1);
}

void setup_player_exit(char **map, int map_w, int map_h)
{
    int px = -1, py = -1;

    // Parcours de la map de haut à gauche vers bas à droite
    for (int y = 0; y < map_h && py == -1; y++) {
        for (int x = 0; x < map_w; x++) {
            if (map[y][x] == '0') {
                map[y][x] = 'S';  // placer le joueur
                px = x;
                py = y;
                break;
            }
        }
    }

    if (px == -1) return; // pas de case libre trouvée

    // Initialiser le tableau de distances pour le flood fill
    int **dist = malloc(sizeof(int*) * map_h);
    for (int y = 0; y < map_h; y++) {
        dist[y] = malloc(sizeof(int) * map_w);
        for (int x = 0; x < map_w; x++)
            dist[y][x] = -1;
    }

    t_point queue[map_w * map_h];
    int front = 0, back = 0;
    queue[back++] = (t_point){px, py};
    dist[py][px] = 0;

    int dx[4] = {1, -1, 0, 0};
    int dy[4] = {0, 0, 1, -1};

    while (front < back) {
        t_point p = queue[front++];
        for (int i = 0; i < 4; i++) {
            int nx = p.x + dx[i];
            int ny = p.y + dy[i];
            if (is_valid(nx, ny, map, dist, map_w, map_h)) { // ajouter map_w, map_h dans is_valid
                dist[ny][nx] = dist[p.y][p.x] + 1;
                queue[back++] = (t_point){nx, ny};
            }
        }
    }

    int max_dist = -1;
    int ex = px, ey = py;
    for (int y = 0; y < map_h; y++)
        for (int x = 0; x < map_w; x++)
            if (dist[y][x] > max_dist) {
                max_dist = dist[y][x];
                ex = x;
                ey = y;
            }
    map[ey][ex] = 'X';

    for (int y = 0; y < map_h; y++)
        free(dist[y]);
    free(dist);
}


t_room create_room(char **map, int x, int y, int w, int h, int map_w, int map_h)
{
    t_room room;
    room.x = x;
    room.y = y;
    room.w = w;
    room.h = h;
    room.cx = x + w / 2;
    room.cy = y + h / 2;

    int enemies_to_place = 2 + rand() % 2;
    int placed = 0;

    for (int j = 0; j < h; j++)
    {
        for (int i = 0; i < w; i++)
        {
            int nx = x + i;
            int ny = y + j;
            if (nx <= 0 || nx >= map_w - 1 || ny <= 0 || ny >= map_h - 1)
                continue;

            if (i == 0 || i == w-1 || j == 0 || j == h-1)
                map[ny][nx] = '1';
            else
                map[ny][nx] = '0';
        }
    }

    while (placed < enemies_to_place)
    {
        int ex = x + 1 + rand() % (w - 2);
        int ey = y + 1 + rand() % (h - 2);
        if (map[ey][ex] == '0')
        {
            if (placed %2 == 0)
                map[ey][ex] = 'M';
            else 
                map[ey][ex] = 'B';
            placed++;
        }
    }

    return (room);
}




void carve_tile(char **map, int x, int y, int map_w, int map_h)
{
    if (x <= 0 || y <= 0 || x >= map_w - 1 || y >= map_h - 1)
        return;

    if (map[y][x] == '1' || map[y][x] == ' ')
        map[y][x] = '0';
}




void create_corridor(char **map, t_room room1, t_room room2, int map_w, int map_h)
{
    int x = room1.cx;
    int y = room1.cy;
    int x_end = room2.cx;
    int y_end = room2.cy;
    int door_placed = 0;

    while (x != x_end)
    {
        x += (x < x_end) ? 1 : -1;
        if (!door_placed && map[y][x] == '1')
        {
            map[y][x] = 'D';
            door_placed = 1;
        }
        else
            carve_tile(map, x, y, map_w, map_h);
    }

    while (y != y_end)
    {
        y += (y < y_end) ? 1 : -1;
        carve_tile(map, x, y, map_w, map_h);
    }
}


// void create_corridor(char **map, t_room room1, t_room room2)
// {
//     int x = room1.cx;
//     int y = room1.cy;
//     int x_end = room2.cx;
//     int y_end = room2.cy;

//     while (x != x_end)
//     {
//         if (x < x_end) x++;
//         else x--;
//         carve_tile(map, x, y);
//     }
//     while (y != y_end)
//     {
//         if (y < y_end) y++;
//         else y--;
//         carve_tile(map, x, y);
//     }
// }
// Vérifie si une nouvelle salle est trop proche d'une salle existante



char **generate_map(int map_w, int map_h)
{
    char **map = alloc_map(map_w, map_h);
    int number_room = 3 + rand() % 4; // entre 3 et 6 salles
    t_room rooms[10];
    int room_count = 0;
    int tries = 0;

    while (room_count < number_room && tries < 200)
    {
        tries++;

        int w = 7 + rand() % 4; // largeur 7-10
        int h = 7 + rand() % 4; // hauteur 7-10

        int max_x = map_w - w - 2;
        int max_y = map_h - h - 2;

        if (max_x <= 0 || max_y <= 0)
            break; // map trop petite pour cette salle

        int x = 1 + rand() % max_x;
        int y = 1 + rand() % max_y;

        if (is_too_close_x(rooms, room_count, x, w) && is_too_close_y(rooms, room_count, y, h))
            continue; // essaie une autre position

        rooms[room_count] = create_room(map, x, y, w, h, map_w, map_h);

        if (room_count > 0)
            create_corridor(map, rooms[room_count - 1], rooms[room_count], map_w, map_h);

        room_count++;
    }

    return map;
}



char **make_map(t_data *data)
{
    srand(time(NULL));
    char **map = generate_map(data->map_w, data->map_h);
	// printf("map W = %i | map H = %i \n",data->map_w, data->map_h);
	// printf("res X = %i | res Y = %i \n",data->res_x, data->res_y);
    clean_map(map, data->map_w, data->map_h);
    setup_player_exit(map, data->map_w, data->map_h);
    reparse(map);
    return map;
}
#endif