// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   map_generator2.c                                   :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: hrouchy <hrouchy@student.42.fr>            +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2025/09/01 12:26:31 by hrouchy           #+#    #+#             */
// /*   Updated: 2025/10/10 11:24:21 by hrouchy          ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include <stdio.h>
// #include <stdlib.h>
// #include <math.h>
// #include "../includes/cub3d.h"

// typedef struct {
//     int x, y;
// } t_point;

// typedef struct {
//     int map_w;
//     int map_h;
//     int num_rooms;
//     int enemies_per_room;
// } t_difficulty;

// // Calcul de la difficulté avec courbe ease-in cubic
// t_difficulty calculate_difficulty(int level)
// {
//     t_difficulty diff;
    
//     // Courbe ease-in cubic: y = x^3
//     float t = level / 20.0f;
//     if (t > 1.0f) t = 1.0f;
//     float cubic = t * t * t;
    
//     // Taille de la map (de 40x40 à 100x100)
//     diff.map_w = 40 + (int)(cubic * 60);
//     diff.map_h = 40 + (int)(cubic * 60);
    
//     // Nombre de salles (de 4 à 15)
//     diff.num_rooms = 4 + (int)(cubic * 11);
    
//     // Ennemis par salle (de 2 à 6)
//     diff.enemies_per_room = 2 + (int)(cubic * 4);
    
//     return diff;
// }

// int is_valid_pos(int x, int y, int map_w, int map_h)
// {
//     return (x >= 0 && x < map_w && y >= 0 && y < map_h);
// }

// char **alloc_map(int map_w, int map_h)
// {
//     char **map = calloc(map_h + 1, sizeof(char *));
//     for (int y = 0; y < map_h; y++)
//     {
//         map[y] = calloc(map_w + 1, sizeof(char));
//         for (int x = 0; x < map_w; x++)
//             map[y][x] = '1';
//         map[y][map_w] = '\0';
//     }
//     map[map_h] = NULL;
//     return map;
// }

// int is_valid(int x, int y, char **map, int **visited, int map_w, int map_h)
// {
//     return (x >= 0 && x < map_w && y >= 0 && y < map_h
//             && (map[y][x] == '0' || map[y][x] == 'D' || map[y][x] == 'E' || map[y][x] == 'M')
//             && visited[y][x] == -1);
// }

// // Crée la salle de spawn du joueur (5x5)
// t_room create_spawn_room(char **map, int map_w, int map_h)
// {
// 	if(map_w || map_h)
// 		printf("");
//     t_room room;
//     int w = 5;
//     int h = 5;
    
//     // Centrer dans un coin avec marge
//     int x = 3;
//     int y = 3;
    
//     room.x = x;
//     room.y = y;
//     room.w = w;
//     room.h = h;
//     room.cx = x + w / 2;
//     room.cy = y + h / 2;
    
//     // Créer la salle
//     for (int j = 0; j < h; j++)
//     {
//         for (int i = 0; i < w; i++)
//         {
//             int nx = x + i;
//             int ny = y + j;
            
//             if (i == 0 || i == w-1 || j == 0 || j == h-1)
//                 map[ny][nx] = '1';
//             else
//                 map[ny][nx] = '0';
//         }
//     }
    
//     // Placer le joueur au centre
//     map[room.cy][room.cx] = 'N';
    
//     return room;
// }

// t_room create_room(char **map, int x, int y, int w, int h, int map_w, int map_h, int enemies_to_place)
// {
// 	if (map_w || map_h)
// 		printf("");
//     t_room room;
//     room.x = x;
//     room.y = y;
//     room.w = w;
//     room.h = h;
//     room.cx = x + w / 2;
//     room.cy = y + h / 2;
    
//     int placed = 0;
    
//     // Créer la salle
//     for (int j = 0; j < h; j++)
//     {
//         for (int i = 0; i < w; i++)
//         {
//             int nx = x + i;
//             int ny = y + j;
            
//             if (i == 0 || i == w-1 || j == 0 || j == h-1)
//                 map[ny][nx] = '1';
//             else
//                 map[ny][nx] = '0';
//         }
//     }
    
//     // Placer les ennemis
//     while (placed < enemies_to_place && w > 2 && h > 2)
//     {
//         int ex = x + 1 + rand() % (w - 2);
//         int ey = y + 1 + rand() % (h - 2);
//         if (map[ey][ex] == '0')
//         {
//             map[ey][ex] = 'M';
//             placed++;
//         }
//     }
    
//     return room;
// }

// // Trouve le point de sortie optimal sur le bord d'une salle vers une cible
// t_point get_best_exit_point(t_room room, int target_x, int target_y)
// {
//     t_point p;
//     int dx = target_x - room.cx;
//     int dy = target_y - room.cy;
    
//     // Déterminer de quel côté sortir en fonction de la direction
//     if (abs(dx) > abs(dy))
//     {
//         // Sortir horizontalement
//         if (dx > 0)
//         {
//             p.x = room.x + room.w - 1; // Droite
//             p.y = room.cy;
//         }
//         else
//         {
//             p.x = room.x; // Gauche
//             p.y = room.cy;
//         }
//     }
//     else
//     {
//         // Sortir verticalement
//         if (dy > 0)
//         {
//             p.x = room.cx;
//             p.y = room.y + room.h - 1; // Bas
//         }
//         else
//         {
//             p.x = room.cx;
//             p.y = room.y; // Haut
//         }
//     }
    
//     return p;
// }

// void carve_tile(char **map, int x, int y, int map_w, int map_h)
// {
//     if (x <= 0 || y <= 0 || x >= map_w - 1 || y >= map_h - 1)
//         return;
    
//     if (map[y][x] == '1')
//         map[y][x] = '0';
// }

// // Vérifie si on est sur le bord d'une salle
// int is_room_border(char **map, int x, int y, int map_w, int map_h)
// {
//     if (x <= 0 || y <= 0 || x >= map_w - 1 || y >= map_h - 1)
//         return 0;
    
//     if (map[y][x] != '1')
//         return 0;
    
//     // Vérifier si adjacent à un '0'
//     if ((x > 0 && map[y][x-1] == '0') ||
//         (x < map_w - 1 && map[y][x+1] == '0') ||
//         (y > 0 && map[y-1][x] == '0') ||
//         (y < map_h - 1 && map[y+1][x] == '0'))
//         return 1;
    
//     return 0;
// }

// void create_corridor(char **map, t_room room1, t_room room2, int map_w, int map_h)
// {
//     // Trouver les meilleurs points de sortie
//     t_point start = get_best_exit_point(room1, room2.cx, room2.cy);
//     t_point end = get_best_exit_point(room2, room1.cx, room1.cy);
    
//     int x = start.x;
//     int y = start.y;
//     int door1_placed = 0;
//     // int door2_placed = 0;
    
//     // Placer porte de sortie de room1
//     if (is_room_border(map, x, y, map_w, map_h))
//     {
//         map[y][x] = 'D';
//         door1_placed = 1;
//         // Avancer d'une case
//         if (end.x != x)
//             x += (x < end.x) ? 1 : -1;
//         else if (end.y != y)
//             y += (y < end.y) ? 1 : -1;
//     }
    
//     // Creuser le couloir horizontal
//     while (x != end.x)
//     {
//         carve_tile(map, x, y, map_w, map_h);
//         carve_tile(map, x, y + 1, map_w, map_h); // Largeur 2
//         x += (x < end.x) ? 1 : -1;
//     }
    
//     // Creuser le couloir vertical
//     while (y != end.y)
//     {
//         carve_tile(map, x, y, map_w, map_h);
//         carve_tile(map, x + 1, y, map_w, map_h); // Largeur 2
//         y += (y < end.y) ? 1 : -1;
//     }
    
//     // S'assurer d'arriver au point final
//     carve_tile(map, end.x, end.y, map_w, map_h);
    
//     // Placer porte d'entrée dans room2
//     if (is_room_border(map, end.x, end.y, map_w, map_h))
//         map[end.y][end.x] = 'D';
// }

// // Vérifie si deux salles se chevauchent
// int rooms_overlap(t_room r1, t_room r2, int margin)
// {
//     return !(r1.x + r1.w + margin <= r2.x ||
//              r2.x + r2.w + margin <= r1.x ||
//              r1.y + r1.h + margin <= r2.y ||
//              r2.y + r2.h + margin <= r1.y);
// }

// // S'assure que toute la bordure de la map est un mur
// void seal_map_borders(char **map, int map_w, int map_h)
// {
//     // Bordure supérieure et inférieure
//     for (int x = 0; x < map_w; x++)
//     {
//         map[0][x] = '1';
//         map[map_h - 1][x] = '1';
//     }
    
//     // Bordure gauche et droite
//     for (int y = 0; y < map_h; y++)
//     {
//         map[y][0] = '1';
//         map[y][map_w - 1] = '1';
//     }
// }

// char **generate_map(int level, int *out_map_w, int *out_map_h)
// {
//     t_difficulty diff = calculate_difficulty(level);
//     *out_map_w = diff.map_w;
//     *out_map_h = diff.map_h;
    
//     char **map = alloc_map(diff.map_w, diff.map_h);
//     t_room rooms[25];
//     int room_count = 0;
//     int tries = 0;
    
//     // Créer la salle de spawn en premier
//     rooms[room_count] = create_spawn_room(map, diff.map_w, diff.map_h);
//     room_count++;
    
//     // Créer les autres salles
//     while (room_count < diff.num_rooms && tries < 1000)
//     {
//         tries++;
        
//         int w = 7 + rand() % 5; // 7-11
//         int h = 7 + rand() % 5; // 7-11
        
//         int max_x = diff.map_w - w - 3;
//         int max_y = diff.map_h - h - 3;
        
//         if (max_x <= 10 || max_y <= 3)
//             break;
        
//         // Éviter la zone de spawn (0-12 en x et y)
//         int x = 15 + rand() % (max_x - 15);
//         int y = 3 + rand() % (max_y - 3);
        
//         // Vérifier qu'elle ne chevauche pas les autres
//         t_room new_room;
//         new_room.x = x;
//         new_room.y = y;
//         new_room.w = w;
//         new_room.h = h;
//         new_room.cx = x + w / 2;
//         new_room.cy = y + h / 2;
        
//         int valid = 1;
//         for (int i = 0; i < room_count; i++)
//         {
//             if (rooms_overlap(rooms[i], new_room, 3))
//             {
//                 valid = 0;
//                 break;
//             }
//         }
        
//         if (!valid)
//             continue;
        
//         rooms[room_count] = create_room(map, x, y, w, h, diff.map_w, diff.map_h, diff.enemies_per_room);
        
//         // Relier à la salle précédente
//         create_corridor(map, rooms[room_count - 1], rooms[room_count], diff.map_w, diff.map_h);
        
//         room_count++;
//     }
    
//     // S'assurer que toute la bordure est fermée
//     seal_map_borders(map, diff.map_w, diff.map_h);
    
//     return map;
// }

// void setup_exit(char **map, int map_w, int map_h)
// {
//     // Trouver la position du joueur
//     int px = -1, py = -1;
//     for (int y = 0; y < map_h && py == -1; y++)
//     {
//         for (int x = 0; x < map_w; x++)
//         {
//             if (map[y][x] == 'N')
//             {
//                 px = x;
//                 py = y;
//                 break;
//             }
//         }
//     }
    
//     if (px == -1) return;
    
//     // Flood fill pour trouver la case la plus éloignée
//     int **dist = malloc(sizeof(int*) * map_h);
//     for (int y = 0; y < map_h; y++)
//     {
//         dist[y] = malloc(sizeof(int) * map_w);
//         for (int x = 0; x < map_w; x++)
//             dist[y][x] = -1;
//     }
    
//     t_point queue[map_w * map_h];
//     int front = 0, back = 0;
//     queue[back++] = (t_point){px, py};
//     dist[py][px] = 0;
    
//     int dx[4] = {1, -1, 0, 0};
//     int dy[4] = {0, 0, 1, -1};
    
//     while (front < back)
//     {
//         t_point p = queue[front++];
//         for (int i = 0; i < 4; i++)
//         {
//             int nx = p.x + dx[i];
//             int ny = p.y + dy[i];
//             if (is_valid(nx, ny, map, dist, map_w, map_h))
//             {
//                 dist[ny][nx] = dist[p.y][p.x] + 1;
//                 queue[back++] = (t_point){nx, ny};
//             }
//         }
//     }
    
//     // Trouver la case la plus éloignée
//     int max_dist = -1;
//     int ex = px, ey = py;
//     for (int y = 0; y < map_h; y++)
//     {
//         for (int x = 0; x < map_w; x++)
//         {
//             if (dist[y][x] > max_dist && map[y][x] == '0')
//             {
//                 max_dist = dist[y][x];
//                 ex = x;
//                 ey = y;
//             }
//         }
//     }
    
//     map[ey][ex] = 'X';
    
//     for (int y = 0; y < map_h; y++)
//         free(dist[y]);
//     free(dist);
// }

// char **make_map(t_data *data, int level)
// {
//     srand(time(NULL));
    
//     int map_w, map_h;
//     char **map = generate_map(level, &map_w, &map_h);
    
//     data->map_w = map_w;
//     data->map_h = map_h;
    
//     printf("=== LEVEL %d ===\n", level);
//     printf("Map size: %d x %d\n", map_w, map_h);
//     printf("Resolution: %d x %d\n", data->res_x, data->res_y);
    
//     clean_map(map, map_w, map_h);
//     setup_exit(map, map_w, map_h);
//     reparse(map);
    
//     return map;
// }