/**
 * @file hud.h
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

#ifndef _HUD_H_
#define _HUD_H_

/**
 * @struct STRUCT_HUD
 * @brief Struct that represents a game HUD
 */
typedef struct STRUCT_HUD {
  SDL_Surface* pstSurface;
  SDL_Texture* pstTexture;
  SDL_Rect stRect;
  SDL_Rect stTextRect;
  char szFont[512];
  int iFontSize;
  SDL_Color stTextColor;
  char szText[2048];
} STRUCT_HUD, *PSTRUCT_HUD;

#endif
