CC=g++
CFLAGS=-Wall -std=c++11 -O3 -g3 -pg -std=c++0x

all: search LSH.so LSHashFunction.so NearestNeighbour.so HashTable.so Distance.so ImageData.so Dataset.so Algorithm.so Hypercube.so Centroid.so SearchLib.so

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


# create shared libraries for python (C)
LSH.so: LSH.o
	$(CC) Assignment1files/LSH.cpp -o LSH.so -fPIC -shared

LSHashFunction.so: LSHashFunction.o
	$(CC) Assignment1files/LSHashFunction.cpp -o LSHashFunction.so -fPIC -shared

NearestNeighbour.so: NearestNeighbour.o
	$(CC) Assignment1files/NearestNeighbour.cpp -o NN.so -fPIC -shared

HashTable.so: HashTable.o
	$(CC) Assignment1files/general/HashTable.cpp -o HashTable.so -fPIC -shared

Dataset.so: Dataset.o
	$(CC) Assignment1files/general/Dataset.cpp -o Dataset.so -fPIC -shared

Distance.so: distance.o
	$(CC) Assignment1files/general/distance.cpp -o Distance.so -fPIC -shared

ImageData.so: ImageData.o
	$(CC) Assignment1files/general/ImageData.cpp -o ImageData.so -fPIC -shared

Algorithm.so: Algorithm.o
	$(CC) Assignment1files/Algorithm.cpp -o Algorithm.so -fPIC -shared

Hypercube.so: Hypercube.o
	$(CC) Assignment1files/Hypercube.cpp -o Hypercube.so -fPIC -shared

Centroid.so: Centroid.o
	$(CC) Assignment1files/Centroid.cpp -o Centroid.so -fPIC -shared

CubeHashFunction.so: CubeHashFunction.o
	$(CC) Assignment1files/CubeHashFunction.cpp -o CubeHashFunction.so -fPIC -shared

SearchLib.so: LSH.o lshMainUtils.o LSHashFunction.o NearestNeighbour.o HashTable.o Dataset.o distance.o functions.o ImageData.o Algorithm.o Hypercube.o Centroid.o CubeHashFunction.o
	$(CC) Assignment1files/LSH.cpp B/lshMainUtils.cpp Assignment1files/LSHashFunction.cpp Assignment1files/NearestNeighbour.cpp Assignment1files/general/HashTable.cpp Assignment1files/general/Dataset.cpp Assignment1files/general/distance.cpp Assignment1files/general/functions.cpp Assignment1files/general/ImageData.cpp Assignment1files/Algorithm.cpp Assignment1files/Hypercube.cpp Assignment1files/Centroid.cpp Assignment1files/CubeHashFunction.cpp -o SearchLib.so -fPIC -shared

.PHONY: clean

clean:
	rm -f lsh *.o *.so
