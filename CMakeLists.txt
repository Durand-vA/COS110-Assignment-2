cmake_minimum_required(VERSION 3.24)
project(Assignment_2)

set(CMAKE_CXX_STANDARD 98)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libstdc++ -static-libgcc")

add_executable(Assignment_2 main.cpp
        bivariate.h
        circle.h
        ellipse.h
        linear.h
        polynomial.h
        quadratic.h
        term.h
        univariate.h
        term.cpp
        polynomial.cpp
        univariate.cpp
        bivariate.cpp
        linear.cpp
        quadratic.cpp
        circle.cpp
        ellipse.cpp)
