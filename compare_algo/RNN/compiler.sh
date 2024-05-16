#!/bin/bash

# g++ -c ./header/file_operation.cpp -o ./header/file_operation.o
# g++ -c ./header/proposed.cpp -o ./header/proposed.o
# g++ -c ./header/f1_score.cpp -o ./header/f1_score.o
# g++ -c ./RNN.cpp -o ./RNN.o

# g++ -o RNN ./header/file_operation.o ./header/proposed.o ./header/f1_score.o ./RNN.o
# echo "Compile Done"
# echo ""

./RNN ./dataset/abalone/ 0.5 3