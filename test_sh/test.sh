#!/bin/sh

echo -e "Rulare guided \v" >> Final.txt
echo -e "Rulare guided  \v" 

gcc -O3  -fopenmp -fdump-tree-all heat_transfer_omp.cpp `pkg-config opencv --libs --cflags` -lstdc++

for j in {1..10}
do
        echo -e "N_Threads = $j \v" >> Final.txt
	echo -e "N_Threads = $j \v"
        for i in {1..3}
        do
                export OMP_NUM_THREADS=$j
		export OMP_SCHEDULE="guided,1"
                ./a.out >> Final.txt
        done
done

for j in {12..60..2}
do
        echo -e "N_Threads = $j \v" >> Final.txt
	echo -e "N_Threads = $j \v"
        for i in {1..3}
        do
                export OMP_NUM_THREADS=$j
		export OMP_SCHEDULE="guided,1"
                ./a.out >> Final.txt
        done
done


echo -e "Rulare guided Chunk = 4\v" >> Final.txt
echo -e "Rulare guided Chunk = 4\v" 
for j in {1..10}
do
        echo -e "N_Threads = $j \v" >> Final.txt
	echo -e "N_Threads = $j \v"
        for i in {1..3}
        do
                export OMP_NUM_THREADS=$j
		export OMP_SCHEDULE="guided,4"
                ./a.out >> Final.txt
        done
done

for j in {12..60..2}
do
        echo -e "N_Threads = $j \v" >> Final.txt
	echo -e "N_Threads = $j \v"
        for i in {1..3}
        do
                export OMP_NUM_THREADS=$j
		export OMP_SCHEDULE="guided,4"
                ./a.out >> Final.txt
        done
done


echo -e "Rulare guided Chunk = 8\v" >> Final.txt
echo -e "Rulare guided Chunk = 8\v" 
for j in {1..10}
do
        echo -e "N_Threads = $j \v" >> Final.txt
	echo -e "N_Threads = $j \v"
        for i in {1..3}
        do
                export OMP_NUM_THREADS=$j
		export OMP_SCHEDULE="guided,8"
                ./a.out >> Final.txt
        done
done

for j in {12..60..2}
do
        echo -e "N_Threads = $j \v" >> Final.txt
	echo -e "N_Threads = $j \v"
        for i in {1..3}
        do
                export OMP_NUM_THREADS=$j
		export OMP_SCHEDULE="guided,8"
                ./a.out >> Final.txt
        done
done



echo -e "Rulare guided Chunk = 16\v" >> Final.txt
echo -e "Rulare guided Chunk = 16\v" 
for j in {1..10}
do
        echo -e "N_Threads = $j \v" >> Final.txt
	echo -e "N_Threads = $j \v"
        for i in {1..3}
        do
                export OMP_NUM_THREADS=$j
		export OMP_SCHEDULE="guided,16"
                ./a.out >> Final.txt
        done
done

for j in {12..60..2}
do
        echo -e "N_Threads = $j \v" >> Final.txt
	echo -e "N_Threads = $j \v"
        for i in {1..3}
        do
                export OMP_NUM_THREADS=$j
		export OMP_SCHEDULE="guided,16"
                ./a.out >> Final.txt
        done
done



echo -e "Rulare guided Chunk = 32\v" >> Final.txt
echo -e "Rulare guided Chunk = 32\v" 
for j in {1..10}
do
        echo -e "N_Threads = $j \v" >> Final.txt
	echo -e "N_Threads = $j \v"
        for i in {1..3}
        do
                export OMP_NUM_THREADS=$j
		export OMP_SCHEDULE="guided,32"
                ./a.out >> Final.txt
        done
done

for j in {12..60..2}
do
        echo -e "N_Threads = $j \v" >> Final.txt
	echo -e "N_Threads = $j \v"
        for i in {1..3}
        do
                export OMP_NUM_THREADS=$j
		export OMP_SCHEDULE="guided,32"
                ./a.out >> Final.txt
        done
done


echo -e "Rulare guided Chunk = 64\v" >> Final.txt
echo -e "Rulare guided Chunk = 64\v" 
for j in {1..10}
do
        echo -e "N_Threads = $j \v" >> Final.txt
	echo -e "N_Threads = $j \v"
        for i in {1..3}
        do
                export OMP_NUM_THREADS=$j
		export OMP_SCHEDULE="guided,64"
                ./a.out >> Final.txt
        done
done

for j in {12..60..2}
do
        echo -e "N_Threads = $j \v" >> Final.txt
	echo -e "N_Threads = $j \v"
        for i in {1..3}
        do
                export OMP_NUM_THREADS=$j
		export OMP_SCHEDULE="guided,64"
                ./a.out >> Final.txt
        done
done
