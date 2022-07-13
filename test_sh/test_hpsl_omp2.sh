#!/bin/sh

echo -e "Rulare static\v" >> final_hpsl_omp2.txt
echo -e "Rulare static\v" 

gcc -O3  -fopenmp -fdump-tree-all heat_transfer_omp2.cpp `pkg-config opencv --libs --cflags` -lstdc++

for j in {1..10}
do
        echo -e "N_Threads = $j \v" >> final_hpsl_omp2.txt
	echo -e "N_Threads = $j \v"
        for i in {1..2}
        do
                export OMP_NUM_THREADS=$j
		export OMP_SCHEDULE="static,1"
                ./a.out >> final_hpsl_omp2.txt
        done
done

for j in {12..60..2}
do
        echo -e "N_Threads = $j \v" >> final_hpsl_omp2.txt
	echo -e "N_Threads = $j \v"
        for i in {1..2}
        do
                export OMP_NUM_THREADS=$j
		export OMP_SCHEDULE="static,1"
                ./a.out >> final_hpsl_omp2.txt
        done
done

echo -e "Rulare static Chunk = 4\v" >> final_hpsl_omp2.txt
echo -e "Rulare static Chunk = 4\v" 

gcc -O3  -fopenmp -fdump-tree-all heat_transfer_omp2.cpp `pkg-config opencv --libs --cflags` -lstdc++

for j in {1..10}
do
        echo -e "N_Threads = $j \v" >> final_hpsl_omp2.txt
	echo -e "N_Threads = $j \v"
        for i in {1..2}
        do
                export OMP_NUM_THREADS=$j
		export OMP_SCHEDULE="static,4"
                ./a.out >> final_hpsl_omp2.txt
        done
done

for j in {12..60..2}
do
        echo -e "N_Threads = $j \v" >> final_hpsl_omp2.txt
	echo -e "N_Threads = $j \v"
        for i in {1..2}
        do
                export OMP_NUM_THREADS=$j
		export OMP_SCHEDULE="static,4"
                ./a.out >> final_hpsl_omp2.txt
        done
done



echo -e "Rulare static Chunk = 8\v" >> final_hpsl_omp2.txt
echo -e "Rulare static Chunk = 8\v" 

gcc -O3  -fopenmp -fdump-tree-all heat_transfer_omp2.cpp `pkg-config opencv --libs --cflags` -lstdc++

for j in {1..10}
do
        echo -e "N_Threads = $j \v" >> final_hpsl_omp2.txt
	echo -e "N_Threads = $j \v"
        for i in {1..2}
        do
                export OMP_NUM_THREADS=$j
		export OMP_SCHEDULE="static,8"
                ./a.out >> final_hpsl_omp2.txt
        done
done

for j in {12..60..2}
do
        echo -e "N_Threads = $j \v" >> final_hpsl_omp2.txt
	echo -e "N_Threads = $j \v"
        for i in {1..2}
        do
                export OMP_NUM_THREADS=$j
		export OMP_SCHEDULE="static,8"
                ./a.out >> final_hpsl_omp2.txt
        done
done

echo -e "Rulare static Chunk = 16\v" >> final_hpsl_omp2.txt
echo -e "Rulare static Chunk = 16\v" 

gcc -O3  -fopenmp -fdump-tree-all heat_transfer_omp2.cpp `pkg-config opencv --libs --cflags` -lstdc++

for j in {1..10}
do
        echo -e "N_Threads = $j \v" >> final_hpsl_omp2.txt
	echo -e "N_Threads = $j \v"
        for i in {1..2}
        do
                export OMP_NUM_THREADS=$j
		export OMP_SCHEDULE="static,16"
                ./a.out >> final_hpsl_omp2.txt
        done
done

for j in {12..60..2}
do
        echo -e "N_Threads = $j \v" >> final_hpsl_omp2.txt
	echo -e "N_Threads = $j \v"
        for i in {1..2}
        do
                export OMP_NUM_THREADS=$j
		export OMP_SCHEDULE="static,16"
                ./a.out >> final_hpsl_omp2.txt
        done
done


echo -e "Rulare static Chunk = 32\v" >> final_hpsl_omp2.txt
echo -e "Rulare static Chunk = 32\v" 

gcc -O3  -fopenmp -fdump-tree-all heat_transfer_omp2.cpp `pkg-config opencv --libs --cflags` -lstdc++

for j in {1..10}
do
        echo -e "N_Threads = $j \v" >> final_hpsl_omp2.txt
	echo -e "N_Threads = $j \v"
        for i in {1..2}
        do
                export OMP_NUM_THREADS=$j
		export OMP_SCHEDULE="static,32"
                ./a.out >> final_hpsl_omp2.txt
        done
done

for j in {12..60..2}
do
        echo -e "N_Threads = $j \v" >> final_hpsl_omp2.txt
	echo -e "N_Threads = $j \v"
        for i in {1..2}
        do
                export OMP_NUM_THREADS=$j
		export OMP_SCHEDULE="static,32"
                ./a.out >> final_hpsl_omp2.txt
        done
done

echo -e "Rulare static Chunk = 64\v" >> final_hpsl_omp2.txt
echo -e "Rulare static Chunk = 64\v" 

gcc -O3  -fopenmp -fdump-tree-all heat_transfer_omp2.cpp `pkg-config opencv --libs --cflags` -lstdc++

for j in {1..10}
do
        echo -e "N_Threads = $j \v" >> final_hpsl_omp2.txt
	echo -e "N_Threads = $j \v"
        for i in {1..2}
        do
                export OMP_NUM_THREADS=$j
		export OMP_SCHEDULE="static,64"
                ./a.out >> final_hpsl_omp2.txt
        done
done

for j in {12..60..2}
do
        echo -e "N_Threads = $j \v" >> final_hpsl_omp2.txt
	echo -e "N_Threads = $j \v"
        for i in {1..2}
        do
                export OMP_NUM_THREADS=$j
		export OMP_SCHEDULE="static,64"
                ./a.out >> final_hpsl_omp2.txt
        done
done


#!/bin/sh

echo -e "Rulare dynamic\v" >> final_hpsl_omp2.txt
echo -e "Rulare dynamic\v" 

gcc -O3  -fopenmp -fdump-tree-all heat_transfer_omp2.cpp `pkg-config opencv --libs --cflags` -lstdc++

for j in {1..10}
do
        echo -e "N_Threads = $j \v" >> final_hpsl_omp2.txt
	echo -e "N_Threads = $j \v"
        for i in {1..2}
        do
                export OMP_NUM_THREADS=$j
		export OMP_SCHEDULE="dynamic,1"
                ./a.out >> final_hpsl_omp2.txt
        done
done

for j in {12..60..2}
do
        echo -e "N_Threads = $j \v" >> final_hpsl_omp2.txt
	echo -e "N_Threads = $j \v"
        for i in {1..2}
        do
                export OMP_NUM_THREADS=$j
		export OMP_SCHEDULE="dynamic,1"
                ./a.out >> final_hpsl_omp2.txt
        done
done

echo -e "Rulare dynamic Chunk = 4\v" >> final_hpsl_omp2.txt
echo -e "Rulare dynamic Chunk = 4\v" 

gcc -O3  -fopenmp -fdump-tree-all heat_transfer_omp2.cpp `pkg-config opencv --libs --cflags` -lstdc++

for j in {1..10}
do
        echo -e "N_Threads = $j \v" >> final_hpsl_omp2.txt
	echo -e "N_Threads = $j \v"
        for i in {1..2}
        do
                export OMP_NUM_THREADS=$j
		export OMP_SCHEDULE="dynamic,4"
                ./a.out >> final_hpsl_omp2.txt
        done
done

for j in {12..60..2}
do
        echo -e "N_Threads = $j \v" >> final_hpsl_omp2.txt
	echo -e "N_Threads = $j \v"
        for i in {1..2}
        do
                export OMP_NUM_THREADS=$j
		export OMP_SCHEDULE="dynamic,4"
                ./a.out >> final_hpsl_omp2.txt
        done
done



echo -e "Rulare dynamic Chunk = 8\v" >> final_hpsl_omp2.txt
echo -e "Rulare dynamic Chunk = 8\v" 

gcc -O3  -fopenmp -fdump-tree-all heat_transfer_omp2.cpp `pkg-config opencv --libs --cflags` -lstdc++

for j in {1..10}
do
        echo -e "N_Threads = $j \v" >> final_hpsl_omp2.txt
	echo -e "N_Threads = $j \v"
        for i in {1..2}
        do
                export OMP_NUM_THREADS=$j
		export OMP_SCHEDULE="dynamic,8"
                ./a.out >> final_hpsl_omp2.txt
        done
done

for j in {12..60..2}
do
        echo -e "N_Threads = $j \v" >> final_hpsl_omp2.txt
	echo -e "N_Threads = $j \v"
        for i in {1..2}
        do
                export OMP_NUM_THREADS=$j
		export OMP_SCHEDULE="dynamic,8"
                ./a.out >> final_hpsl_omp2.txt
        done
done

echo -e "Rulare dynamic Chunk = 16\v" >> final_hpsl_omp2.txt
echo -e "Rulare dynamic Chunk = 16\v" 

gcc -O3  -fopenmp -fdump-tree-all heat_transfer_omp2.cpp `pkg-config opencv --libs --cflags` -lstdc++

for j in {1..10}
do
        echo -e "N_Threads = $j \v" >> final_hpsl_omp2.txt
	echo -e "N_Threads = $j \v"
        for i in {1..2}
        do
                export OMP_NUM_THREADS=$j
		export OMP_SCHEDULE="dynamic,16"
                ./a.out >> final_hpsl_omp2.txt
        done
done

for j in {12..60..2}
do
        echo -e "N_Threads = $j \v" >> final_hpsl_omp2.txt
	echo -e "N_Threads = $j \v"
        for i in {1..2}
        do
                export OMP_NUM_THREADS=$j
		export OMP_SCHEDULE="dynamic,16"
                ./a.out >> final_hpsl_omp2.txt
        done
done


echo -e "Rulare dynamic Chunk = 32\v" >> final_hpsl_omp2.txt
echo -e "Rulare dynamic Chunk = 32\v" 

gcc -O3  -fopenmp -fdump-tree-all heat_transfer_omp2.cpp `pkg-config opencv --libs --cflags` -lstdc++

for j in {1..10}
do
        echo -e "N_Threads = $j \v" >> final_hpsl_omp2.txt
	echo -e "N_Threads = $j \v"
        for i in {1..2}
        do
                export OMP_NUM_THREADS=$j
		export OMP_SCHEDULE="dynamic,32"
                ./a.out >> final_hpsl_omp2.txt
        done
done

for j in {12..60..2}
do
        echo -e "N_Threads = $j \v" >> final_hpsl_omp2.txt
	echo -e "N_Threads = $j \v"
        for i in {1..2}
        do
                export OMP_NUM_THREADS=$j
		export OMP_SCHEDULE="dynamic,32"
                ./a.out >> final_hpsl_omp2.txt
        done
done

echo -e "Rulare dynamic Chunk = 64\v" >> final_hpsl_omp2.txt
echo -e "Rulare dynamic Chunk = 64\v" 

gcc -O3  -fopenmp -fdump-tree-all heat_transfer_omp2.cpp `pkg-config opencv --libs --cflags` -lstdc++

for j in {1..10}
do
        echo -e "N_Threads = $j \v" >> final_hpsl_omp2.txt
	echo -e "N_Threads = $j \v"
        for i in {1..2}
        do
                export OMP_NUM_THREADS=$j
		export OMP_SCHEDULE="dynamic,64"
                ./a.out >> final_hpsl_omp2.txt
        done
done

for j in {12..60..2}
do
        echo -e "N_Threads = $j \v" >> final_hpsl_omp2.txt
	echo -e "N_Threads = $j \v"
        for i in {1..2}
        do
                export OMP_NUM_THREADS=$j
		export OMP_SCHEDULE="dynamic,64"
                ./a.out >> final_hpsl_omp2.txt
        done
done


#!/bin/sh

echo -e "Rulare guided\v" >> final_hpsl_omp2.txt
echo -e "Rulare guided\v" 

gcc -O3  -fopenmp -fdump-tree-all heat_transfer_omp2.cpp `pkg-config opencv --libs --cflags` -lstdc++

for j in {1..10}
do
        echo -e "N_Threads = $j \v" >> final_hpsl_omp2.txt
	echo -e "N_Threads = $j \v"
        for i in {1..2}
        do
                export OMP_NUM_THREADS=$j
		export OMP_SCHEDULE="guided,1"
                ./a.out >> final_hpsl_omp2.txt
        done
done

for j in {12..60..2}
do
        echo -e "N_Threads = $j \v" >> final_hpsl_omp2.txt
	echo -e "N_Threads = $j \v"
        for i in {1..2}
        do
                export OMP_NUM_THREADS=$j
		export OMP_SCHEDULE="guided,1"
                ./a.out >> final_hpsl_omp2.txt
        done
done

echo -e "Rulare guided Chunk = 4\v" >> final_hpsl_omp2.txt
echo -e "Rulare guided Chunk = 4\v" 

gcc -O3  -fopenmp -fdump-tree-all heat_transfer_omp2.cpp `pkg-config opencv --libs --cflags` -lstdc++

for j in {1..10}
do
        echo -e "N_Threads = $j \v" >> final_hpsl_omp2.txt
	echo -e "N_Threads = $j \v"
        for i in {1..2}
        do
                export OMP_NUM_THREADS=$j
		export OMP_SCHEDULE="guided,4"
                ./a.out >> final_hpsl_omp2.txt
        done
done

for j in {12..60..2}
do
        echo -e "N_Threads = $j \v" >> final_hpsl_omp2.txt
	echo -e "N_Threads = $j \v"
        for i in {1..2}
        do
                export OMP_NUM_THREADS=$j
		export OMP_SCHEDULE="guided,4"
                ./a.out >> final_hpsl_omp2.txt
        done
done



echo -e "Rulare guided Chunk = 8\v" >> final_hpsl_omp2.txt
echo -e "Rulare guided Chunk = 8\v" 

gcc -O3  -fopenmp -fdump-tree-all heat_transfer_omp2.cpp `pkg-config opencv --libs --cflags` -lstdc++

for j in {1..10}
do
        echo -e "N_Threads = $j \v" >> final_hpsl_omp2.txt
	echo -e "N_Threads = $j \v"
        for i in {1..2}
        do
                export OMP_NUM_THREADS=$j
		export OMP_SCHEDULE="guided,8"
                ./a.out >> final_hpsl_omp2.txt
        done
done

for j in {12..60..2}
do
        echo -e "N_Threads = $j \v" >> final_hpsl_omp2.txt
	echo -e "N_Threads = $j \v"
        for i in {1..2}
        do
                export OMP_NUM_THREADS=$j
		export OMP_SCHEDULE="guided,8"
                ./a.out >> final_hpsl_omp2.txt
        done
done

echo -e "Rulare guided Chunk = 16\v" >> final_hpsl_omp2.txt
echo -e "Rulare guided Chunk = 16\v" 

gcc -O3  -fopenmp -fdump-tree-all heat_transfer_omp2.cpp `pkg-config opencv --libs --cflags` -lstdc++

for j in {1..10}
do
        echo -e "N_Threads = $j \v" >> final_hpsl_omp2.txt
	echo -e "N_Threads = $j \v"
        for i in {1..2}
        do
                export OMP_NUM_THREADS=$j
		export OMP_SCHEDULE="guided,16"
                ./a.out >> final_hpsl_omp2.txt
        done
done

for j in {12..60..2}
do
        echo -e "N_Threads = $j \v" >> final_hpsl_omp2.txt
	echo -e "N_Threads = $j \v"
        for i in {1..2}
        do
                export OMP_NUM_THREADS=$j
		export OMP_SCHEDULE="guided,16"
                ./a.out >> final_hpsl_omp2.txt
        done
done


echo -e "Rulare guided Chunk = 32\v" >> final_hpsl_omp2.txt
echo -e "Rulare guided Chunk = 32\v" 

gcc -O3  -fopenmp -fdump-tree-all heat_transfer_omp2.cpp `pkg-config opencv --libs --cflags` -lstdc++

for j in {1..10}
do
        echo -e "N_Threads = $j \v" >> final_hpsl_omp2.txt
	echo -e "N_Threads = $j \v"
        for i in {1..2}
        do
                export OMP_NUM_THREADS=$j
		export OMP_SCHEDULE="guided,32"
                ./a.out >> final_hpsl_omp2.txt
        done
done

for j in {12..60..2}
do
        echo -e "N_Threads = $j \v" >> final_hpsl_omp2.txt
	echo -e "N_Threads = $j \v"
        for i in {1..2}
        do
                export OMP_NUM_THREADS=$j
		export OMP_SCHEDULE="guided,32"
                ./a.out >> final_hpsl_omp2.txt
        done
done

echo -e "Rulare guided Chunk = 64\v" >> final_hpsl_omp2.txt
echo -e "Rulare guided Chunk = 64\v" 

gcc -O3  -fopenmp -fdump-tree-all heat_transfer_omp2.cpp `pkg-config opencv --libs --cflags` -lstdc++

for j in {1..10}
do
        echo -e "N_Threads = $j \v" >> final_hpsl_omp2.txt
	echo -e "N_Threads = $j \v"
        for i in {1..2}
        do
                export OMP_NUM_THREADS=$j
		export OMP_SCHEDULE="guided,64"
                ./a.out >> final_hpsl_omp2.txt
        done
done

for j in {12..60..2}
do
        echo -e "N_Threads = $j \v" >> final_hpsl_omp2.txt
	echo -e "N_Threads = $j \v"
        for i in {1..2}
        do
                export OMP_NUM_THREADS=$j
		export OMP_SCHEDULE="guided,64"
                ./a.out >> final_hpsl_omp2.txt
        done
done

echo -e "Rulare guided auto\v" >> final_hpsl_omp2.txt
echo -e "Rulare guided auto\v" 

gcc -O3  -fopenmp -fdump-tree-all heat_transfer_omp2.cpp `pkg-config opencv --libs --cflags` -lstdc++

for j in {1..10}
do
        echo -e "N_Threads = $j \v" >> final_hpsl_omp2.txt
	echo -e "N_Threads = $j \v"
        for i in {1..2}
        do
                export OMP_NUM_THREADS=$j
		export OMP_SCHEDULE="auto"
                ./a.out >> final_hpsl_omp2.txt
        done
done

for j in {12..60..2}
do
        echo -e "N_Threads = $j \v" >> final_hpsl_omp2.txt
	echo -e "N_Threads = $j \v"
        for i in {1..2}
        do
                export OMP_NUM_THREADS=$j
		export OMP_SCHEDULE="auto"
                ./a.out >> final_hpsl_omp2.txt
        done
done