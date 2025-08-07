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

#include <ctype.h>
#include "trace.h"

STRUCT_TRACE_PRM gstTracePrm;

static int bStrIsEmpty(const char *kpszString) {
  if ( kpszString == NULL ) {
    return 1;
  }
  while ( *kpszString ) {
    if ( !isspace((unsigned char) *kpszString) ) {
      return 0;
    }
    kpszString++;
  }
  return 1;
}

void vInitTrace(const char *kpszTrace, const char *kpszDebugLevel) {
  sprintf(gstTracePrm.szTrace, "%s", kpszTrace);
  sprintf(gstTracePrm.szDebugLevel, "%s", kpszDebugLevel);
}


void vTrace(const char* kpszFmt, ...) {
  FILE* fpTrace = NULL;
  time_t lSeconds = 0;
  struct tm* pstToday = NULL;
  va_list ap;

  if ( bStrIsEmpty(gstTracePrm.szTrace) || bStrIsEmpty(gstTracePrm.szDebugLevel) ) return;
  lSeconds = time(NULL);
  pstToday = localtime(&lSeconds);

  va_start(ap, kpszFmt);
  if ( (fpTrace = fopen(gstTracePrm.szTrace, "a")) == NULL ) {
    fprintf(stderr, "E: Impossible to open the file [%s]: [%s]", gstTracePrm.szTrace, strerror(errno));
    return;
  }
  fprintf(
    fpTrace,
    "%02d/%02d/%02d %02d:%02d:%02d - ",
    pstToday->tm_mday,
    pstToday->tm_mon+1,
    pstToday->tm_year+1900,
    pstToday->tm_hour,
    pstToday->tm_min,
    pstToday->tm_sec
  );
  vfprintf(fpTrace, kpszFmt, ap);
  fprintf(fpTrace, "\n");
  fclose(fpTrace);
  fpTrace = NULL;
  va_end(ap);
}

void vTraceCmdLine(int argc, char **argv) {
  int ii = 0;
  for ( ii = 0; ii < argc; ii++ ) {
    vTrace("%d: [%s]", ii, argv[ii]);
  }
}
