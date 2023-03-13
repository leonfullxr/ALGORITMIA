.ONESHELL:

################################################
#
# MAKEFILE VARIABLES
#
######################### Compilation
SRCD := src
BIND := bin
TXTD := data

SRCF := $(wildcard $(SRCD)/*.cpp)
BINF := $(SRCF:$(SRCD)/%.cpp=$(BIND)/%.bin)

CC := g++
CFLAGS := -Wall -Wextra -Wpedantic

######################### Execution (por rellenar según el programa)

RR := ./
OUTPUT_FILE := ./$(TXTD)/burbuja_times.txt
SIZE := 1000 2000 3000 10000 20000 30000

######################### Colors

# Preamble Foreground (Brown)
PBG := \e[1;33m
# Black Foreground
BFG := \e[30m
# Indexes Foreground
IFG := \e[1;33m
# Light Red Foreground
LRFG := \e[1;31m
# Light Green Foreground
LGFG := \e[1;32m
# Purple Foreground
PFG := \e[35m
# End color
EC := \e[0m

################################################

all: preamble $(BINF) indexes

clean:
	@echo "\n$(LRFG)Deleting $(BIN)...$(EC)\n"
	-rm -fv ./$(BIND)/* ./$(TXTD)/*

$(BIND)/%.bin: $(SRCD)/%.cpp
	@echo "\n$(LGFG)Compiling $@...$(EC)"
	$(CC) $< $(CFLAGS) -o $@

preamble:
	@echo "$(PBG)*************************************************$(EC)"
	@echo "$(PBG)*$(EC)                 Algoritmica                   $(PBG)*$(EC)"
	@echo "$(PBG)*$(EC)               Curso 2022-2023                 $(PBG)*$(EC)"
	@echo "$(PBG)*-----------------------------------------------*$(EC)"
	@echo "$(PBG)*$(EC)                 Práctica 1                    $(PBG)*$(EC)"
	@echo "$(PBG)*$(EC)            Cálculo de eficiencia              $(PBG)*$(EC)"
	@echo "$(PBG)*-----------------------------------------------*$(EC)"
	@echo "$(PBG)*$(EC) Trabajo realizado por:                        $(PBG)*$(EC)"
	@echo "$(PBG)*$(EC) - Toni (Rellena nombre xd)                    $(PBG)*$(EC)"
	@echo "$(PBG)*$(EC) - León (Rellena nombre xd)                    $(PBG)*$(EC)"
	@echo "$(PBG)*$(EC) - Alejandro Madueño Buciegas                  $(PBG)*$(EC)"
	@echo "$(PBG)*************************************************$(EC)"

indexes:
	@echo "\n$(IFG)Execution indexes (type make <index> to execute):$(EC)"
	@echo "$(IFG) - rb:$(EC) $(BIND)/burbuja.bin $(OUTPUT_FILE) $(SIZE)"

rb: burbuja
	@echo "\n$(IFG)Data times in file ./$(TXTD)/$<_times.txt!"

burbuja: $(BIND)/burbuja.bin
	$(RR)$< ./$(TXTD)/$@_times.txt $(SIZE)

.PHONY: all clean
