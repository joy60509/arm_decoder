#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "cpsr.h"
#include "reg_mgnt.h"

#define REG_REGISTER(_reg)                      \
        {                                       \
            .reg_name = #_reg,                  \
            .handler = {                        \
                .decoder = _reg##_decoder,      \
                .spec_print = _reg##_print,     \
                .illustrate = _reg##_illustrate \
            },                                  \
        }

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

int fill_reg_descript(char *reg_name, uint64_t reg_value, enum reg_op reg_mode)
{
    int idx = 0;

    idx = find_reg_idx(reg_name);
    if (idx >= 0) {
        reg_support_list[idx].reg_value = reg_value;
        reg_support_list[idx].reg_hanlder_mode = reg_mode;
    }

    return 0;
}

struct reg_descrp *get_reg_descript(char *reg_name)
{
    int idx = 0;

    idx = find_reg_idx(reg_name);

    return (idx >= 0 ? &reg_support_list[idx] : NULL);
}

int exec_reg_descript(struct reg_descrp *descript)
{
    switch(descript->reg_hanlder_mode) {
        case REG_DECODER:
            ((descript->handler).decoder)(descript->reg_value);
            break;
        default:
            goto fail;
    }

    return 0;
fail:
    return -1;

}
