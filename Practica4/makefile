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

RANDOM_MAXV := $(shell bash -c "awk 'BEGIN{srand();print( int(100000*rand()) )}'")
RANDOM_SEED := $(shell bash -c "awk 'BEGIN{srand();print( int(65536*rand()) )}'")

RR := ./

MAX_VALUE := $(RANDOM_MAXV)
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
	-rm -rf ./$(BIND)

$(DIRSTRUCT):
	@mkdir -p $@

$(BIND)/%.bin: $(SRCD)/%.cpp
	@echo "\n$(LGFG)Compiling $@...$(EC)"
	$(CC) $< $(CFLAGS) -I$(LIBD) -o $@

preamble:
	@echo "$(PBG)*************************************************$(EC)"
	@echo "$(PBG)*$(EC)                 Algoritmica                   $(PBG)*$(EC)"
	@echo "$(PBG)*$(EC)               Curso 2022-2023                 $(PBG)*$(EC)"
	@echo "$(PBG)*-----------------------------------------------*$(EC)"
	@echo "$(PBG)*$(EC)                 Práctica 4                    $(PBG)*$(EC)"
	@echo "$(PBG)*$(EC)     Algoritmos de Programación Dinámica       $(PBG)*$(EC)"
	@echo "$(PBG)*-----------------------------------------------*$(EC)"
	@echo "$(PBG)*$(EC) Trabajo realizado por:                        $(PBG)*$(EC)"
	@echo "$(PBG)*$(EC) - Toni Marti Albons                           $(PBG)*$(EC)"
	@echo "$(PBG)*$(EC) - León Elliott Fuller                         $(PBG)*$(EC)"
	@echo "$(PBG)*$(EC) - Alejandro Madueño Buciegas                  $(PBG)*$(EC)"
	@echo "$(PBG)*************************************************$(EC)"

indexes:
	@echo "\n$(IFG)Execution indexes (type make <index> to execute):$(EC)"
	@echo
		@echo "$(IFG) - DBP-B (Benchmark):$(EC) $(BIND)/DealerBagProblem.bin b n"
		@echo "$(IFG) - DBP-F1 (File 1):$(EC) $(BIND)/DealerBagProblem.bin f ./data/example1.txt v"
		@echo "$(IFG) - DBP-F2 (File 2):$(EC) $(BIND)/DealerBagProblem.bin f ./data/example2.txt v"
		@echo "$(IFG) - DBP-E1 (Example 1):$(EC) $(BIND)/DealerBagProblem.bin e 1 v"
		@echo "$(IFG) - DBP-E2 (Example 2):$(EC) $(BIND)/DealerBagProblem.bin e 2 v"
		@echo "$(IFG) - DBP-E3 (Example 3):$(EC) $(BIND)/DealerBagProblem.bin e 3 v"
		@echo "$(IFG) - DBP-E4 (Example 4):$(EC) $(BIND)/DealerBagProblem.bin e 4 v"
		@echo "$(IFG) - DBP-E5 (Example 5):$(EC) $(BIND)/DealerBagProblem.bin e 5 v"
		@echo "$(IFG) - DBP-E6 (Example 6):$(EC) $(BIND)/DealerBagProblem.bin e 6 v"
		@echo "$(IFG) - DBP-E7 (Example 7):$(EC) $(BIND)/DealerBagProblem.bin e 7 v"
		@echo "$(IFG) - DBP-W (analisis eficiencia W cte):$(EC) $(BIND)/efficiency_analysis_w_constant.bin"
		@echo "$(IFG) - DBP-N (analisis eficiencia N cte):$(EC) $(BIND)/efficiency_analysis_n_constant.bin"

DBP-B: $(BIND)/DealerBagProblem.bin
	$(RR)$< b n

DBP-F1: $(BIND)/DealerBagProblem.bin
	$(RR)$< f $(TXTD)/example1.txt v
	
DBP-F2: $(BIND)/DealerBagProblem.bin
	$(RR)$< f $(TXTD)/example2.txt v

DBP-E1: $(BIND)/DealerBagProblem.bin
	$(RR)$< e 1 v

DBP-E2: $(BIND)/DealerBagProblem.bin
	$(RR)$< e 2 v

DBP-E3: $(BIND)/DealerBagProblem.bin
	$(RR)$< e 3 v

DBP-E4: $(BIND)/DealerBagProblem.bin
	$(RR)$< e 4 v

DBP-E5: $(BIND)/DealerBagProblem.bin
	$(RR)$< e 5 v

DBP-E6: $(BIND)/DealerBagProblem.bin
	$(RR)$< e 6 v

DBP-E7: $(BIND)/DealerBagProblem.bin
	$(RR)$< e 7 v
	
DBP-W: $(BIND)/efficiency_analysis_w_constant.bin
	$(RR)$<
	
DBP-N: $(BIND)/efficiency_analysis_n_constant.bin
	$(RR)$<

.PHONY: all clean
