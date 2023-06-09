.ONESHELL:

################################################
#
# MAKEFILE VARIABLES
#
######################### Compilation
SRCD := src
BIND := bin
TXTD := data

DIRSTRUCT := $(BIND) $(TXTD)

SRCF := $(wildcard $(SRCD)/*.cpp)
BINF := $(SRCF:$(SRCD)/%.cpp=$(BIND)/%.bin)

CC := g++
CFLAGS := -Wall -Wextra -Wpedantic

######################### Execution (por rellenar según el programa)

RANDOM_MAXV := $(shell bash -c "awk 'BEGIN{srand();print( int(100000*rand()) )}'")
RANDOM_SEED := $(shell bash -c "awk 'BEGIN{srand();print( int(65536*rand()) )}'")

RR := ./
SIZES := $(shell seq 1000 1000 100000)
MAX_VALUE := $(RANDOM_MAXV)
SEED := $(RANDOM_SEED)
DISCS := 6
ANIMATION := Y

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
	@echo "$(PBG)*$(EC) - Toni Marti Albons                           $(PBG)*$(EC)"
	@echo "$(PBG)*$(EC) - León Elliott Fuller                         $(PBG)*$(EC)"
	@echo "$(PBG)*$(EC) - Alejandro Madueño Buciegas                  $(PBG)*$(EC)"
	@echo "$(PBG)*************************************************$(EC)"

indexes:
	@echo "\n$(IFG)Execution indexes (type make <index> to execute):$(EC)"
	@echo
	@echo "$(IFG) - rh:$(EC) $(BIND)/heapsort.bin $(SEED) $(MAX_VALUE) $(SIZES) > $(TXTD)/heapsort_times.txt"
	@echo
	@echo "$(IFG) - rm:$(EC) $(BIND)/mergesort.bin $(SEED) $(SIZES) > $(TXTD)/mergesort_times.txt"
	@echo
	@echo "$(IFG) - rd:$(EC) $(BIND)/borradoDuplicadosIterativo.bin $(TXTD)/borradoDuplicadosIterativo_times.txt $(SIZES)"
	@echo
	@echo "$(IFG) - rdo:$(EC) $(BIND)/borradoDuplicadosIterativoOrdenado.bin $(TXTD)/borradoDuplicadosIterativoOrdenado_times.txt $(SIZES)"
	@echo
	@echo "$(IFG) - rt:$(EC) $(BIND)/hanoi.bin $(DISCS) $(ANIMATION)"

rd: borradoDuplicadosIterativo
	@cat ./$(TXTD)/$<_times.txt
	@echo "$(EC)"

rdo: borradoDuplicadosIterativoOrdenado
	@echo "\n$(IFG)Data times in file ./$(TXTD)/$<_times.txt:$(PFG)"
	@cat ./$(TXTD)/$<_times.txt
	@echo "$(EC)"

rh: heapsort
	@echo "\n$(IFG)Data times in file ./$(TXTD)/$<_times.txt:$(PFG)"
	@cat ./$(TXTD)/$<_times.txt
	@echo "$(EC)"

rm: mergesort
	@echo "\n$(IFG)Data times in file ./$(TXTD)/$<_times.txt:$(PFG)"
	@cat ./$(TXTD)/$<_times.txt
	@echo "$(EC)"

rt: hanoi
	@echo "\n$(PFG)"

borradoDuplicadosIterativo: $(BIND)/borradoDuplicadosIterativo.bin
	$(RR)$< ./$(TXTD)/$@_times.txt $(SEED) $(SIZES)
	
borradoDuplicadosIterativoOrdenado: $(BIND)/borradoDuplicadosIterativoOrdenado.bin
	$(RR)$< ./$(TXTD)/$@_times.txt $(SEED) $(SIZES)

heapsort: $(BIND)/heapsort.bin
	$(RR)$< $(SEED) $(MAX_VALUE) $(SIZES) > ./$(TXTD)/$@_times.txt

mergesort: $(BIND)/mergesort.bin	
	$(RR)$< $(SEED) $(SIZES) > ./$(TXTD)/$@_times.txt

hanoi: $(BIND)/hanoi.bin
	$(RR)$< $(DISCS) $(ANIMATION)

.PHONY: all clean
