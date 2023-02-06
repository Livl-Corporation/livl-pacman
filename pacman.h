#ifndef PACMAN_H
#define PACMAN_H

#include <SDL.h>
#include <stdio.h>
#include <stdbool.h>

#define GAME_TITLE "PacMan"
#define PACMAN_PATH_BMP "./pacman_sprites.bmp"
#define GAME_SCREEN_WIDTH 700
#define GAME_SCREEN_HEIGHT 900

SDL_Window* pWindow = NULL;
SDL_Surface* win_surf = NULL;
SDL_Surface* plancheSprites = NULL;

SDL_Rect src_bg = { 200,3, 168,216 }; // x,y, w,h (0,0) en haut a gauche
SDL_Rect bg = { 4,4, 672,864 }; // ici scale x4

SDL_Rect ghost_r = { 3,123, 16,16 };
SDL_Rect ghost_l = { 37,123, 16,16 };
SDL_Rect ghost_d = { 105,123, 16,16 };
SDL_Rect ghost_u = { 71,123, 16,16 };
SDL_Rect ghost = { 34,34, 32,32 };     // ici scale x2

int count;

void init();

/**
 * @brief Met à jour la surface de la fenetre "win_surf"
 */
void draw();

#endif // PACMAN_H