#ifndef __LOG_H__
#define __LOG_H__

#define _STR(x) #x
#define STR(x) _STR(x)
#define HELP_L1_PRINTF(_fmt, ...)   printf(_fmt STR(\n\n), ##__VA_ARGS__)
#define HELP_L2_PRINTF(_fmt, ...)   printf("  " _fmt STR(\n), ##__VA_ARGS__)
#define HELP_L3_PRINTF(_fmt, ...)   printf(STR(\t) _fmt STR(\n), ##__VA_ARGS__)

#endif //__LOG_H__