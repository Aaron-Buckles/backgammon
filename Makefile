CXXFLAGS=-std=c++11 -Wpedantic -Wall -Wextra -Werror -Weffc++ -Wzero-as-null-pointer-constant

main: main.cpp Backgammon.cpp Dice.cpp
	g++ -g ${CXXFLAGS} main.cpp -o main
