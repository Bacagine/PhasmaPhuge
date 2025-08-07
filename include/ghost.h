/**
 * @file ghost.h
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

#ifndef _GHOST_H_
#define _GHOST_H_

#include "entity.h"
#include "audio.h"

/**
 * @def MAX_GHOSTS
 * @brief It's the maximum quantity of ghosts in the level
 */
#define MAX_GHOSTS 4

/**
 * @def GHOST_SPRITE_SHEET
 * @brief Ghost sprite sheet name
 */
#define GHOST_SPRITE_SHEET "ghosts.png"

/**
 * @def GHOST_NORMAL_SPRITE
 * @brief Ghost normal sprite
 */
#define GHOST_NORMAL_LEFT_SPRITE  0

/**
 * @def GHOST_SCARED_SPRITE
 * @brief Ghost scared sprite
 */
#define GHOST_SCARED_LEFT_SPRITE 1

/**
 * @def GHOST_SCARED_SPRITE
 * @brief Ghost scared sprite
 */
#define GHOST_SCARED_RIGHT_SPRITE 2

/**
 * @def GHOST_NORMAL_SPRITE
 * @brief Ghost normal sprite
 */
#define GHOST_NORMAL_RIGHT_SPRITE  3

/**
 * @def GHOST_DEATH_SOUND_FILE
 * @brief Ghost death sound file
 */
#define GHOST_DEATH_SOUND_FILE "deathd.wav"

/**
 * @typedef STRUCT_GHOST
 * @brief Representation of the ghost (the enemies of the game)
 */
typedef struct STRUCT_ENTITY STRUCT_GHOST;

/**
 * @var gastGhost
 * @brief Ghosts enemies
 */
extern STRUCT_GHOST gastGhost[MAX_GHOSTS];

/**
 * @var gpstGhostDeathSound
 * @brief It's the ghost death sound
 */
extern Mix_Chunk* gpstGhostDeathSound;

#endif
