#!/bin/sh
# run mpi_pi.c con np de 1 a 8

mpicc -o pi mpi_pi.c

for i in $(seq 1 8)
do
mpirun -np $i ./pi
done
