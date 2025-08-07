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

#ifndef _GUI_H_
#define _GUI_H_

#include <SDL2/SDL_image.h>
#include "util.h"
#include "trace.h"
#include "audio.h"
#include "hud.h"

/**
 * @def WINDOW_WIDTH
 * @brief Default window width
 */
#define WINDOW_WIDTH  625
/**
 * @def WINDOW_HEIGHT
 * @brief Default window height
 */
#define WINDOW_HEIGHT 625

/**
 * @def FPS
 * @brief Frame Per Second
 */
#define FPS 2

/**
 * @def FRAME_DELAY
 * @brief Frame delay based in FPS define
 */
#define FRAME_DELAY (1000 / FPS)

/**
 * @def FONT_NAME
 * @brief It's the name of ttf font used in the game
 */
#define FONT_NAME "DroidSans.ttf"

/**
 * @brief Start up SDL module
 *
 * @return TRUE load with success
 * @return FALSE SDL load error
 */
boolean bInitSDL(void);

/**
 * @brief Clean up the SDL module
 */
void vDestroySDL(void);

/**
 * @var giFrameStart
 * @brief It's the start frame of main loop
 */
extern Uint32 giFrameStart;

/**
 * @var giFrameTime
 * @brief It's the frame time between the start frame and the end of the game loop
 */
extern Uint32 giFrameTime;

/**
 * @var gbRun
 * @brief Used to maintain the main loop running
 */
extern volatile boolean gbRun;

/**
 * @var gpstWindow
 * @brief SDL window global pointer
 */
extern SDL_Window* gpstWindow;

/**
 * @var gpstRenderer
 * @brief SDL renderer global pointer
 */
extern SDL_Renderer* gpstRenderer;

/**
 * @var gunEvent
 * @brief SDL event global variable
 */
extern SDL_Event gunEvent;

/**
 * @var giWindowWidth
 * @brief Current window width
 */
extern int giWindowWidth;

/**
 * @var giWindowHeight
 * @brief Current window height
 */
extern int giWindowHeight;

/**
 * @brief ...
 *
 */
extern char gszFontDir[_MAX_PATH];

#endif
