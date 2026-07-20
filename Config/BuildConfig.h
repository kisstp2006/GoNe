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