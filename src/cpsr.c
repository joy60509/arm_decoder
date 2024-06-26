#include <stdint.h>
#include <stdio.h>

#include "log.h"
void cpsr_decoder(uint64_t cpsr_value)
{
    printf("%s 123123123\n", __func__);
    return;
}

void cpsr_print(void)
{
    return;
}

void cpsr_illustrate(void)
{
    HELP_L2_PRINTF("Current Program Status Register(CPSR)");

    HELP_L3_PRINTF("Holds PE status and control information.");

    return;
}