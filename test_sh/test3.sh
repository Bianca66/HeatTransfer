#!/bin/sh

echo -e "Rulare static Chunk = 64\v" >> Final2.txt
echo -e "Rulare static Chunk = 64\v" 

gcc -O3  -fopenmp -fdump-tree-all heat_transfer_omp.cpp `pkg-config opencv --libs --cflags` -lstdc++

for j in {1..10}
do
        echo -e "N_Threads = $j \v" >> Final2.txt
	echo -e "N_Threads = $j \v"
        for i in {1..3}
        do
                export OMP_NUM_THREADS=$j
		export OMP_SCHEDULE="static,64"
                ./a.out >> Final2.txt
        done
done

for j in {12..60..2}
do
        echo -e "N_Threads = $j \v" >> Final2.txt
	echo -e "N_Threads = $j \v"
        for i in {1..3}
        do
                export OMP_NUM_THREADS=$j
		export OMP_SCHEDULE="static,64"
                ./a.out >> Final2.txt
        done
done


echo -e "Rulare guided Chunk = 64\v" >> Final2.txt
echo -e "Rulare guided Chunk = 64\v" 
for j in {1..10}
do
        echo -e "N_Threads = $j \v" >> Final2.txt
	echo -e "N_Threads = $j \v"
        for i in {1..3}
        do
                export OMP_NUM_THREADS=$j
		export OMP_SCHEDULE="guided,64"
                ./a.out >> Final2.txt
        done
done

for j in {12..60..2}
do
        echo -e "N_Threads = $j \v" >> Final2.txt
	echo -e "N_Threads = $j \v"
        for i in {1..3}
        do
                export OMP_NUM_THREADS=$j
		export OMP_SCHEDULE="guided,64"
                ./a.out >> Final2.txt
        done
done


echo -e "Rulare dynamic Chunk = 64\v" >> Final2.txt
echo -e "Rulare dynamic Chunk = 64\v" 
for j in {1..10}
do
        echo -e "N_Threads = $j \v" >> Final2.txt
	echo -e "N_Threads = $j \v"
        for i in {1..3}
        do
                export OMP_NUM_THREADS=$j
		export OMP_SCHEDULE="dynamic,64"
                ./a.out >> Final2.txt
        done
done

for j in {12..60..2}
do
        echo -e "N_Threads = $j \v" >> Final2.txt
	echo -e "N_Threads = $j \v"
        for i in {1..3}
        do
                export OMP_NUM_THREADS=$j
		export OMP_SCHEDULE="dynamic,64"
                ./a.out >> Final2.txt
        done
done
