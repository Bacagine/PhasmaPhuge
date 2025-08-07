/**
 * @file sprite.h
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

#ifndef _SPRITE_H_
#define _SPRITE_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "trace.h"

/**
 * @struct STRUCT_SPRITE_SHEET
 * @brief Struct that represents a sprite sheet
 */
typedef struct STRUCT_SPRITE_SHEET{
  SDL_Texture* pstTextures; /**< Sprite textures                */
  SDL_Rect* pstRects;       /**< Sprite rects                   */
  int iCtSprites;           /**< Quantity of sprites in the file */
} STRUCT_SPRITE_SHEET, *PSTRUCT_SPRITE_SHEET;

/**
 * @brief Load a sprite sheet
 *
 * @param pstRenderer Pointer to renderer
 * @param kpszFile The path of sprite sheet
 * @param iWidth Width of the sprite
 * @param iHeight Height of the sprite
 * @param iTotalSprites Total sprites in the sheet
 * @param iCols Total cols in the sprite sheet
 * @return Pointer to a sprite sheet
 */
PSTRUCT_SPRITE_SHEET pstLoadSpriteSheet(
  SDL_Renderer* pstRenderer,
  const char* kpszFile,
  int iWidth,
  int iHeight,
  int iTotalSprites,
  int iCols);

/**
 * @brief Free sprite sheet loaded with pstLoadSpriteSheet
 *
 * @param pstSpriteSheet sprite sheet to free
 */
void vFreeSpriteSheet(PSTRUCT_SPRITE_SHEET pstSpriteSheet);

#endif
