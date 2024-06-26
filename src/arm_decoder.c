#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "arm_decoder.h"
#include "log.h"

#define REG_REGISTER(_reg)                  \
        {                                   \
            .reg_name = #_reg,              \
            .decoder = _reg##_decoder,      \
            .spec_print = _reg##_print,     \
            .illustrate = _reg##_illustrate \
        }

enum reg_op {
    REG_DECODER,
    REG_SPEC_PRINT,
    REG_ILLUSTRATE,
};

struct reg_descrp {
    char *reg_name;
    void (*decoder)(uint64_t);
    void (*spec_print)(void);
    void (*illustrate)(void);
};

static struct reg_descrp reg_support_list[] = {
    REG_REGISTER(cpsr),
};

#define SUPPORT_REG_NUM (sizeof(reg_support_list)/sizeof(reg_support_list[0]))

static int find_reg_idx(char *reg_name)
{
    int i = 0;

    if (reg_name == NULL)
        return -1;

    for (i = 0; i < SUPPORT_REG_NUM; i++) {
        if (strncmp(reg_name, reg_support_list[i].reg_name, 
            strlen(reg_support_list[i].reg_name)) == 0)
            goto match;
    }

    return -1;
match:
    return i;
}

#include <argp.h>

struct decoder_info {
    char reg_name[10];
    enum reg_op reg_ops;
    uint64_t reg_value;
};

static struct argp_option options[] = {
    { "decode", 'd', "REG_NAME=0x12345678", 0, "Decode register value."},
    { "spec", 's', "REG_NAME", 0, "Print the specified register spec."},
    { 0 } 
};


static error_t parse_opt(int key, char *arg, struct argp_state *state)
{
    struct decoder_info *decoder = state->input;

    switch(key) {
        case 'd':
            decoder->reg_ops = REG_DECODER;
            sscanf(arg, "%9[^=]=%lx", decoder->reg_name, &(decoder->reg_value));
            break;
        case 's':
            decoder->reg_ops = REG_SPEC_PRINT;
            snprintf(decoder->reg_name, sizeof(decoder->reg_name), "%s", arg);
            break;
        default:
            return ARGP_ERR_UNKNOWN;    
    }

    return 0;
}

static struct argp argp = { options, parse_opt, 0, 0, 0, 0, 0 };

static int reg_ops_dispatch(struct decoder_info *decoder)
{
    int idx = 0;

    idx = find_reg_idx(decoder->reg_name);
    if (idx < 0)
        goto fail;

    switch(decoder->reg_ops) {
        case REG_DECODER:
            (reg_support_list[idx].decoder)(decoder->reg_value);
            break;
        default:
            goto fail;
    }

    return 0;
fail:
    return -1;
}

int main(int argc, char **argv)
{
    int ret = 0;
    struct decoder_info decoder = {0};


    ret = argp_parse(&argp, argc, argv, 0, 0, &decoder);
    if (ret)
        goto fail;
    
    ret = reg_ops_dispatch(&decoder);
    if (ret)
        goto fail;

    return 0;
fail:
    return -1;
}