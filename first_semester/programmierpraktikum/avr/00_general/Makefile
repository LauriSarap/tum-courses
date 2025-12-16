# Test Makefile for AVR Simulator
# Usage:
#   make sim     - Build and run with simulator
#   make clean   - Clean build artifacts

SRC = main.c
SIM_DIR = ../simulator

.PHONY: sim clean

sim:
	make -f $(SIM_DIR)/Makefile SRC=$(SRC) run

clean:
	make -f $(SIM_DIR)/Makefile clean
