#!/bin/bash

echo "For generating the tables Python3 with SciPy should be installed"

echo "Generating T Distribution table"
python3 generators/main.py data/t.csv t 20

echo "Generating Chi-square Distribution table"
python3 generators/main.py data/chi.csv chi 20

echo "Generating F Distribution table"
python3 generators/main.py data/f.csv f 20 20

echo "Generation complete"
