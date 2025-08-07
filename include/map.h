/**
 * @file map.h
 *
 * Copyright (C) 2025 Gustavo Bacagine
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation; version 3 of the License.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program; if not, see <https://www.gnu.org/licenses>.
 *
 * @brief A simple dot maze game written in ANSI C using SDL2
 *
 * @author Gustavo Bacagine <gustavo.bacagine@protonmail.com> in Aug 2025
 */

#ifndef _MAP_H_
#define _MAP_H_

#include "util.h"
#include "player.h"
#include "ghost.h"
#include "audio.h"

/**
 * @def MAP_ROW
 * @brief Max map rows
 */
#define MAP_ROW 16

/**
 * @def MAP_COL
 * @brief Max map cols
 */
#define MAP_COL 16

/**
 * @def NONE_MOVEMENT
 * @brief No movement
 */
#define NONE_MOVEMENT -1

/**
 * @def UP_MOVEMENT
 * @brief Up movement
 */
#define UP_MOVEMENT    0

/**
 * @def LEFT_MOVEMENT
 * @brief Left movement
 */
#define LEFT_MOVEMENT  1

/**
 * @def DOWN_MOVEMENT
 * @brief Down movement
 */
#define DOWN_MOVEMENT  2

/**
 * @def RIGHT_MOVENT
 * @brief Right movement
 */
#define RIGHT_MOVENT   3

/**
 * @brief Set the coordinates of character in the map
 *
 * @param iX New col
 * @param iY New row
 */
void vSetCoordinates(int iX, int iY);

/**
 * @brief Update the map with new coordinates
 */
void vUpdateMap(void);

/**
 * @brief Get the initial player x, y coordinates
 */
void vGetInitialPlayerPosition(void);

/**
 * @brief Get the initial ghosts x, y coordinates
 */
void vGetInitialGhostsPosition(void);

/**
 * @brief Gets total score in the level
 */
void vGetTotalScoreLevel(void);

/**
 * @brief Load a level from a file
 *
 * @param kpszMapFile is the path of level file
 * @return TRUE load with success
 * @return FALSE level load error
 */
boolean bLoadLevel(const char *kpszMapFile);

/**
 * @var gszMap
 * @brief The game matrix map
 */
extern char gszMap[MAP_ROW][MAP_COL];

/**
 * @var gbHeroEndMap
 * @brief Defines whether the player has reached the end of the map
 */
extern boolean gbHeroEndMap;

/**
 * @var gbGhostEndMap
 * @brief Defines whether the ghost has reached the end of the map
 */
extern boolean gbGhostEndMap;

/**
 * @var giTotalGameScore
 * @brief Sum of the total scores of the game
 */
extern int giTotalGameScore;

/**
 * @var giCurrentLevelScore
 * @brief Player's score at current level
 */
extern int giCurrentLevelScore;

/**
 * @var giTotalCurrentLevelScore
 * @brief Total score of the level
 */
extern int giTotalCurrentLevelScore;

/**
 * @var giPowersCollected
 * @brief Used to kill ghosts
 */
extern int giPowersCollected;

/**
 * @var giLevel
 * @brief Current game level
 */
extern int giLevel;

/**
 * @var gbGameOver
 * @brief Define if the game is over
 */
extern boolean gbGameOver;

/**
 * @var gpstPowerUpSound
 * @brief It's the power up sound
 */
extern Mix_Chunk* gpstPowerUpSound;

/**
 * @var gpstLevelUpSound
 * @brief It's the level up sound
 */
extern Mix_Chunk* gpstLevelUpSound;

/**
 * @var gpstGameWinSound
 * @brief It's the game win sound
 */
extern Mix_Chunk* gpstGameWinSound;

#endif
