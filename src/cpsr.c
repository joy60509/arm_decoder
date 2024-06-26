#include <stdint.h>
#include <stdio.h>

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
    printf("Current Program Status Register(CPSR)");

    printf("Holds PE status and control information.");

    return;
}