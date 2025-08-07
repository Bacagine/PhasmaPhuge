/**
 * @file util.h
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

#ifndef _UTIL_H_
#define _UTIL_H_

#include <stdio.h>
#include <ctype.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "trace.h"

/**
 * @def _MAX_PATH
 * @brief Max path length
 */
#ifndef _MAX_PATH
  #define _MAX_PATH 256
#endif

/**
 * @def DIR_SEPARATOR
 * @brief Directory slash separator
 */
#ifdef _WIN32
  #define DIR_SEPARATOR '\\'
#else
  #define DIR_SEPARATOR '/'
#endif

/**
 * @enum boolean
 * @brief Boolean representation for C ANSI
 */
typedef enum boolean { FALSE, TRUE } boolean;

/**
 * @brief Check if string is empty
 *
 * @param kpszString String
 * @return TRUE if string is empty
 * @return FALSE if string has content
 */
boolean bStrIsEmpty(const char* kpszString);

/**
 * @brief Show GUI message box
 *
 * @param kpszMsg Message
 */
void vMessageBox(const char* kpszMsg, const char* kpszFooterMsg);

#endif
