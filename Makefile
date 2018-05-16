BUILD_DIR := build
OBJ_DIR := $(BUILD_DIR)/obj
CC := gcc
CFLAGS := -std=c11
INC :=
RM := rm 

all: directory scheduler process

process: src/process.c
	$(CC) $(CFLAGS) -o $@ src/process.c

OBJ-SCHEDULER = scheduler.o sched_internal.o queue.o priority_queue.o fifo.o sjf.o psjf.o round_robin.o
	
scheduler: $(addprefix $(OBJ_DIR)/, $(OBJ-SCHEDULER))
	$(CC) $(CFLAGS) -o $@ $(addprefix $(OBJ_DIR)/, $(OBJ-SCHEDULER))

$(OBJ_DIR)/%.o : src/%.c
	$(CC) $< $(CFLAGS) $(INC) -c -o $@

.PHONY: directory
directory:
	mkdir -p $(BUILD_DIR)
	mkdir -p $(OBJ_DIR)

.PHONY: clean
clean:
	$(RM) -rf $(BUILD_DIR)