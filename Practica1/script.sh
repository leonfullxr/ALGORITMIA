#!/bin/bash

output_file=./data/ficheroSalidaBorrado.txt
seed=123456

# Generate arguments from 1000 to 30000 with an increment of 1000
args=$(seq 1000 1000 100000)

# Execute the program once with all arguments
./bin/borradoDuplicadosIterativo "$output_file" "$seed" $args

