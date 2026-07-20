/*
 * GoNe - Build configuration (header)
 * Copyright (C) 2026  <your name>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef GONE_BUILD_CONFIG_H
#define GONE_BUILD_CONFIG_H

/*
 * The build system should define exactly one of these:
 *
 * GONE_DEBUG_BUILD
 * GONE_RELEASE_BUILD
 */

#if defined(GONE_DEBUG_BUILD) && defined(GONE_RELEASE_BUILD)
    #error "Both GONE_DEBUG_BUILD and GONE_RELEASE_BUILD are defined."
#endif

#if defined(GONE_DEBUG_BUILD)

    #define GONE_IS_DEBUG_BUILD   1
    #define GONE_IS_RELEASE_BUILD 0
    #define GONE_BUILD_NAME       "Debug"

#elif defined(GONE_RELEASE_BUILD)

    #define GONE_IS_DEBUG_BUILD   0
    #define GONE_IS_RELEASE_BUILD 1
    #define GONE_BUILD_NAME       "Release"

#else

    /*
     * Fallback detection.
     */
    #if defined(_DEBUG)

        #define GONE_IS_DEBUG_BUILD   1
        #define GONE_IS_RELEASE_BUILD 0
        #define GONE_BUILD_NAME       "Debug"

    #elif defined(NDEBUG)

        #define GONE_IS_DEBUG_BUILD   0
        #define GONE_IS_RELEASE_BUILD 1
        #define GONE_BUILD_NAME       "Release"

    #else

        #define GONE_IS_DEBUG_BUILD   0
        #define GONE_IS_RELEASE_BUILD 0
        #define GONE_BUILD_NAME       "Unknown"

    #endif

#endif

#endif