/**
 * @file trace.h
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

#ifndef _TRACE_H_
#define _TRACE_H_

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <time.h>
#include <stdarg.h>
#include <string.h>

/**
 * @def DEBUG_INFO
 * @brief Trace info debug messages
 */
#define DEBUG_INFO         gstTracePrm.szDebugLevel[0] > '0'

/**
 * @def DEBUG_WARNING
 * @brief Trace warning debug messages
 */
#define DEBUG_WARNING      gstTracePrm.szDebugLevel[0] > '1'

/**
 * @def DEBUG_ERROR
 * @brief Trace error debug messages
 */
#define DEBUG_ERROR        gstTracePrm.szDebugLevel[0] > '2'

/**
 * @def DEBUG_FATAL
 * @brief Trace fatal debug messages
 */
#define DEBUG_FATAL        gstTracePrm.szDebugLevel[0] > '3'

/**
 * @def DEBUG_DETAILS
 * @brief Trace debug details messages
 */
#define DEBUG_DETAILS      gstTracePrm.szDebugLevel[0] > '4'

/**
 * @def DEBUG_TRACE
 * @brief Trace debug messages
 */
#define DEBUG_TRACE        gstTracePrm.szDebugLevel[0] > '5'

/**
 * @def DEBUG_MORE_DETAILS
 * @brief Trace debug more details messages
 */
#define DEBUG_MORE_DETAILS gstTracePrm.szDebugLevel[0] > '6'

/**
 * @def DEBUG_VERBOSE
 * @brief Trace debug verbose messages
 */
#define DEBUG_VERBOSE      gstTracePrm.szDebugLevel[0] > '7'

/**
 * @def DEBUG_ALL
 * @brief Trace all debug messages
 */
#define DEBUG_ALL          gstTracePrm.szDebugLevel[0] > '8'

typedef struct STRUCT_TRACE_PRM {
  char szTrace[256];
  char szDebugLevel[32];
} STRUCT_TRACE_PRM, *PSTRUCT_TRACE_PRM;

extern STRUCT_TRACE_PRM gstTracePrm;

void vInitTrace(const char *kpszTrace, const char *kpszDebugLevel);

/**
 * @brief Trace message in .log file
 *
 * @param kpszMsg Message
 */
void vTrace(const char* kpszFmt, ...);

/**
 * @brief Trace the command line in .log file
 *
 * @param argc Argument counter
 * @param argv Argument vector
 */
void vTraceCmdLine(int argc, char** argv);

#endif
