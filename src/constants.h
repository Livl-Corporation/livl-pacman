//
// Created by Franck GUTMANN on 15/02/2023.
//

#ifndef PACMAN_CONSTANTS_H
#define PACMAN_CONSTANTS_H

#define GAME_TITLE "PacMan"

#define CELL_SIZE 32

#define MAP_WIDTH 21
#define MAP_HEIGHT 27

#define WINDOW_SCREEN_WIDTH 672
#define WINDOW_SCREEN_HEIGHT 864

#define PATH_FILE_MAZE "../assets/text/maze.txt"
#define PATH_SPRITE_SHEET_PACMAN "../assets/img/pacman_sprites.bmp"
#define PATH_SPRITE_SHEET_PLAY_BTN "../assets/img/play_btn.bmp"

#define GAME_SPEED 200.0 // IN FPS, BIGGER IS FASTER
#define ANIMATION_SPEED 14 // BIGGER IS SLOWER
#define SPRITE_SPEED 1 // Don't change this for the moment

#define GHOST_INITIAL_POS_X 4
#define GHOST_INITIAL_POS_Y 124

#define GHOST_SPACING_X 3
#define GHOST_SPACING_Y 4

#define GHOST_SIZE 14
#define GHOST_COUNT 4

#endif // PACMAN_CONSTANTS_H
