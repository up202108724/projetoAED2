cmake_minimum_required(VERSION 3.23)
project(projetoAED2)

set(CMAKE_CXX_STANDARD 17)

add_executable(projetoAED2 main.cpp GestaoAeroporto.cpp GestaoAeroporto.h CompanhiaAerea.h CompanhiaAerea.cpp Aeroporto.cpp Aeroporto.h Aeroporto.cpp Voo.cpp Voo.h )
