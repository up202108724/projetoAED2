cmake_minimum_required(VERSION 3.24)
project(projetoAED2)

set(CMAKE_CXX_STANDARD 17)

add_executable(projetoAED2 main.cpp GestaoAeroporto.cpp GestaoAeroporto.h CompanhiaAerea.h CompanhiaAerea.cpp Aeroportos.cpp Aeroportos.h)
