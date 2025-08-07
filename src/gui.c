/**
 * @file gui.h
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

#include "gui.h"

Uint32 giFrameStart = 0;
Uint32 giFrameTime = 0;
volatile boolean gbRun = TRUE;
SDL_Window* gpstWindow = NULL;
SDL_Renderer* gpstRenderer = NULL;
SDL_Event gunEvent;
int giWindowWidth = WINDOW_WIDTH;
int giWindowHeight = WINDOW_HEIGHT;
char gszFontDir[_MAX_PATH];

boolean bInitSDL(void) {
  if ( SDL_Init(SDL_INIT_EVERYTHING) ) {
    if ( DEBUG_FATAL ) vTrace("Error starting SDL module: [%s]", SDL_GetError());
    return FALSE;
  }
  gpstWindow = SDL_CreateWindow(
    "Dot Maze",
    SDL_WINDOWPOS_CENTERED,
    SDL_WINDOWPOS_CENTERED,
    giWindowWidth,
    giWindowHeight,
    SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE
  );
  if ( !gpstWindow ) {
    if ( DEBUG_FATAL ) vTrace("Error to creating window: [%s]", SDL_GetError());
    return FALSE;
  }
  gpstRenderer = SDL_CreateRenderer(
    gpstWindow,
    -1,
    SDL_RENDERER_ACCELERATED
  );
  if ( !gpstRenderer ) {
    if ( DEBUG_FATAL ) vTrace("Error to creating renderer: [%s]", SDL_GetError());
    SDL_DestroyWindow(gpstWindow);
    return FALSE;
  }

  if ( !(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) ) {
    if ( DEBUG_FATAL ) vTrace("Error starting IMG module: [%s]", IMG_GetError());
    SDL_DestroyRenderer(gpstRenderer);
    SDL_DestroyWindow(gpstWindow);
    return FALSE;
  }

  if ( TTF_Init() != 0 ) {
    if ( DEBUG_FATAL ) vTrace("F: Failure to start TTF module: [%s]!", TTF_GetError());
    return FALSE;
  }

  if ( Mix_OpenAudio(AUDIO_FREQUENCY, MIX_DEFAULT_FORMAT, 2, AUDIO_CHUNKSIZE) < 0 ) {
    if ( DEBUG_WARNING ) vTrace("W: Failure to start Mixer module: [%s]!", Mix_GetError());
  }

  return TRUE;
}

void vDestroySDL(void) {
  Mix_CloseAudio();
  TTF_Quit();
  IMG_Quit();
  SDL_DestroyRenderer(gpstRenderer);
  SDL_DestroyWindow(gpstWindow);
  SDL_Quit();
}

void vMessageBox(const char *kpszMsg, const char *kpszFooterMsg) {
  SDL_Surface* pstMsgBoxTextSurface = NULL;
  SDL_Texture* pstMsgBoxTextTexture = NULL;
  SDL_Rect stFooterTextRect = { 0 };
  TTF_Font* pstFont = NULL;
  TTF_Font* pstFooterFont = NULL;
  SDL_Surface* pstFooterTextSurface = NULL;
  SDL_Texture* pstFooterTextTexture = NULL;
  boolean bShowMsgBox = TRUE;
  boolean bRenderer = TRUE;
  char szFont[512] = "";
  int iFontSize = 15;
  int iExitMsgFontSize = 10;
  SDL_Color stBackgroundColor;
  SDL_Color stBorderColor;
  SDL_Color stTextColor;
  SDL_Rect stRect;
  SDL_Rect stTextRect;

  if ( bStrIsEmpty(kpszMsg) ) return;

  sprintf(szFont, "%s%c%s", gszFontDir, DIR_SEPARATOR, FONT_NAME);
  if ( (pstFont = TTF_OpenFont(szFont, iFontSize)) == NULL ) {
    if ( DEBUG_FATAL ) vTrace("F: Impossible to open the font [%s]: [%s]", szFont, TTF_GetError());
    return;
  }

  if ( (pstFooterFont = TTF_OpenFont(szFont, iExitMsgFontSize)) == NULL ) {
    if ( DEBUG_FATAL ) vTrace("F: Impossible to open the font [%s]: [%s]", szFont, TTF_GetError());
    TTF_CloseFont(pstFont);
    return;
  }

  stBackgroundColor.r = 255;
  stBackgroundColor.g = 255;
  stBackgroundColor.b = 255;
  stBackgroundColor.a = 255;

  stBorderColor.r = 0;
  stBorderColor.g = 0;
  stBorderColor.b = 0;
  stBorderColor.a = 255;

  stTextColor.r = 0;
  stTextColor.g = 0;
  stTextColor.b = 0;
  stTextColor.a = 255;

  stRect.h = 100;
  stRect.w = giWindowWidth / 2;
  stRect.x = (giWindowWidth - stRect.w) / 2;
  stRect.y = giWindowHeight / 4;

  pstMsgBoxTextSurface = TTF_RenderText_Blended(pstFont, kpszMsg, stTextColor);
  pstMsgBoxTextTexture = SDL_CreateTextureFromSurface(gpstRenderer, pstMsgBoxTextSurface);

  stTextRect.w = pstMsgBoxTextSurface->w;
  stTextRect.h = pstMsgBoxTextSurface->h;
  stTextRect.x = stRect.x + (stRect.w - stTextRect.w) / 2;
  stTextRect.y = stRect.y + (stRect.h - stTextRect.h) / 4;

  pstFooterTextSurface = TTF_RenderText_Blended(pstFooterFont, kpszFooterMsg, stTextColor);
  pstFooterTextTexture = SDL_CreateTextureFromSurface(gpstRenderer, pstFooterTextSurface);

  stFooterTextRect.w = pstFooterTextSurface->w;
  stFooterTextRect.h = pstFooterTextSurface->h;
  stFooterTextRect.x = stRect.x + (stRect.w - stFooterTextRect.w) / 2;
  stFooterTextRect.y = stRect.y + stRect.h - stFooterTextRect.h - 10;

  bRenderer = TRUE;
  while ( bShowMsgBox ) {
    while ( SDL_PollEvent(&gunEvent) ) {
      if ( gunEvent.type == SDL_KEYDOWN || gunEvent.type == SDL_QUIT ) {
        bShowMsgBox = FALSE;
        bRenderer = FALSE;
        if ( gunEvent.type == SDL_QUIT ) gbRun = FALSE;
        break;
      }
    }

    if ( bRenderer ) {
      SDL_SetRenderDrawColor(gpstRenderer, stBackgroundColor.r, stBackgroundColor.g, stBackgroundColor.b, stBackgroundColor.a);
      SDL_RenderFillRect(gpstRenderer, &stRect);
      SDL_SetRenderDrawColor(
        gpstRenderer,
        stBorderColor.r,
        stBorderColor.g,
        stBorderColor.b,
        stBorderColor.a
      );
      SDL_RenderDrawRect(gpstRenderer, &stRect);
      SDL_RenderCopy(gpstRenderer, pstMsgBoxTextTexture, NULL, &stTextRect);
      SDL_RenderCopy(gpstRenderer, pstFooterTextTexture, NULL, &stFooterTextRect);
      SDL_RenderPresent(gpstRenderer);
      if ( DEBUG_INFO ) {
        vTrace("vMessageBox - %s", kpszMsg);
        vTrace("vMessageBox - %s", kpszFooterMsg);
      }
      bRenderer = FALSE;
    }
  }

  SDL_FreeSurface(pstMsgBoxTextSurface);
  SDL_DestroyTexture(pstMsgBoxTextTexture);
  SDL_FreeSurface(pstFooterTextSurface);
  SDL_DestroyTexture(pstFooterTextTexture);
  TTF_CloseFont(pstFooterFont);
  TTF_CloseFont(pstFont);
}
