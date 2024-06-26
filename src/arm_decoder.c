#include <argp.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "reg_mgnt.h"

static struct argp_option options[] = {
    { "decode", 'd', "REG_NAME=0x12345678", 0, "Decode register value."},
    { "spec", 's', "REG_NAME", 0, "Print the specified register spec."},
    { 0 } 
};

static error_t parse_opt(int key, char *arg, struct argp_state *state)
{
    char reg_name[10] = {0};
    uint64_t reg_value = 0;
    enum reg_op reg_mode = REG_UNKNOWN;
    struct reg_descrp **descript = state->input;

    switch(key) {
        case 'd':
            reg_mode = REG_DECODER;
            sscanf(arg, "%9[^=]=%lx", reg_name, &reg_value);
            break;
        case 's':
            reg_mode = REG_SPEC_PRINT;
            snprintf(reg_name, sizeof(reg_name), "%s", arg);
            break;
        default:
            return ARGP_ERR_UNKNOWN;    
    }

    fill_reg_descript(reg_name, reg_value, reg_mode);
    *descript = get_reg_descript(reg_name);

    return 0;
}

static struct argp argp = { options, parse_opt, 0, 0, 0, 0, 0 };

int main(int argc, char **argv)
{
    int ret = 0;
    struct reg_descrp *descriptor = NULL;

    ret = argp_parse(&argp, argc, argv, 0, 0, &descriptor);
    if (ret)
        goto fail;
    
    ret = exec_reg_descript(descriptor);
    if (ret)
        goto fail;

    return 0;
fail:
    return -1;
}