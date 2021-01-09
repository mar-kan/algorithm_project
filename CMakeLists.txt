cmake_minimum_required(VERSION 3.17)
project(project3)

set(CMAKE_CXX_STANDARD 14)


add_executable(
        lsh
        B/LSH.h B/LSH.cpp
        B/LSHashFunction.cpp B/LSHashFunction.h
        B/lshMain.cpp
        B/lshMainUtils.cpp B/lshMainUtils.h
        B/NearestNeighbour.cpp B/NearestNeighbour.h
        general/Dataset.cpp general/Dataset.h
        general/ImageData.cpp general/ImageData.h
        general/distance.cpp general/distance.h
        general/functions.cpp general/functions.cpp
        general/HashTable.cpp general/HashTable.h
        D/Algorithm.cpp D/Algorithm.h
        D/Centroid.cpp D/Centroid.h
        B/CubeHashFunction.h B/CubeHashFunction.cpp
        B/Hypercube.h B/Hypercube.cpp
)