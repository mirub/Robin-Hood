build: p1 p2 p3

p1: p1.cpp
	g++ -std=c++17 -Wall -Wextra p1.cpp -o p1

p2: p2.cpp
	g++ -std=c++17 -Wall -Wextra p2.cpp -o p2

p3: p3.cpp
	g++ -std=c++17 -Wall -Wextra p3.cpp -o p3

run-p1:
	./p1

run-p2:
	./p2

run-p3:
	./p3

clean:
	rm -rf p1 p2 p3