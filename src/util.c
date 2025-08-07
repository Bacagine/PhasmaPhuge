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

#include "util.h"

boolean bStrIsEmpty(const char *kpszString) {
  if ( kpszString == NULL ) {
    return TRUE;
  }
  while ( *kpszString ) {
    if ( !isspace((unsigned char) *kpszString) ) {
      return FALSE;
    }
    kpszString++;
  }
  return TRUE;
}

