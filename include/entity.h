/**
 * @file entity.h
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

#ifndef _ENTITY_H_
#define _ENTITY_H_

#include "sprite.h"

/**
 * @struct STRUCT_ENTITY
 * @brief Structure that represents an entity
 */
typedef struct STRUCT_ENTITY {
  int iX;                              /**< Current col                            */
  int iY;                              /**< Current row                            */
  int iInitialX;                       /**< Initial col                            */
  int iInitialY;                       /**< Initial row                            */
  PSTRUCT_SPRITE_SHEET pstSpriteSheet; /**< Sprite sheet of the entity             */
  char chLetter;                       /**< Representation of the entity in gszMap */
  char chOldXY;                        /**< Old character in gszMap                */
  int iLives;                          /**< Quantity of the entity's lives         */
  int iMovementDirection;              /**< Move direction of the entity           */
} STRUCT_ENTITY, *PSTRUCT_ENTITY;

#endif
