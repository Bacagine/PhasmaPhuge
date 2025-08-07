/**
 * @file game.c
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

#include "game.h"

ENUM_STATUS geStatus = STATUS_IDLE;
int giLevel = 1;
boolean gbGameOver = FALSE;
boolean gbTimeOut = FALSE;
const int gkaiLevelsTime[] = {
  180,
  180,
  180,
  180,
  180,
};
int giCurrentLevelTime = gkaiLevelsTime[0];
Mix_Music* gpstMusic = NULL;

/**
 * @brief Move the hero in the map
 */
static void vHeroMove(void);

/**
 * @brief Move the ghosts in the map
 */
static void vGhostsMove(void);

/**
 * @var gpaMovements
 * @brief Movements array variable
 */
static PFNMOVEMENTS gpaMovements[] = {
  vUp,
  vLeft,
  vDown,
  vRight
};

boolean bInitGame(void) {
  char szMusicPath[512] = "";
  char szSoundPath[512] = "";

  memset(szMusicPath, 0x00, sizeof(szMusicPath));
  memset(szSoundPath, 0x00, sizeof(szSoundPath));

  sprintf(szMusicPath, "%s%cmusic%c%s", gstCmdLine.szAudioDir, DIR_SEPARATOR, DIR_SEPARATOR, GAME_MUSIC_FILE);
  gpstMusic = Mix_LoadMUS(szMusicPath);
  if ( !gpstMusic ) {
    if ( DEBUG_WARNING ) vTrace("W: Failure in the MixLoadMUS: [%s]!", Mix_GetError());
  }

  sprintf(szSoundPath, "%s%csfx%c%s", gstCmdLine.szAudioDir, DIR_SEPARATOR, DIR_SEPARATOR, POWER_UP_SOUND_FILE);
  gpstPowerUpSound = Mix_LoadWAV(szSoundPath);
  if ( !gpstPowerUpSound ) {
    if ( DEBUG_WARNING ) vTrace("W: Failure in the MixLoadWAV: [%s]!", Mix_GetError());
  }

  memset(szSoundPath, 0x00, sizeof(szSoundPath));
  sprintf(szSoundPath, "%s%csfx%c%s", gstCmdLine.szAudioDir, DIR_SEPARATOR, DIR_SEPARATOR, LEVEL_UP_SOUND_FILE);
  gpstLevelUpSound = Mix_LoadWAV(szSoundPath);
  if ( !gpstLevelUpSound ) {
    if ( DEBUG_WARNING ) vTrace("W: Failure in the MixLoadWAV: [%s]!", Mix_GetError());
  }

  memset(szSoundPath, 0x00, sizeof(szSoundPath));
  sprintf(szSoundPath, "%s%csfx%c%s", gstCmdLine.szAudioDir, DIR_SEPARATOR, DIR_SEPARATOR, GAME_WIN_SOUND_FILE);
  gpstGameWinSound = Mix_LoadWAV(szSoundPath);
  if ( !gpstGameWinSound ) {
    if ( DEBUG_WARNING ) vTrace("W: Failure in the MixLoadWAV: [%s]!", Mix_GetError());
  }

  memset(szSoundPath, 0x00, sizeof(szSoundPath));
  sprintf(szSoundPath, "%s%csfx%c%s", gstCmdLine.szAudioDir, DIR_SEPARATOR, DIR_SEPARATOR, HERO_DEATH_SOUND_FILE);
  gpstHeroDeathSound = Mix_LoadWAV(szSoundPath);
  if ( !gpstHeroDeathSound ) {
    if ( DEBUG_WARNING ) vTrace("W: Failure in the MixLoadWAV: [%s]!", Mix_GetError());
  }

  memset(szSoundPath, 0x00, sizeof(szSoundPath));
  sprintf(szSoundPath, "%s%csfx%c%s", gstCmdLine.szAudioDir, DIR_SEPARATOR, DIR_SEPARATOR, GHOST_DEATH_SOUND_FILE);
  gpstGhostDeathSound = Mix_LoadWAV(szSoundPath);
  if ( !gpstGhostDeathSound ) {
    if ( DEBUG_WARNING ) vTrace("W: Failure in the MixLoadWAV: [%s]!", Mix_GetError());
  }

  memset(szSoundPath, 0x00, sizeof(szSoundPath));
  sprintf(szSoundPath, "%s%csfx%c%s", gstCmdLine.szAudioDir, DIR_SEPARATOR, DIR_SEPARATOR, GAME_OVER_SOUND_FILE);
  gpstGameOverSound = Mix_LoadWAV(szSoundPath);
  if ( !gpstGameOverSound ) {
    if ( DEBUG_WARNING ) vTrace("W: Failure in the MixLoadWAV: [%s]!", Mix_GetError());
  }

  return TRUE;
}

boolean bLoadSprites(void) {
  int ii = 0;
  char achLetter[MAX_GHOSTS] = { 'R', 'G', 'B', 'A' };
  char szHeroSpriteSheetPath[_MAX_PATH] = "";
  char szGhostSpriteSheetPath[_MAX_PATH] = "";
  char szHeartSpriteSheetPath[_MAX_PATH] = "";
  memset(szHeroSpriteSheetPath, 0x00, sizeof(szHeroSpriteSheetPath));
  memset(szGhostSpriteSheetPath, 0x00, sizeof(szGhostSpriteSheetPath));
  memset(szHeartSpriteSheetPath, 0x00, sizeof(szHeartSpriteSheetPath));
  sprintf(szHeroSpriteSheetPath, "%s%c%s", gstCmdLine.szImgDir, DIR_SEPARATOR, HERO_SPRITE_SHEET);
  gstPlayer.pstSpriteSheet = pstLoadSpriteSheet(gpstRenderer, szHeroSpriteSheetPath, 48, 48, 16, 4);
  gstPlayer.iLives = HERO_LIVES;
  gstPlayer.iMovementDirection = NONE_MOVEMENT;
  sprintf(szHeartSpriteSheetPath, "%s%c%s", gstCmdLine.szImgDir, DIR_SEPARATOR, HEART_SPRITE_SHEET);
  gpstHeartSpriteSheet = pstLoadSpriteSheet(gpstRenderer, szHeartSpriteSheetPath, 48, 48, 1, 1);
  sprintf(szGhostSpriteSheetPath, "%s%c%s", gstCmdLine.szImgDir, DIR_SEPARATOR, GHOST_SPRITE_SHEET);
  for ( ii = 0; ii < MAX_GHOSTS; ii++ ) {
    gastGhost[ii].pstSpriteSheet = pstLoadSpriteSheet(gpstRenderer, szGhostSpriteSheetPath, 20, 20, 4, 2);
    gastGhost[ii].chLetter = achLetter[ii];
    gastGhost[ii].chOldXY = ' ';
    gastGhost[ii].iMovementDirection = LEFT_MOVEMENT;
  }
  return TRUE;
}

void vDestroySprites(void) {
  int ii = 0;
  vFreeSpriteSheet(gstPlayer.pstSpriteSheet);
  vFreeSpriteSheet(gpstHeartSpriteSheet);
  for ( ii = 0; ii < MAX_GHOSTS; ii++ ) {
    vFreeSpriteSheet(gastGhost[ii].pstSpriteSheet);
  }
}

void vDestroyGame(void) {
  vDestroySprites();
  if ( gpstGameOverSound ) {
    Mix_FreeChunk(gpstGameOverSound);
    gpstGameOverSound = NULL;
  }
  if ( gpstGhostDeathSound ) {
    Mix_FreeChunk(gpstGhostDeathSound);
    gpstGhostDeathSound = NULL;
  }
  if ( gpstHeroDeathSound ) {
    Mix_FreeChunk(gpstHeroDeathSound);
    gpstHeroDeathSound = NULL;
  }
  if ( gpstGameWinSound ) {
    Mix_FreeChunk(gpstGameWinSound);
    gpstGameWinSound = NULL;
  }
  if ( gpstLevelUpSound ) {
    Mix_FreeChunk(gpstLevelUpSound);
    gpstLevelUpSound = NULL;
  }
  if ( gpstPowerUpSound ) {
    Mix_FreeChunk(gpstPowerUpSound);
    gpstPowerUpSound = NULL;
  }
  if ( gpstMusic ) {
    Mix_FreeMusic(gpstMusic);
    gpstMusic = NULL;
  }
}

boolean bLoadLevel(const char *kpszMapFile) {
  FILE *fpMap = NULL;
  char szFileLine[64] = "";
  int iRow = 0;
  int iLives = gstPlayer.iLives > 0 ? gstPlayer.iLives : HERO_LIVES;

  memset(szFileLine, 0x00, sizeof(szFileLine));

  if ( DEBUG_INFO ) vTrace("bLoadLevel - begin");

  if ( !bLoadSprites() ) {
    if ( DEBUG_FATAL ) vTrace("bLoadLevel - F: Fatal error in bLoadSprites");
    return FALSE;
  }
  gstPlayer.iLives = iLives;

  if ( (fpMap = fopen(kpszMapFile, "r")) == NULL ) {
    vTrace("F: Impossible to open the file [%s]: %s", kpszMapFile, strerror(errno));
    return FALSE;
  }
  while ( fgets(szFileLine, sizeof(szFileLine), fpMap) ) {
    szFileLine[strcspn(szFileLine, "\r\n")] = '\0';
    sprintf(gszMap[iRow], "%s", szFileLine);
    iRow++;
  }
  fclose(fpMap);
  fpMap = NULL;
  vGetInitialPlayerPosition();
  vGetInitialGhostsPosition();
  vGetTotalScoreLevel();
  if ( DEBUG_DETAILS ) {
    vTrace("Total Level Score: [%d]", giTotalCurrentLevelScore);
  }
  return TRUE;
}

void vMainMenu(void) {
  char szLevel[512] = "";
  memset(szLevel, 0x00, sizeof(szLevel));
  if ( DEBUG_INFO ) vTrace("vMainMenu - begin");
  gstPlayer.iMovementDirection = NONE_MOVEMENT;
  gbGameOver = FALSE;
  /* TODO: Criar o menu aqui */
  Mix_PlayMusic(gpstMusic, -1);
  sprintf(szLevel, "%s%c%d.txt", gstCmdLine.szLevelDir, DIR_SEPARATOR, giLevel);
  if ( !bLoadLevel(szLevel) ) {
    vTrace("Error loading the level [%s]", szLevel);
    return;
  }
  geStatus = STATUS_RUN;
  if ( DEBUG_INFO ) vTrace("vMainMenu - end");
  return;
}



void vHandleEvents(void) {
  if ( giCurrentLevelTime == 0 ) return;
  while ( SDL_PollEvent(&gunEvent) ) {
    switch ( gunEvent.type ) {
      case SDL_QUIT: {
        gbRun = FALSE;
        break;
      }
      case SDL_KEYDOWN: {
        switch ( gunEvent.key.keysym.sym ) {
          case SDLK_UP:
          case SDLK_w: {
            gstPlayer.iMovementDirection = UP_MOVEMENT;
            geStatus = STATUS_RUN;
            break;
          }
          case SDLK_LEFT:
          case SDLK_a: {
            gstPlayer.iMovementDirection = LEFT_MOVEMENT;
            geStatus = STATUS_RUN;
            break;
          }
          case SDLK_DOWN:
          case SDLK_s: {
            gstPlayer.iMovementDirection = DOWN_MOVEMENT;
            geStatus = STATUS_RUN;
            break;
          }
          case SDLK_RIGHT:
          case SDLK_d: {
            gstPlayer.iMovementDirection = RIGHT_MOVENT;
            geStatus = STATUS_RUN;
            break;
          }
          case SDLK_SPACE: {
            geStatus = (geStatus == STATUS_IDLE ? STATUS_IDLE : (geStatus == STATUS_PAUSE ? STATUS_RUN : STATUS_PAUSE));
            break;
          }
          default: break;
        }
        break;
      }
          case SDL_WINDOWEVENT: {
            if ( gunEvent.window.event == SDL_WINDOWEVENT_RESIZED ) {
              int iNewWidth = gunEvent.window.data1;
              int iNewHeight = gunEvent.window.data2;

              if ( iNewWidth < WINDOW_WIDTH || iNewHeight < WINDOW_HEIGHT ) {
                SDL_SetWindowSize(gpstWindow, giWindowWidth, giWindowHeight);
              }
              else {
                giWindowWidth = iNewWidth;
                giWindowHeight = iNewHeight;
              }
            }
            break;
          }
          default: break;
    }
  }
}

void vDrawMap(void) {
  int iRow = 0;
  int iCol = 0;
  int iCellWidth = giWindowWidth / MAP_COL;
  int iCellHeight = giWindowHeight / MAP_ROW;
  SDL_SetRenderDrawColor(gpstRenderer, 0, 0, 0, 0);
  SDL_RenderClear(gpstRenderer);
  for ( iRow = 0; iRow < MAP_ROW; iRow++ ) {
    for ( iCol = 0; iCol < MAP_COL; iCol++ ) {
      SDL_Rect stRect;
      stRect.x = iCol * iCellWidth;
      stRect.y = iRow * iCellHeight;
      stRect.w = iCellWidth;
      stRect.h = iCellHeight;

      if ( gszMap[iRow][iCol] == '#' ) {
        SDL_SetRenderDrawColor(gpstRenderer, 0, 0, 255, 255);
        SDL_RenderFillRect(gpstRenderer, &stRect);
      }
      else if ( gszMap[iRow][iCol] == '.' ) {
        int iCenterX = stRect.x + stRect.w / 2;
        int iCenterY = stRect.y + stRect.h / 2;
        int iRadius = (iCellWidth < iCellHeight ? iCellWidth : iCellHeight) / 5;
        int iY = 0;
        int iX = 0;
        SDL_SetRenderDrawColor(gpstRenderer, 255, 255, 255, 255);
        for ( iY = -iRadius; iY <= iRadius; iY++ ) {
          for ( iX = -iRadius; iX <= iRadius; iX++ ) {
            if ( iX * iX + iY * iY <= iRadius * iRadius ) {
              SDL_RenderDrawPoint(gpstRenderer, iCenterX + iX, iCenterY + iY);
            }
          }
        }
      }
      else if ( gszMap[iRow][iCol] == 'O' ) {
        int iCenterX = stRect.x + stRect.w / 2;
        int iCenterY = stRect.y + stRect.h / 2;
        int iRadius = (iCellWidth < iCellHeight ? iCellWidth : iCellHeight) / 3;
        int iY = 0;
        int iX = 0;
        SDL_SetRenderDrawColor(gpstRenderer, 255, 255, 255, 255);
        for ( iY = -iRadius; iY <= iRadius; iY++ ) {
          for ( iX = -iRadius; iX <= iRadius; iX++ ) {
            if ( iX * iX + iY * iY <= iRadius * iRadius ) {
              SDL_RenderDrawPoint(gpstRenderer, iCenterX + iX, iCenterY + iY);
            }
          }
        }
      }
      else if ( gszMap[iRow][iCol] == 'H' ) {
        int iSpriteIndex = -1;
        switch ( gstPlayer.iMovementDirection ) {
          case UP_MOVEMENT  : iSpriteIndex = HERO_UP_SPRITE   ; break;
          case LEFT_MOVEMENT: iSpriteIndex = HERO_LEFT_SPRITE ; break;
          case RIGHT_MOVENT : iSpriteIndex = HERO_RIGHT_SPRITE; break;
          case DOWN_MOVEMENT:
          case NONE_MOVEMENT:
          default           : iSpriteIndex = HERO_DOWN_SPRITE; break;
        }
        SDL_RenderCopy(gpstRenderer, gstPlayer.pstSpriteSheet->pstTextures, &gstPlayer.pstSpriteSheet->pstRects[iSpriteIndex], &stRect);
      }
      else if ( gszMap[iRow][iCol] == 'R' ) {
        int iSpriteIndex = giPowersCollected > 0 ? GHOST_SCARED_LEFT_SPRITE : GHOST_NORMAL_LEFT_SPRITE;
        if ( gastGhost[0].iMovementDirection != LEFT_MOVEMENT ){
          iSpriteIndex = giPowersCollected > 0 ? GHOST_SCARED_RIGHT_SPRITE : GHOST_NORMAL_RIGHT_SPRITE;
        }
        SDL_RenderCopy(gpstRenderer, gastGhost[0].pstSpriteSheet->pstTextures, &gastGhost[0].pstSpriteSheet->pstRects[iSpriteIndex], &stRect);
      }
      else if ( gszMap[iRow][iCol] == 'G' ) {
        int iSpriteIndex = giPowersCollected > 0 ? GHOST_SCARED_LEFT_SPRITE : GHOST_NORMAL_LEFT_SPRITE;
        if ( gastGhost[1].iMovementDirection == RIGHT_MOVENT ){
          iSpriteIndex = giPowersCollected > 0 ? GHOST_SCARED_RIGHT_SPRITE : GHOST_NORMAL_RIGHT_SPRITE;
        }
        SDL_RenderCopy(gpstRenderer, gastGhost[1].pstSpriteSheet->pstTextures, &gastGhost[1].pstSpriteSheet->pstRects[iSpriteIndex], &stRect);
      }
      else if ( gszMap[iRow][iCol] == 'B' ) {
        int iSpriteIndex = giPowersCollected > 0 ? GHOST_SCARED_LEFT_SPRITE : GHOST_NORMAL_LEFT_SPRITE;
        if ( gastGhost[2].iMovementDirection == RIGHT_MOVENT ){
          iSpriteIndex = giPowersCollected > 0 ? GHOST_SCARED_RIGHT_SPRITE : GHOST_NORMAL_RIGHT_SPRITE;
        }
        SDL_RenderCopy(gpstRenderer, gastGhost[2].pstSpriteSheet->pstTextures, &gastGhost[2].pstSpriteSheet->pstRects[iSpriteIndex], &stRect);
      }
      else if ( gszMap[iRow][iCol] == 'A' ) {
        int iSpriteIndex = giPowersCollected > 0 ? GHOST_SCARED_LEFT_SPRITE : GHOST_NORMAL_LEFT_SPRITE;
        if ( gastGhost[3].iMovementDirection == RIGHT_MOVENT ){
          iSpriteIndex = giPowersCollected > 0 ? GHOST_SCARED_RIGHT_SPRITE : GHOST_NORMAL_RIGHT_SPRITE;
        }
        SDL_RenderCopy(gpstRenderer, gastGhost[3].pstSpriteSheet->pstTextures, &gastGhost[3].pstSpriteSheet->pstRects[iSpriteIndex], &stRect);
      }
      else {
        continue;
      }
    }
  }
}

void vDrawGameInfo(void) {
  STRUCT_HUD stGameInfoHUD;
  STRUCT_HUD stLiveHUD;
  STRUCT_HUD stClockHUD;
  TTF_Font* pstFont = NULL;

  memset(&stGameInfoHUD, 0x00, sizeof(stGameInfoHUD));
  memset(&stLiveHUD    , 0x00, sizeof(stLiveHUD    ));
  memset(&stClockHUD    , 0x00, sizeof(stClockHUD    ));

  stGameInfoHUD.iFontSize = 20;
  stGameInfoHUD.stTextColor.r = 255;
  stGameInfoHUD.stTextColor.g = 255;
  stGameInfoHUD.stTextColor.b = 255;
  stGameInfoHUD.stTextColor.a = 255;

  sprintf(stGameInfoHUD.szFont, "%s%c%s", gstCmdLine.szFontDir, DIR_SEPARATOR, FONT_NAME);
  if ( (pstFont = TTF_OpenFont(stGameInfoHUD.szFont, stGameInfoHUD.iFontSize)) == NULL ) {
    if ( DEBUG_FATAL ) vTrace("F: Impossible to open the font [%s]: [%s]", stGameInfoHUD.szFont, TTF_GetError());
    return;
  }

  sprintf(
    stGameInfoHUD.szText,
    "Level: %d/%d | Level Score: %d | Total Game Score: %d | Power: %d",
    giLevel, MAX_LEVEL, giCurrentLevelScore, giTotalGameScore, giPowersCollected
  );

  stGameInfoHUD.pstSurface = TTF_RenderText_Blended(pstFont, stGameInfoHUD.szText, stGameInfoHUD.stTextColor);
  stGameInfoHUD.pstTexture = SDL_CreateTextureFromSurface(gpstRenderer, stGameInfoHUD.pstSurface);
  stGameInfoHUD.stRect.h = stGameInfoHUD.pstSurface->h;
  stGameInfoHUD.stRect.w = stGameInfoHUD.pstSurface->w;
  stGameInfoHUD.stRect.x = 0;
  stGameInfoHUD.stRect.y = giWindowHeight - stGameInfoHUD.stRect.h - 10;
  SDL_RenderDrawRect(gpstRenderer, &stGameInfoHUD.stRect);
  SDL_RenderCopy(gpstRenderer, stGameInfoHUD.pstTexture, NULL, &stGameInfoHUD.stRect);

  SDL_FreeSurface(stGameInfoHUD.pstSurface);
  SDL_DestroyTexture(stGameInfoHUD.pstTexture);

  /* Show lives */
  if ( gpstHeartSpriteSheet->pstTextures ) {
    static const int kiPadding = 5;
    int ii = 0;

    sprintf(stLiveHUD.szFont, "%s", stGameInfoHUD.szFont);
    stLiveHUD.iFontSize = stGameInfoHUD.iFontSize;
    stLiveHUD.stTextColor = stGameInfoHUD.stTextColor;

    sprintf(stLiveHUD.szText, "Lives:");

    stLiveHUD.pstSurface = TTF_RenderText_Blended(pstFont, stLiveHUD.szText, stLiveHUD.stTextColor);
    stLiveHUD.pstTexture = SDL_CreateTextureFromSurface(gpstRenderer, stLiveHUD.pstSurface);

    stLiveHUD.stTextRect.h = stLiveHUD.pstSurface->h;
    stLiveHUD.stTextRect.w = stLiveHUD.pstSurface->w;
    stLiveHUD.stTextRect.x = 0;
    stLiveHUD.stTextRect.y = 0;

    SDL_RenderDrawRect(gpstRenderer, &stLiveHUD.stTextRect);
    SDL_RenderCopy(gpstRenderer, stLiveHUD.pstTexture, NULL, &stLiveHUD.stTextRect);

    stLiveHUD.stRect.w = 24;
    stLiveHUD.stRect.h = 24;
    stLiveHUD.stRect.y = 0;
    for ( ii = 0; ii < gstPlayer.iLives; ii++ ) {
      stLiveHUD.stRect.x = (stLiveHUD.stTextRect.w-30) + ((stLiveHUD.stRect.w + kiPadding) * (gstPlayer.iLives - ii));
      SDL_RenderCopy(gpstRenderer, gpstHeartSpriteSheet->pstTextures, NULL, &stLiveHUD.stRect);
    }
    SDL_FreeSurface(stLiveHUD.pstSurface);
    SDL_DestroyTexture(stLiveHUD.pstTexture);
  }

  /* Draw clock */
  {
    int iMinutes = giCurrentLevelTime / 60;
    int iSeconds = giCurrentLevelTime % 60;
    int iTextW = 0;
    int iTextH = 0;
    static const int kiPadding = 6;

    sprintf(stClockHUD.szFont, "%s", stGameInfoHUD.szFont);
    stClockHUD.iFontSize = stGameInfoHUD.iFontSize;

    sprintf(stClockHUD.szText, "%02d:%02d", iMinutes, iSeconds);

    stClockHUD.stTextColor.a = 255;

    stClockHUD.pstSurface = TTF_RenderText_Blended(pstFont, stClockHUD.szText, stClockHUD.stTextColor);
    stClockHUD.pstTexture = SDL_CreateTextureFromSurface(gpstRenderer, stClockHUD.pstSurface);

    iTextW = stClockHUD.pstSurface->w;
    iTextH = stClockHUD.pstSurface->h;

    stClockHUD.stRect.w = iTextW + kiPadding * 2;
    stClockHUD.stRect.h = iTextH + kiPadding * 2;
    stClockHUD.stRect.x = giWindowWidth - stClockHUD.stRect.w - 10;
    stClockHUD.stRect.y = 0;
    stClockHUD.stTextRect.w = iTextW;
    stClockHUD.stTextRect.h = iTextH;
    stClockHUD.stTextRect.x = stClockHUD.stRect.x + kiPadding;
    stClockHUD.stTextRect.y = stClockHUD.stRect.y + kiPadding;
    SDL_SetRenderDrawColor(gpstRenderer, 255, 255, 255, 255);
    SDL_RenderFillRect(gpstRenderer, &stClockHUD.stTextRect);

    SDL_SetRenderDrawColor(gpstRenderer, stClockHUD.stTextColor.r, stClockHUD.stTextColor.g, stClockHUD.stTextColor.b, stClockHUD.stTextColor.a);
    SDL_RenderDrawRect(gpstRenderer, &stClockHUD.stTextRect);

    SDL_RenderCopy(gpstRenderer, stClockHUD.pstTexture, NULL, &stClockHUD.stTextRect);

    SDL_FreeSurface(stClockHUD.pstSurface);
    SDL_DestroyTexture(stClockHUD.pstTexture);
  }

  SDL_RenderPresent(gpstRenderer);
  TTF_CloseFont(pstFont);
}

void vResetLevel(void) {
  giCurrentLevelScore = 0;
  giTotalCurrentLevelScore = 0;
  geStatus = STATUS_IDLE;
  giCurrentLevelTime = gkaiLevelsTime[giLevel-1];
  giPowersCollected = 0;
  vDestroySprites();
  gbTimeOut = FALSE;
}

void vResetGame(void) {
  giLevel = 1;
  giCurrentLevelScore = 0;
  giTotalCurrentLevelScore = 0;
  giTotalGameScore = 0;
  giPowersCollected = 0;
  geStatus = STATUS_IDLE;
  giCurrentLevelTime = gkaiLevelsTime[0];
  vDestroySprites();
  gbGameOver = FALSE;
  gbTimeOut = FALSE;
  memset(gszMap    , 0x00, sizeof(gszMap    ));
  memset(&gstPlayer, 0x00, sizeof(gstPlayer ));
  memset(gastGhost , 0x00, sizeof(gastGhost ));
}

void vLevelUp(void) {
  char szFooterMsg[512] = "";
  memset(szFooterMsg, 0x00, sizeof(szFooterMsg));
  giLevel++;
  sprintf(szFooterMsg, "Press any key to start level %d", giLevel);
  Mix_PauseMusic();
  Mix_PlayChannel(-1, gpstLevelUpSound, 0);
  vMessageBox("Level UP!", szFooterMsg);
  if ( DEBUG_DETAILS ) {
    vTrace("Score achieved at level [%d]: [%d]", giLevel, giCurrentLevelScore);
    vTrace("Total Game Score: [%d]", giTotalGameScore);
  }
  giCurrentLevelScore = 0;
  giTotalCurrentLevelScore = 0;
  giPowersCollected = 0;
  geStatus = STATUS_IDLE;
  giCurrentLevelTime = gkaiLevelsTime[giLevel-1];
  vDestroySprites();
}

void vGameOver(void) {
  vDrawGameInfo();
  Mix_HaltMusic();
  Mix_PlayChannel(-1, gpstGameOverSound, 0);
  vMessageBox("GAME OVER", "Press any key to restart.");
  vResetGame();
}

void vTimeOut(void) {
  if ( gstPlayer.iLives > 0 ) gstPlayer.iLives--;
  if ( gstPlayer.iLives == 0 ) {
    vGameOver();
  }
  else {
    vDrawGameInfo();
    Mix_HaltMusic();
    Mix_PlayChannel(-1, gpstGameOverSound, 0);
    vMessageBox("TIME OUT!", "Press any key to restart the level.");
    vResetLevel();
  }
}

void vYouWin(void) {
  Mix_PauseMusic();
  Mix_PlayChannel(-1, gpstGameWinSound, 0);
  vMessageBox("You Win =)", "Press any key to restart.");
  if ( DEBUG_DETAILS ) {
    vTrace("Score achieved at level [%d]: [%d]", giLevel, giCurrentLevelScore);
    vTrace("Total Game Score: [%d]", giTotalGameScore);
  }
  vResetGame();
}

boolean bLevelComplete(void) {
  return giCurrentLevelScore == giTotalCurrentLevelScore;
}

boolean bWinGame(void) {
  return giLevel == MAX_LEVEL;
}

void vUp(void) {
  gszMap[gstPlayer.iY][gstPlayer.iX] = ' ';
  vSetCoordinates(gstPlayer.iX, gstPlayer.iY-1);
  vUpdateMap();
}

void vLeft(void) {
  gszMap[gstPlayer.iY][gstPlayer.iX] = ' ';
  vSetCoordinates(gstPlayer.iX-1, gstPlayer.iY);
  vUpdateMap();
}

void vDown(void) {
  gszMap[gstPlayer.iY][gstPlayer.iX] = ' ';
  vSetCoordinates(gstPlayer.iX, gstPlayer.iY+1);
  vUpdateMap();
}

void vRight(void) {
  gszMap[gstPlayer.iY][gstPlayer.iX] = ' ';
  vSetCoordinates(gstPlayer.iX+1, gstPlayer.iY);
  vUpdateMap();
}

static void vHeroMove(void) {
  if ( gstPlayer.iMovementDirection != NONE_MOVEMENT ) {
    gpaMovements[gstPlayer.iMovementDirection]();
  }
}

static void vGhostsMove(void) {
  int ii = 0;
  if ( gstPlayer.iMovementDirection == NONE_MOVEMENT && giCurrentLevelScore == 0 ) return;
  for ( ii = 0; ii < MAX_GHOSTS; ii++ ) {
    int iX = 0;
    int iY = 0;
    int direction = 0;
    if ( gastGhost[ii].iX == -1 || gastGhost[ii].iY == -1 ) continue;
    do {
      int iStep = 1;
      direction = rand() % 4;
      iX = gastGhost[ii].iX;
      iY = gastGhost[ii].iY;

      switch ( direction ) {
        case UP_MOVEMENT  : iY -= iStep; break;
        case LEFT_MOVEMENT: iX -= iStep; break;
        case DOWN_MOVEMENT: iY += iStep; break;
        case RIGHT_MOVENT : iX += iStep; break;
        default           : break;
      }
      if ( gbGhostEndMap ) {
        iX = ( iX > MAP_ROW-1 ? 0 : MAP_ROW-1 );
        gbGhostEndMap = FALSE;
      }
      else if ( gszMap[iY][iX] == ' ' && (iX+1 == MAP_ROW || iX == 0) ) gbGhostEndMap = TRUE;
      else if ( iX < 0 || iX > MAP_ROW-1 || iY < 0 || iY > MAP_COL-1 ) {
        gbGhostEndMap = FALSE;
        continue;
      }
      break;
    } while ( TRUE );
    if ( gszMap[iY][iX] == 'R' || gszMap[iY][iX] == 'G' || gszMap[iY][iX] == 'B' || gszMap[iY][iX] == 'A' || gszMap[iY][iX] == '#' ) continue;
    if ( gszMap[iY][iX] == 'H' ) {
      if ( giPowersCollected == 0 ) {
        gstPlayer.iLives--;
        Mix_PlayChannel(-1, gpstHeroDeathSound, 0);
        if ( gstPlayer.iLives == 0 ) {
          gbGameOver = TRUE;
        }
        else {
          gszMap[gstPlayer.iY][gstPlayer.iX] = ' ';
          gstPlayer.iX = gstPlayer.iInitialX;
          gstPlayer.iY = gstPlayer.iInitialY;
          gstPlayer.iMovementDirection = NONE_MOVEMENT;
          gszMap[gstPlayer.iY][gstPlayer.iX] = 'H';
        }
      }
      else {
        gszMap[gastGhost[ii].iY][gastGhost[ii].iX] = gastGhost[ii].chOldXY;
        gastGhost[ii].iX = -1;
        gastGhost[ii].iY = -1;
        if ( giPowersCollected > 0 ) giPowersCollected--;
        Mix_PlayChannel(-1, gpstGhostDeathSound, 0);
        continue;
      }
    }
    gastGhost[ii].iMovementDirection = direction;
    gszMap[gastGhost[ii].iY][gastGhost[ii].iX] = gastGhost[ii].chOldXY;
    gastGhost[ii].chOldXY = gszMap[iY][iX];
    gszMap[iY][iX] = gastGhost[ii].chLetter;
    gastGhost[ii].iY = iY;
    gastGhost[ii].iX = iX;
  }
}

void vMove(void) {
  vHeroMove();
  if ( giCurrentLevelScore != giTotalCurrentLevelScore ) {
    vGhostsMove();
  }
}

void vUpdateScreen(void) {
  if ( giCurrentLevelTime == 0 ) gbTimeOut = TRUE;
  switch ( geStatus ) {
    case STATUS_IDLE: vMainMenu(); break;
    case STATUS_PAUSE: {
      Mix_PauseMusic();
      vMessageBox("PAUSE", "Press any key to continue.");
      Mix_PlayMusic(gpstMusic, -1);
      geStatus = STATUS_RUN;
      break;
    }
    case STATUS_RUN:
    default: {
      if ( !gbTimeOut ) {
        vMove();
        vDrawMap();
      }
      break;
    }
  }

  if ( !gbGameOver ) {
    if ( giCurrentLevelScore == giTotalCurrentLevelScore ) {
      giTotalGameScore += giCurrentLevelScore;
    }
  }

  vDrawGameInfo();

  if ( gbTimeOut ) {
    vTimeOut();
  }
  else if ( gbGameOver ) {
    vGameOver();
  }
  else {
    if ( bLevelComplete() ) {
      if ( bWinGame() ) {
        vYouWin();
      }
      else {
        vLevelUp();
      }
    }
  }
}
