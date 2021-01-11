cmake_minimum_required(VERSION 3.17)
project(project3)

set(CMAKE_CXX_STANDARD 14)


add_executable(
        lsh
        Assignment1files/LSH.h Assignment1files/LSH.cpp
        Assignment1files/LSHashFunction.cpp Assignment1files/LSHashFunction.h
        B/lshMain.cpp
        B/lshMainUtils.cpp B/lshMainUtils.h
        Assignment1files/NearestNeighbour.cpp Assignment1files/NearestNeighbour.h
        Assignment1files/general/Dataset.cpp Assignment1files/general/Dataset.h
        Assignment1files/general/ImageData.cpp Assignment1files/general/ImageData.h
        Assignment1files/general/distance.cpp Assignment1files/general/distance.h
        Assignment1files/general/functions.cpp Assignment1files/general/functions.cpp
        Assignment1files/general/HashTable.cpp Assignment1files/general/HashTable.h
        Assignment1files/Algorithm.cpp Assignment1files/Algorithm.h
        Assignment1files/Centroid.cpp Assignment1files/Centroid.h
        Assignment1files/CubeHashFunction.h Assignment1files/CubeHashFunction.cpp
        Assignment1files/Hypercube.h Assignment1files/Hypercube.cpp
        )