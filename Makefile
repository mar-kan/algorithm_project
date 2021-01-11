CC=g++
CFLAGS=-Wall -std=c++11 -O3 -g3 -pg -std=c++0x

all: search

search: lshMain.o LSH.o lshMainUtils.o LSHashFunction.o NearestNeighbour.o HashTable.o Dataset.o distance.o functions.o ImageData.o Algorithm.o Hypercube.o Centroid.o CubeHashFunction.o
	$(CC) -o lsh lshMain.o LSH.o lshMainUtils.o LSHashFunction.o NearestNeighbour.o HashTable.o Dataset.o distance.o functions.o ImageData.o Algorithm.o Hypercube.o Centroid.o CubeHashFunction.o $(CFLAGS)

#cluster: D/clusterMain.o D/Algorithm.o D/Centroid.o D/Cluster.o D/clusterMainUtils.o D/Lloyds.o D/Silhouette.o general/HashTable.o general/Dataset.o general/distance.o general/functions.o general/ImageData.o B/LSH.o B/Hypercube.o B/CubeHashFunction.o B/LSHashFunction.o
#	$(CC) $(CFLAGS) -o cluster clusterMain.o Algorithm.o Centroid.o Cluster.o clusterMainUtils.o Lloyds.o Silhouette.o HashTable.o Dataset.o distance.o functions.o ImageData.o LSH.o Hypercube.o CubeHashFunction.o LSHashFunction.o $(CFLAGS)

lshMain.o: B/lshMain.cpp
	$(CC) $(CFLAGS) -c B/lshMain.cpp

LSH.o: Assignment1files/LSH.cpp
	$(CC) $(CFLAGS) -c Assignment1files/LSH.cpp

lshMainUtils.o: B/lshMainUtils.cpp
	$(CC) $(CFLAGS) -c B/lshMainUtils.cpp

LSHashFunction.o: Assignment1files/LSHashFunction.cpp
	$(CC) $(CFLAGS) -c Assignment1files/LSHashFunction.cpp

NearestNeighbour.o: Assignment1files/NearestNeighbour.cpp
	$(CC) $(CFLAGS) -c Assignment1files/NearestNeighbour.cpp

cubeMainUtils.o: Assignment1files/cubeMainUtils.cpp
	$(CC) $(CFLAGS) -c Assignment1files/cubeMainUtils.cpp

Hypercube.o: Assignment1files/Hypercube.cpp
	$(CC) $(CFLAGS) -c Assignment1files/Hypercube.cpp

CubeHashFunction.o: Assignment1files/CubeHashFunction.cpp
	$(CC) $(CFLAGS) -c Assignment1files/CubeHashFunction.cpp

clusterMain.o: Assignment1files/clusterMain.cpp
	$(CC) $(CFLAGS) -c Assignment1files/clusterMain.cpp

Algorithm.o: Assignment1files/Algorithm.cpp
	$(CC) $(CFLAGS) -c Assignment1files/Algorithm.cpp

Centroid.o: Assignment1files/Centroid.cpp
	$(CC) $(CFLAGS) -c Assignment1files/Centroid.cpp

Cluster.o: Assignment1files/Cluster.cpp
	$(CC) $(CFLAGS) -c Assignment1files/Cluster.cpp

clusterMainUtils.o: Assignment1files/clusterMainUtils.cpp
	$(CC) $(CFLAGS) -c Assignment1files/clusterMainUtils.cpp

Lloyds.o: Assignment1files/Lloyds.cpp
	$(CC) $(CFLAGS) -c Assignment1files/Lloyds.cpp

Silhouette.o: Assignment1files/Silhouette.cpp
	$(CC) $(CFLAGS) -c Assignment1files/Silhouette.cpp

HashTable.o: Assignment1files/general/HashTable.cpp
	$(CC) $(CFLAGS) -c Assignment1files/general/HashTable.cpp

Dataset.o: Assignment1files/general/Dataset.cpp
	$(CC) $(CFLAGS) -c Assignment1files/general/Dataset.cpp

distance.o: Assignment1files/general/distance.cpp
	$(CC) $(CFLAGS) -c Assignment1files/general/distance.cpp

functions.o: Assignment1files/general/functions.cpp
	$(CC) $(CFLAGS) -c Assignment1files/general/functions.cpp

ImageData.o: Assignment1files/general/ImageData.cpp
	$(CC) $(CFLAGS) -c Assignment1files/general/ImageData.cpp

.PHONY: clean

clean:
	rm -f search *.o *.so
