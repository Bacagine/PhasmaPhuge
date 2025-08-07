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

#include "map.h"

char gszMap[MAP_ROW][MAP_COL];
boolean gbHeroEndMap = FALSE;
boolean gbGhostEndMap = FALSE;
int giTotalGameScore = 0;
int giCurrentLevelScore = 0;
int giTotalCurrentLevelScore = 0;
boolean gbShowPowerMessage = TRUE;
int giPowersCollected = 0;
Mix_Chunk* gpstPowerUpSound = NULL;
Mix_Chunk* gpstLevelUpSound = NULL;
Mix_Chunk* gpstGameWinSound = NULL;
STRUCT_PLAYER gstPlayer;
PSTRUCT_SPRITE_SHEET gpstHeartSpriteSheet;
Mix_Chunk* gpstHeroDeathSound;
STRUCT_GHOST gastGhost[MAX_GHOSTS];
Mix_Chunk* gpstGhostDeathSound;

void vSetCoordinates(int iX, int iY) {
  if ( gbHeroEndMap ) {
    iX = ( iX > MAP_ROW-1 ? 0 : MAP_ROW-1 );
    gbHeroEndMap = FALSE;
  }
  else if ( gszMap[iY][iX] == ' ' && (iX+1 == MAP_ROW || iX == 0) ) gbHeroEndMap = TRUE;
  else if ( iX < 0 || iX > MAP_ROW-1 || iY < 0 || iY > MAP_COL-1 ) {
    gbHeroEndMap = FALSE;
    return;
  }
  else if ( gszMap[iY][iX] == 'R' ||
    gszMap[iY][iX] == 'G' ||
    gszMap[iY][iX] == 'B' ||
    gszMap[iY][iX] == 'A' ) {
    if ( giPowersCollected > 0 ) {
      int iIndex = -1;
      switch( gszMap[iY][iX] ) {
        case 'R': iIndex = 0; break;
        case 'G': iIndex = 1; break;
        case 'B': iIndex = 2; break;
        case 'A': iIndex = 3; break;
        default: break;
      }
      gszMap[gastGhost[iIndex].iY][gastGhost[iIndex].iX] = gastGhost[iIndex].chOldXY;
      gastGhost[iIndex].iX = -1;
      gastGhost[iIndex].iY = -1;
      if ( giPowersCollected > 0 ) giPowersCollected--;
      Mix_PlayChannel(-1, gpstGhostDeathSound, 0);
    }
    else {
      gstPlayer.iLives--;
      Mix_PlayChannel(-1, gpstHeroDeathSound, 0);
      if ( gstPlayer.iLives == 0 ) {
        gbGameOver = TRUE;
        return;
      }
      else {
        iX = gstPlayer.iInitialX;
        iY = gstPlayer.iInitialY;
        gszMap[gstPlayer.iY][gstPlayer.iX] = ' ';
        gstPlayer.iMovementDirection = NONE_MOVEMENT;
      }
    }
    }
    else if ( gszMap[iY][iX] == '#' ) {
      return;
    }
    if ( gszMap[iY][iX] == '.' ) {
      giCurrentLevelScore += 10;
    }
    else if ( gszMap[iY][iX] == 'O' ) {
      giCurrentLevelScore += 100;
      giPowersCollected++;
      Mix_PlayChannel(-1, gpstPowerUpSound, 0);
    }
    gstPlayer.iX = iX;
    gstPlayer.iY = iY;
    if ( gszMap[iY][iX] == 'O' && gbShowPowerMessage ) {
      vMessageBox("Wow, would you like to kill a ghost?", "Press any key to continue.");
      gbShowPowerMessage = FALSE;
    }
}

void vUpdateMap(void) {
  gszMap[gstPlayer.iY][gstPlayer.iX] = 'H';
}

void vGetInitialPlayerPosition(void) {
  int iRow = 0;
  int iCol = 0;
  for ( iRow = 0; iRow < MAP_ROW; iRow++ ) {
    for ( iCol = 0; iCol < MAP_COL; iCol++ ) {
      if ( gszMap[iRow][iCol] == 'H' ) {
        gstPlayer.iY = iRow;
        gstPlayer.iX = iCol;
        gstPlayer.iInitialY = iRow;
        gstPlayer.iInitialX = iCol;
        return;
      }
    }
  }
}

void vGetInitialGhostsPosition(void) {
  int iRow = 0;
  int iCol = 0;
  int ii = 0;
  for ( ii = 0; ii < MAX_GHOSTS; ii++ ) {
    for ( iRow = 0; iRow < MAP_ROW; iRow++ ) {
      for ( iCol = 0; iCol < MAP_COL; iCol++ ) {
        if ( gszMap[iRow][iCol] == gastGhost[ii].chLetter ) {
          gastGhost[ii].iY = iRow;
          gastGhost[ii].iX = iCol;
          gastGhost[ii].iInitialY = iRow;
          gastGhost[ii].iInitialX = iCol;
        }
      }
    }
  }
}

void vGetTotalScoreLevel(void) {
  int iRow = 0;
  int iCol = 0;
  giTotalCurrentLevelScore = 0;
  for ( iRow = 0; iRow < MAP_ROW; iRow++ ) {
    for ( iCol = 0; iCol < MAP_COL; iCol++ ) {
      if ( gszMap[iRow][iCol] == '.' ) {
        giTotalCurrentLevelScore += 10;
      }
      else if ( gszMap[iRow][iCol] == 'O' ) {
        giTotalCurrentLevelScore += 100;
      }
    }
  }
}

