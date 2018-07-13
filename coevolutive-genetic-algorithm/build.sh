#!\bin\bash

if [ ! -d "bin" ]; then
  mkdir bin
fi

g++ scrollRule2.cpp -o ./bin/scrollRule2 -std=c++14 -O3
g++ scrollRule3.cpp -o ./bin/scrollRule3 -std=c++14
g++ main_etapa1.cpp -o ./bin/main_etapa1 -std=c++14 -O3
g++ main_etapa2.cpp -o ./bin/main_etapa2 -std=c++14 -O3
g++ final_evaluation_r2.cpp -o ./bin/final_evaluation_r2 -std=c++14 -O3
g++ final_evaluation_r3.cpp -o ./bin/final_evaluation_r3 -std=c++14
