/**
 * @file audio.h
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

#ifndef _AUDIO_H_
#define _AUDIO_H_

#include <SDL2/SDL_mixer.h>

/**
 * @def AUDIO_FREQUENCY
 * @brief It's the frequency to playback audio at (in Hz).
 */
#define AUDIO_FREQUENCY 44100

/**
 * @def AUDIO_CHUNKSIZE
 * @brief It's the audio buffer size in sample FRAMES (total samples divided by
 * channel count).
 */
#define AUDIO_CHUNKSIZE 2048

#endif
