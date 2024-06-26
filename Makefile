BUILD_DIR := out
BUILD_SRC_DIR := out/src
SRC_DIR := src
SRC_SRCS := $(shell find $(SRC_DIR) -name '*.c')
SRC_OBJS := $(addprefix ${BUILD_DIR}/, $(patsubst %.c,%.o,$(SRC_SRCS)))
SRC_DEPS := $(patsubst %.o,%.d,$(SRC_OBJS))
BIN := arm_decoder

CC := gcc
LD := ld

#-Wp,-MD,$(SRC_DEPS) -MT $@ -MP
Q := @

all: $(BUILD_SRC_DIR) $(BUILD_DIR)/$(BIN)
	${Q}echo "Build project success"

$(BUILD_SRC_DIR): $(BUILD_DIR)
	${Q}mkdir -p $@

$(BUILD_DIR):
	${Q}mkdir -p $@

$(BUILD_DIR)/$(BIN): $(SRC_OBJS)
	${Q}echo "  LD      $^"
	${Q}$(CC) $(SRC_OBJS) -o $@

$(BUILD_SRC_DIR)/%.o: $(SRC_DIR)/%.c
	${Q}echo "  CC      $<"
	${Q}$(CC) -c $< -o $@

clean:
	${Q}echo "Clean project"
	${Q}rm -rf $(BUILD_DIR)
