/**
 * @file main.c
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

/******************************************************************************
 *                                                                            *
 *                                 Command Line                               *
 *                                                                            *
 ******************************************************************************/


const char* gkpszProgramName = NULL;
STRUCT_COMMAND_LINE gstCmdLine;

/**
 * @var opterr
 * @brief external variable.
 * Set 0 to disable default getopt error message
 */
int opterr = 0;

const char* gkpszShortOptions = "h,v,t:d:";

const struct option astCmdOpt[] = {
  { "help"       , no_argument      , 0, 'h' },
  { "version"    , no_argument      , 0, 'v' },
  { "trace"      , required_argument, 0, 't' },
  { "debug-level", required_argument, 0, 'd' },
  { "img-dir"    , required_argument, 0, 'i' },
  { "level-dir"  , required_argument, 0, 'l' },
  { "font-dir"   , required_argument, 0, 'f' },
  { "audio-dir"  , required_argument, 0, 'a' },
  { NULL         , 0                , 0, 0   }
};

const char* gkpaszCmdLineExampleArguments[] = {
  NULL,
  NULL,
  "<path>",
  "<number>",
  "<path>",
  "<path>",
  "<path>",
  "<path>",
  NULL
};

const char* gkpaszHelpCmdLineMessages[] = {
  "Show this message and exit.",
  "Show the version and exit.",
  "<path> is the path of trace file.",
  "<number> is the debug level (default 0).",
#ifdef _WIN32
  "<path> is the game images directory path (default .\\assets\\img).",
  "<path> is the game levels directory path (default .\\assets\\levels).",
  "<path> is the ttf fonts directory path (default .\\assets\\font).",
  "<path> is the audio directory path (default .\\assets\\audio).",
#else
  "<path> is the game images directory path (default ./assets/img).",
  "<path> is the game levels directory path (default ./assets/levels).",
  "<path> is the ttf fonts directory path (default ./assets/font).",
  "<path> is the audio directory path (default ./assets/audio).",
#endif
  NULL
};

/******************************************************************************
 *                                                                            *
 *                               Global Variables                             *
 *                                                                            *
 ******************************************************************************/

boolean gbShowHelp = FALSE;
boolean gbShowVersion = FALSE;

/**
 * @brief Show the version of the software
 */
static void vShowVersion(void);

/**
 * @brief Show the help message about how to usage the command line arguments
 */
static void vShowUsage(void);

/**
 * @brief Parse the command line
 *
 * @param argc Command line argument counter
 * @param argv Command line argument vector
 *
 * @return TRUE command line was parsed with success
 * @return FALSE command line parser error
 */
static boolean bParseCommandLine(int argc, char** argv);

static void vShowVersion(void) {
  printf("%s %s [%s %s]\n", gkpszProgramName, VERSION, __DATE__, __TIME__);
}

static void vShowUsage(void) {
  int ii = 0;
  printf("Usage: %s --parameter=arguments\n", gkpszProgramName);
  for ( ii = 0; astCmdOpt[ii].name; ii++ ) {
    printf(
      "  -%c%s, --%s%s%s\n"
      "    %s\n",
      astCmdOpt[ii].val, gkpaszCmdLineExampleArguments[ii] ? gkpaszCmdLineExampleArguments[ii] : "",
      astCmdOpt[ii].name, gkpaszCmdLineExampleArguments[ii] ? "=" : "", gkpaszCmdLineExampleArguments[ii] ? gkpaszCmdLineExampleArguments[ii] : "",
      gkpaszHelpCmdLineMessages[ii]
    );
  }
}

static boolean bParseCommandLine(int argc, char **argv) {
  int iOpt = 0;
  int iLongInd = 0;
  while ( (iOpt = getopt_long(argc, argv, gkpszShortOptions, astCmdOpt, &iLongInd)) != -1 ) {
    switch ( iOpt ) {
      case 'h': {
        gbShowHelp = TRUE;
        return TRUE;
      }
      case 'v': {
        gbShowVersion = TRUE;
        return TRUE;
      }
      case 't': {
        sprintf(gstCmdLine.szTrace, "%s", optarg);
        break;
      }
      case 'd': {
        sprintf(gstCmdLine.szDebugLevel, "%s", optarg);
        break;
      }
      case 'm': {
        sprintf(gstCmdLine.szMap, "%s", optarg);
        break;
      }
      case '?':
      default: return FALSE;
    }
  }
  return TRUE;
}

/******************************************************************************
 *                                                                            *
 *                                   main                                     *
 *                                                                            *
 ******************************************************************************/
int main(int argc, char **argv) {
  gkpszProgramName = basename(argv[0]);

  memset(gszMap      , 0x00, sizeof(gszMap     ));
  memset(&gstPlayer  , 0x00, sizeof(gstPlayer  ));
  memset(gastGhost   , 0x00, sizeof(gastGhost  ));
  memset(&gstTracePrm, 0x00, sizeof(gstTracePrm));
  memset(&gstCmdLine , 0x00, sizeof(gstCmdLine ));

  if ( !bParseCommandLine(argc, argv) ) {
    vShowUsage();
    return -1;
  }

  if ( gbShowHelp ) {
    vShowUsage();
    return 0;
  }

  if ( gbShowVersion ) {
    vShowVersion();
    return 0;
  }

  if ( !bStrIsEmpty(gstCmdLine.szTrace) && !bStrIsEmpty(gstCmdLine.szDebugLevel) ) {
    vInitTrace(gstCmdLine.szTrace, gstCmdLine.szDebugLevel);
  }

  if ( DEBUG_DETAILS ) {
    vTrace("main - begin");
    vTraceCmdLine(argc, argv);
  }

  if ( bStrIsEmpty(gstCmdLine.szImgDir) ) {
    sprintf(gstCmdLine.szImgDir, "./assets%cimg", DIR_SEPARATOR);
  }
  if ( bStrIsEmpty(gstCmdLine.szLevelDir) ) {
    sprintf(gstCmdLine.szLevelDir, "./assets%clevels", DIR_SEPARATOR);
  }
  if ( bStrIsEmpty(gstCmdLine.szFontDir) ) {
    sprintf(gstCmdLine.szFontDir, "./assets%cfonts", DIR_SEPARATOR);
  }
  if ( bStrIsEmpty(gstCmdLine.szAudioDir) ) {
    sprintf(gstCmdLine.szAudioDir, "./assets%caudio", DIR_SEPARATOR);
  }
  sprintf(gszFontDir, "%s", gstCmdLine.szFontDir);

  if ( !bInitSDL() ) {
    if ( DEBUG_FATAL ) vTrace("main - F: error in bInitSDL!");
    return -1;
  }

  if ( !bInitGame() ) {
    if ( DEBUG_FATAL ) vTrace("main - F: error in bInitGame!");
    return -1;
  }

  /* main loop */
  while ( gbRun ) {
    giFrameStart = SDL_GetTicks();
    vHandleEvents();
    vUpdateScreen();
    giFrameTime = SDL_GetTicks() - giFrameStart;
    if ( giFrameTime < FRAME_DELAY ) {
      SDL_Delay(FRAME_DELAY - giFrameTime);
      if ( giCurrentLevelScore > 0 && giCurrentLevelTime > 0 ) giCurrentLevelTime--;
    }
  }

  vDestroyGame();
  vDestroySDL();

  if ( DEBUG_INFO ) vTrace("main - end");

  return 0;
}
