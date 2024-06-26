#ifndef __REG_MGNT_HH__
#define __REG_MGNT_HH__

#include <stdint.h>

enum reg_op {
    REG_UNKNOWN,
    REG_DECODER,
    REG_SPEC_PRINT,
    REG_ILLUSTRATE,
};

struct reg_handler {
    void (*decoder)(uint64_t);
    void (*spec_print)(void);
    void (*illustrate)(void);
};

struct reg_descrp {
    char *reg_name;
    uint64_t reg_value;
    enum reg_op reg_hanlder_mode;
    struct reg_handler handler;
};

int fill_reg_descript(char *reg_name, uint64_t reg_value, enum reg_op reg_mode);
struct reg_descrp *get_reg_descript(char *reg_name);
int exec_reg_descript(struct reg_descrp *descript);

#endif //__REG_MGNT_HH__
