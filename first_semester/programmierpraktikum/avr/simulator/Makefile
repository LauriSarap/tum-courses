# AVR Simulator Makefile
#
# Usage from simulator directory:
#   make SRC=../01_led/p.c        - Build exercise 01
#   make run SRC=../01_led/p.c    - Build and run exercise 01
#   make clean                    - Remove build artifacts
#
# Usage from an exercise directory (e.g., 01_led/):
#   make -f ../simulator/Makefile SRC=p.c
#   make -f ../simulator/Makefile SRC=p.c run

CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -g -O2
LDFLAGS = -lncurses

# Default source file (for testing)
SRC ?= ../00_general/main.c

# Find simulator directory relative to this Makefile
MAKEFILE_DIR := $(dir $(abspath $(lastword $(MAKEFILE_LIST))))
SIM_SRC := $(MAKEFILE_DIR)avr_sim.c
SIM_INC := -I$(MAKEFILE_DIR)

# Output binary
OUT = avr_sim

.PHONY: all run clean help

all: $(OUT)

$(OUT): $(SRC) $(SIM_SRC)
	$(CC) $(CFLAGS) $(SIM_INC) -o $@ $(SRC) $(SIM_SRC) $(LDFLAGS)

run: $(OUT)
	./$(OUT)

clean:
	rm -f $(OUT) *.o

help:
	@echo "AVR Simulator - Build System"
	@echo ""
	@echo "Usage:"
	@echo "  make SRC=<source_file>       Build simulator with specified source"
	@echo "  make run SRC=<source_file>   Build and run"
	@echo "  make clean                   Remove build artifacts"
	@echo ""
	@echo "Examples:"
	@echo "  make SRC=../01_led/p.c"
	@echo "  make run SRC=../04_taster_pollen/p.c"
