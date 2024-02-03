CXXFLAGS=-std=c++20 -Wall -Wextra -Wshadow

sol: sol.cpp
	g++ $(CXXFLAGS) -fsanitize=address,undefined -g -DLOCAL sol.cpp -o sol 

fast: sol.cpp
	g++ $(CXXFLAGS) -O2 sol.cpp -o fast
