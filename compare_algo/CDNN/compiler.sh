#!/bin/bash

# g++ -c ./header/knn_heap.cpp -o ./header/knn_heap.o
# g++ -c ./header/file_operation.cpp -o ./header/file_operation.o
# g++ -c ./header/proposed.cpp -o ./header/proposed.o
# g++ -c ./header/f1_score.cpp -o ./header/f1_score.o
# g++ -c ./CDNN.cpp -o ./CDNN.o

# g++ -o CDNN ./header/knn_heap.o ./header/file_operation.o ./header/proposed.o ./header/f1_score.o ./CDNN.o
# echo "Compile Done"
# echo ""

./CDNN ./dataset/abalone/ 24 3