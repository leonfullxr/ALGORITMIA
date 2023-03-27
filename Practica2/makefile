.ONESHELL:

################################################
#
# MAKEFILE VARIABLES
#
######################### Compilation
SRCD := src
BIND := bin
TXTD := data
LIBD := lib

DIRSTRUCT := $(BIND) $(TXTD)

SRCF := $(wildcard $(SRCD)/*.cpp)
BINF := $(SRCF:$(SRCD)/%.cpp=$(BIND)/%.bin)

CC := g++
CFLAGS := -Wall -Wextra -Wpedantic

######################### Execution (por rellenar según el programa)

RANDOM_SEED := $(shell bash -c "awk 'BEGIN{srand();print( int(65536*rand()) )}'")

K := 10
C_SIZE := 10

RR := ./
SEED := $(RANDOM_SEED)

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

all: preamble $(DIRSTRUCT) $(BINF) indexes 

clean:
	@echo "\n$(LRFG)Deleting $(BIN)...$(EC)\n"
	-rm -fv ./$(BIND)/* ./$(TXTD)/*

$(DIRSTRUCT):
	@mkdir -p $@

$(BIND)/%.bin: $(SRCD)/%.cpp
	@echo "\n$(LGFG)Compiling $@...$(EC)"
	$(CC) $(CFLAGS) -I$(LIBD) $< -o $@

preamble:
	@echo "$(PBG)*************************************************$(EC)"
	@echo "$(PBG)*$(EC)                 Algoritmica                   $(PBG)*$(EC)"
	@echo "$(PBG)*$(EC)               Curso 2022-2023                 $(PBG)*$(EC)"
	@echo "$(PBG)*-----------------------------------------------*$(EC)"
	@echo "$(PBG)*$(EC)                 Práctica 2                    $(PBG)*$(EC)"
	@echo "$(PBG)*$(EC)        Algoritmos divide y venceras           $(PBG)*$(EC)"
	@echo "$(PBG)*-----------------------------------------------*$(EC)"
	@echo "$(PBG)*$(EC) Trabajo realizado por:                        $(PBG)*$(EC)"
	@echo "$(PBG)*$(EC) - Toni Marti Albons                           $(PBG)*$(EC)"
	@echo "$(PBG)*$(EC) - León Elliott Fuller                         $(PBG)*$(EC)"
	@echo "$(PBG)*$(EC) - Alejandro Madueño Buciegas                  $(PBG)*$(EC)"
	@echo "$(PBG)*************************************************$(EC)"

indexes:
	@echo "\n$(IFG)Execution indexes (type make <index> to execute):$(EC)"
	@echo
	@echo "$(IFG) - hp_sec:$(EC) $(BIND)/hyperplane_SEC.bin $(SEED) $(K) $(C_SIZE)"
	@echo "$(IFG) - hp_dyv:$(EC) $(BIND)/hyperplane_DyV.bin $(SEED) $(K) $(C_SIZE)"

hp_sec: hyperplane_SEC
#	@cat ./$(TXTD)/$<_times.txt
#	@echo "$(EC)"

hyperplane_SEC: $(BIND)/hyperplane_SEC.bin
	$(RR)$< $(SEED) $(K) $(C_SIZE)

.PHONY: all clean
