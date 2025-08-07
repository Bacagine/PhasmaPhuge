/**
 * @file player.h
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

#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "entity.h"
#include "audio.h"

/**
 * @def HERO_SPRITE_SHEET
 * @brief Hero sprite sheet name
 */
#define HERO_SPRITE_SHEET "hero.png"

/**
 * @def
 * @brief Hero life image
 */
#define HEART_SPRITE_SHEET "heart.png"

/**
 * @def HERO_DOWN_SPRITE
 * @brief Hero move down sprite
 */
#define HERO_DOWN_SPRITE  0

/**
 * @def HERO_LEFT_SPRITE
 * @brief Hero move left sprite
 */
#define HERO_LEFT_SPRITE  1

/**
 * @def HERO_UP_SPRITE
 * @brief Hero move up sprite
 */
#define HERO_UP_SPRITE    2

/**
 * @def HERO_RIGHT_SPRITE
 * @brief Hero move right sprite
 */
#define HERO_RIGHT_SPRITE 3

/**
 * @def HERO_LIVES
 * @brief Hero's lives
 */
#define HERO_LIVES 3

/**
 * @def HERO_DEATH_SOUND_FILE
 * @brief Hero death sound file
 */
#define HERO_DEATH_SOUND_FILE "death.wav"

/**
 * @typedef STRUCT_PLAYER
 * @brief Representation of the player
 */
typedef struct STRUCT_ENTITY STRUCT_PLAYER;

/**
 * @var gstPlayer
 * @brief Player
 */
extern STRUCT_PLAYER gstPlayer;

/**
 * @var gpstHeartSpriteSheet
 * @brief It's the heart sprite sheet
 */
extern PSTRUCT_SPRITE_SHEET gpstHeartSpriteSheet;

/**
 * @var gpstHeroDeathSound
 * @brief It's the hero death sound
 */
extern Mix_Chunk* gpstHeroDeathSound;

#endif
