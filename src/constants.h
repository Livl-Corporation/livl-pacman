//
// Created by Franck GUTMANN on 15/02/2023.
//

#ifndef PACMAN_CONSTANTS_H
#define PACMAN_CONSTANTS_H

#define GAME_TITLE "PacMan"

#define TIME_START_GAME_READY 2000

#define CELL_SIZE 25
#define MAP_WIDTH 21
#define MAP_HEIGHT 27

#define MAZE_SCREEN_HEIGHT 675
#define HEADER_SCREEN_HEIGHT 75
#define FOOTER_SCREEN_HEIGHT 40
#define TOTAL_SCREEN_WIDTH 525
#define TOTAL_SCREEN_HEIGHT (MAZE_SCREEN_HEIGHT + HEADER_SCREEN_HEIGHT + FOOTER_SCREEN_HEIGHT)

#define PATH_FILE_MAZE "../assets/text/maze.txt"
#define PATH_SPRITE_SHEET_PACMAN "../assets/img/pacman_sprites.bmp"

#define GAME_SPEED 200.0   // IN FPS, BIGGER IS FASTER
#define ANIMATION_SPEED 14 // BIGGER IS SLOWER
#define SPRITE_SPEED 1     // Don't change this for the moment

#define GHOST_INITIAL_POS_X 4
#define GHOST_INITIAL_POS_Y 124
#define GHOST_SPACING_X 3
#define GHOST_SPACING_Y 4
#define GHOST_SIZE 14
#define GHOST_COUNT 4

#define PACMAN_SIZE 14
#define PACMAN_SPRITE_MOUTHS_DIRECTION 3
#define PACMAN_ARROW_SIZE 7
#define PACMAN_ARROW_SPACING 20

#define EATABLE_GHOST_DURATION 1000

#define SCORE_GHOST_EATEN_DURATION 200 // when pacman eat a ghost

#define INITIAL_LIVES 3

#define BIG_COIN_RATE 50 < 30

#endif // PACMAN_CONSTANTS_H
