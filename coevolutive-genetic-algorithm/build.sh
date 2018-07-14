#!\bin\bash

if [ ! -d "bin" ]; then
  mkdir bin
fi

g++ scrollRule2.cpp -o ./bin/scrollRule2 -std=c++14 -O3
g++ scrollRule3.cpp -o ./bin/scrollRule3 -std=c++14
g++ final_evaluation_r2.cpp -o ./bin/final_evaluation_r2 -std=c++14 -O3
g++ final_evaluation_r3.cpp -o ./bin/final_evaluation_r3 -std=c++14
g++ main.cpp -o ./bin/main -std=c++14 -O3
