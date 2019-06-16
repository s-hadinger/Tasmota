/* pgmspace_bearssl.h - Accessor utilities/types for accessing PROGMEM data */

//#pragma GCC optimize ("O2")   // -Os is the default, forcing -O2 for BearSSL
#define PGM_READ_UNALIGNED 0    // all calls are aligned, take the optimized version

#include <sys/pgmspace.h>
