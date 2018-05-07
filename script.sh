g++ -std=c++11 -c *.cpp;
g++ main.o grid.o environment.o agent.o filewriter.o -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system;
