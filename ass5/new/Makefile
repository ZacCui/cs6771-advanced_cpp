all: sortTester benchmark

sortTester : sortTester.o BucketSort.o
	g++ -std=c++14 -Wall -Werror -pg -O2 -pthread -o sortTester sortTester.o BucketSort.o

sortTester.o: sortTester.cpp BucketSort.h
	g++ -std=c++14 -Wall -Werror -O2 -pthread -c sortTester.cpp

benchmark : benchmark.o BucketSort.o
	g++ -std=c++14 -Wall -Werror -O2 -pthread -o benchmark benchmark.o BucketSort.o

benchmark.o: benchmark.cpp BucketSort.h
	g++ -std=c++14 -Wall -Werror -O2 -pthread -c benchmark.cpp

BucketSort.o : BucketSort.h BucketSort.cpp
	g++ -std=c++14 -Wall -Werror -O2 -pthread -c BucketSort.cpp

clean:
	rm *.o sortTester benchmark
