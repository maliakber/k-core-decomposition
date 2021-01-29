# k-core-decomposition
	C++ implementation of the k-core-decompostion algorithm + unit-test
	An O(m) Algorithm for Cores Decomposition of Networks (https://arxiv.org/abs/cs/0310049)

# How to run (using cmake)?
	1. Install cmake (https://cmake.org/install/)
	2. Go to the project folder and open terminal
	3. Run the following commands:
		mkdir build
		cd build
		cmake -DCMAKE_BUILD_TYPE=Release ..
		make
	4. Now run the program:
		./src/k-core -f <graph_file_name.txt>

# How to run (manually using gcc)?
	1. Compile the program:
		g++ -Wall -O3 -std=c++17 -fopenmp -o main main.cpp common/graph.cpp kcore/kcore.cpp
			-Wall: with all warnings
			-O3: compiler optimization
			-std: using c++ standard 17
			-fopenmp: to use openmp parallel library (#pragma)
			-o: output binary name 
	2. Run the program:
		./main -f <graph_file_name.txt>