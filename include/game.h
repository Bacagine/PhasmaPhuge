/**
 * @file game.h
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

#ifndef _GAME_H_
#define _GAME_H_

/******************************************************************************
 *                                                                            *
 *                                  Includes                                  *
 *                                                                            *
 ******************************************************************************/
#include <getopt.h>
#include <libgen.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "util.h"
#include "trace.h"
#include "map.h"
#include "hud.h"
#include "gui.h"

/******************************************************************************
 *                                                                            *
 *                                   Defines                                   *
 *                                                                            *
 ******************************************************************************/

/**
 * @def VERSION
 * @brief The version of the software
 */
#define VERSION "1.0"

/**
 * @def MAX_SPRITES
 * @brief Max sprites for an entity
 */
#define MAX_SPRITES 5

/**
 * @def MAX_LEVEL
 * @brief Maximum levels of the game
 */
#define MAX_LEVEL 5

/**
 * @def GAME_MUSIC_FILE
 * @brief The music theme file of the game
 */
#define GAME_MUSIC_FILE "theme.mp3"

/**
 * @def POWER_UP_SOUND_FILE
 * @brief Power up sound file
 */
#define POWER_UP_SOUND_FILE "power_up_sound.wav"

/**
 * @def LEVEL_UP_SOUND_FILE
 * @brief Level up sound file
 */
#define LEVEL_UP_SOUND_FILE "newthingget.wav"

/**
 * @def GAME_WIN_SOUND_FILE
 * @brief You win sound file
 */
#define GAME_WIN_SOUND_FILE "sboe.wav"

/**
 * @def GAME_OVER_SOUND_FILE
 * @brief Game over sound file
 */
#define GAME_OVER_SOUND_FILE "Funeral March.wav"

/******************************************************************************
 *                                                                            *
 *                                 Command Line                               *
 *                                                                            *
 ******************************************************************************/

/**
 * @var gkpszProgramName
 * @brief Receives the program's name
 */
extern const char* gkpszProgramName;

/**
 * @struct STRUCT_COMMAND_LINE
 * @brief Structure that represents command line arguments
 */
typedef struct STRUCT_COMMAND_LINE {
  char szTrace[_MAX_PATH];    /**< Trace file path */
  char szDebugLevel[32];      /**< Debug level     */
  char szMap[_MAX_PATH];      /**< Map file path   */
  char szImgDir[_MAX_PATH];   /**< Images dir path */
  char szLevelDir[_MAX_PATH]; /**< Level dir path  */
  char szFontDir[_MAX_PATH];  /**< TTFs dir path   */
  char szAudioDir[_MAX_PATH]; /**< Audio dir path  */
} STRUCT_COMMAND_LINE, *PSTRUCT_COMMAND_LINE;

/**
 * @var gstCmdLine
 * @brief Global command line arguments
 */
extern STRUCT_COMMAND_LINE gstCmdLine;

/**
 * @var gkpszShortOptions
 * @brief Command line short options
 */
extern const char* gkpszShortOptions;

/**
 * @var astCmdOpt
 * @brief Array of the command line options
 */
extern const struct option astCmdOpt[];

/**
 * @var gkpaszCmdLineExampleArguments
 * @brief Array with command line example arguments
 */
extern const char* gkpaszCmdLineExampleArguments[];

/**
 * @var gkpaszHelpCmdLineMessages
 * @brief Help command line messages
 */
extern const char* gkpaszHelpCmdLineMessages[];

/******************************************************************************
 *                                                                            *
 *                         Typedefs/Structs/Unions/Enums                      *
 *                                                                            *
 ******************************************************************************/

/**
 * @typedef PFNMOVEMENTS
 * @brief Function pointer to movement functions
 */
typedef void (*PFNMOVEMENTS)(void);

/**
 * @enum ENUM_STATUS
 * @brief Enumeration that represents game's status
 */
typedef enum ENUM_STATUS {
  STATUS_IDLE, /**< Do nothing  */
  STATUS_RUN,  /**< Game run    */
  STATUS_PAUSE /**< Game pause  */
} ENUM_STATUS, *PENUM_STATUS;

/******************************************************************************
 *                                                                            *
 *                                  Prototypes                                *
 *                                                                            *
 ******************************************************************************/

/**
 * @brief ...
 *
 * @return boolean
 */
boolean bInitGame(void);

/**
 * @brief Load all sprites of the game
 *
 * @return TRUE load with success
 * @return FALSE sprite load error
 */
boolean bLoadSprites(void);

/**
 * @brief Free all sprites loaded with bLoadSprites
 */
void vDestroySprites(void);

/**
 * @brief ...
 *
 */
void vDestroyGame(void);

/**
 * @brief Load a level from a file
 *
 * @param kpszMapFile is the path of level file
 * @return TRUE load with success
 * @return FALSE level load error
 */
boolean bLoadLevel(const char *kpszMapFile);

/**
 * @brief Main menu
 */
void vMainMenu(void);

/**
 * @brief Handle the game events
 */
void vHandleEvents(void);

/**
 * @brief Show the map of the current level on the screen
 */
void vDrawMap(void);

/**
 * @brief Draw game info on the screen
 */
void vDrawGameInfo(void);

/**
 * @brief ...
 *
 */
void vResetLevel(void);

/**
 * @brief Reset game global variables
 */
void vResetGame(void);

/**
 * @brief Update global variables to the next level
 */
void vLevelUp(void);

/**
 * @brief Show game over message and reset the game
 */
void vGameOver(void);

/**
 * @brief ...
 *
 */
void vTimeOut(void);

/**
 * @brief Show you win message and reset the game
 */
void vYouWin(void);

/**
 * @brief Check if the player finish the current level
 *
 * @return TRUE player finish the current level
 * @return FALSE player didn't finish the current level
 */
boolean bLevelComplete(void);

/**
 * @brief Check if the player win the game
 *
 * @return TRUE game end
 * @return FALSE player didn't win the game
 */
boolean bWinGame(void);

/**
 * @brief Command press up or w key
 */
void vUp(void);

/**
 * @brief Command press a or left key
 */
void vLeft(void);

/**
 * @brief Command press down or s key
 */
void vDown(void);

/**
 * @brief Command press right or d key
 */
void vRight(void);

/**
 * @brief Call vHeroMove and vGhostsMove
 */
void vMove(void);

/**
 * @brief Update the screen
 */
void vUpdateScreen(void);

/******************************************************************************
 *                                                                            *
 *                               Global Variables                             *
 *                                                                            *
 ******************************************************************************/

/**
 * @var gbShowHelp
 * @brief Used to show help message about command line in terminal
 */
extern boolean gbShowHelp;

/**
 * @var gbShowVersion
 * @brief Used to show the version of the software in the terminal
 */
extern boolean gbShowVersion;

/**
 * @var gbShowPowerMessage
 * @brief Used to show power message
 */
extern boolean gbShowPowerMessage;

/**
 * @var geStatus
 * @brief It's the status of the game
 */
extern ENUM_STATUS geStatus;

/**
 * @var giLevel
 * @brief Current game level
 */
extern int giLevel;

/**
 * @var gbGameOver
 * @brief Define if the game is over
 */
extern boolean gbGameOver;

/**
 * @brief ...
 *
 */
extern boolean gbTimeOut;

/**
 * @brief ...
 *
 */
extern const int gkaiLevelsTime[MAX_LEVEL];

/**
 * @brief ...
 *
 */
extern int giCurrentLevelTime;

/**
 * @var gpstMusic
 * @brief It's the theme music of the game
 */
extern Mix_Music* gpstMusic;

/**
 * @var gpstGameOverSound
 * @brief It's the game over sound
 */
static Mix_Chunk* gpstGameOverSound = NULL;

#endif
