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

#include "sprite.h"

PSTRUCT_SPRITE_SHEET pstLoadSpriteSheet(
  SDL_Renderer *pstRenderer,
  const char *kpszFile,
  int iWidth,
  int iHeight,
  int iTotalSprites,
  int iCols) {
  PSTRUCT_SPRITE_SHEET pstSpriteSheet = NULL;
  int ii = 0;

  pstSpriteSheet = (PSTRUCT_SPRITE_SHEET) calloc(1, sizeof(STRUCT_SPRITE_SHEET));
  if ( !pstSpriteSheet ) {
    vTrace("Error allocating memory to spritesheet");
    return NULL;
  }

  pstSpriteSheet->pstTextures = IMG_LoadTexture(pstRenderer, kpszFile);
  if ( !pstSpriteSheet->pstTextures ) {
    vTrace("Error loading the imagem %s: %s", kpszFile, IMG_GetError());
    free(pstSpriteSheet);
    return NULL;
  }

  pstSpriteSheet->pstRects = (SDL_Rect *) calloc(1, sizeof(SDL_Rect) * (long unsigned int) iTotalSprites);
  if ( !pstSpriteSheet->pstRects ) {
    vTrace("Error allocating memory to rectangles");
    SDL_DestroyTexture(pstSpriteSheet->pstTextures);
    free(pstSpriteSheet);
    return NULL;
  }

  pstSpriteSheet->iCtSprites = iTotalSprites;

  for ( ii = 0; ii < iTotalSprites; ii++ ) {
    int iCol = ii % iCols;
    int iRow  = ii / iCols;
    pstSpriteSheet->pstRects[ii].x = iCol * iWidth;
    pstSpriteSheet->pstRects[ii].y = iRow * iHeight;
    pstSpriteSheet->pstRects[ii].w = iWidth;
    pstSpriteSheet->pstRects[ii].h = iHeight;
  }

  return pstSpriteSheet;
}

void vFreeSpriteSheet(PSTRUCT_SPRITE_SHEET pstSpriteSheet) {
  if ( pstSpriteSheet ) {
    if ( pstSpriteSheet->pstTextures ) {
      SDL_DestroyTexture(pstSpriteSheet->pstTextures);
    }
    if ( pstSpriteSheet->pstRects ) {
      free(pstSpriteSheet->pstRects);
      pstSpriteSheet->pstRects = NULL;
    }
    free(pstSpriteSheet);
    pstSpriteSheet = NULL;
  }
}
