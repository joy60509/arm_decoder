#ifndef __ARM_DECODER_H__
#define __ARM_DECODER_H__

#include "cpsr.h"

static inline void unknown_decoder(uint64_t unknown_value)
{
    HELP_L2_PRINTF("Reigster name mismatch");
}

static inline void unknown_print(void)
{
    HELP_L2_PRINTF("Reigster name mismatch");
}

static inline void unknown_illustrate(void)
{
    HELP_L2_PRINTF("Reigster name mismatch");
}

#endif //__ARM_DECODER_H__
