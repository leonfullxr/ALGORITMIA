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

RANDOM_INT := $(shell bash -c "awk 'BEGIN{srand();print( int(65536*rand()) )}'")

RR := ./
SIZES := 1000 2000 3000 10000 20000 30000
MAX_VALUE := $(RANDOM_INT)
SEED := $(RANDOM_INT)

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
	@echo "$(IFG) - rb:$(EC) $(BIND)/burbuja.bin $(TXTD)/burbuja_times.txt $(SIZES)"
	@echo "$(IFG) - rh:$(EC) $(BIND)/heapsort.bin <RANDOM_INT> $(SIZES) > $(TXTD)/heapsort_times.txt"
	@echo "$(IFG) - rm:$(EC) $(BIND)/mergesort.bin <RANDOM_INT> $(SIZES) > $(TXTD)/mergesort_times.txt"

rb: burbuja
	@echo "\n$(IFG)Data times in file ./$(TXTD)/$<_times.txt!:$(END)$(PFG)"
	@cat ./$(TXTD)/$<_times.txt

rh: heapsort
	@echo "\n$(IFG)Data times in file ./$(TXTD)/$<_times.txt!:$(END)$(PFG)"
	@cat ./$(TXTD)/$<_times.txt

rm: mergesort
	@echo "\n$(IFG)Data times in file ./$(TXTD)/$<_times.txt!:$(END)$(PFG)"
	@cat ./$(TXTD)/$<_times.txt

burbuja: $(BIND)/burbuja.bin
	$(RR)$< ./$(TXTD)/$@_times.txt $(SIZES)

heapsort: $(BIND)/heapsort.bin
	$(RR)$< $(SEED) $(MAX_VALUE) $(SIZES) > ./$(TXTD)/$@_times.txt

mergesort: $(BIND)/mergesort.bin
	$(RR)$< $(SEED) $(SIZES) > ./$(TXTD)/$@_times.txt

.PHONY: all clean
