CC=g++
CFLAGS=-Wall -std=c++11 -O3 -g3 -pg -std=c++0x

all: lsh cube cluster

lsh: B/lshMain.o B/LSH.o B/lshMainUtils.o B/LSHashFunction.o B/NearestNeighbour.o general/HashTable.o general/Dataset.o general/distance.o general/functions.o general/ImageData.o D/Algorithm.o B/Hypercube.o D/Centroid.o B/CubeHashFunction.o
	$(CC) -o lsh lshMain.o LSH.o lshMainUtils.o LSHashFunction.o NearestNeighbour.o HashTable.o Dataset.o distance.o functions.o ImageData.o Algorithm.o Hypercube.o Centroid.o CubeHashFunction.o $(CFLAGS)

cube: B/cubeMain.o B/cubeMainUtils.o B/Hypercube.o B/LSHashFunction.o B/NearestNeighbour.o general/HashTable.o general/Dataset.o general/distance.o general/functions.o general/ImageData.o D/Algorithm.o B/LSH.o D/Centroid.o B/CubeHashFunction.o
	$(CC) -o cube cubeMain.o cubeMainUtils.o Hypercube.o LSHashFunction.o NearestNeighbour.o HashTable.o Dataset.o distance.o functions.o ImageData.o Algorithm.o LSH.o Centroid.o CubeHashFunction.o $(CFLAGS)

cluster: D/clusterMain.o D/Algorithm.o D/Centroid.o D/Cluster.o D/clusterMainUtils.o D/Lloyds.o D/Silhouette.o general/HashTable.o general/Dataset.o general/distance.o general/functions.o general/ImageData.o B/LSH.o B/Hypercube.o B/CubeHashFunction.o B/LSHashFunction.o
	$(CC) $(CFLAGS) -o cluster clusterMain.o Algorithm.o Centroid.o Cluster.o clusterMainUtils.o Lloyds.o Silhouette.o HashTable.o Dataset.o distance.o functions.o ImageData.o LSH.o Hypercube.o CubeHashFunction.o LSHashFunction.o $(CFLAGS)

B/lshMain.o: B/lshMain.cpp
	$(CC) $(CFLAGS) -c B/lshMain.cpp

B/LSH.o: B/LSH.cpp
	$(CC) $(CFLAGS) -c B/LSH.cpp

B/lshMainUtils.o: B/lshMainUtils.cpp
	$(CC) $(CFLAGS) -c B/lshMainUtils.cpp

B/LSHashFunction.o: B/LSHashFunction.cpp
	$(CC) $(CFLAGS) -c B/LSHashFunction.cpp

B/NearestNeighbour.o: B/NearestNeighbour.cpp
	$(CC) $(CFLAGS) -c B/NearestNeighbour.cpp

B/cubeMain.o: B/cubeMain.cpp
	$(CC) $(CFLAGS) -c B/cubeMain.cpp

B/cubeMainUtils.o: B/cubeMainUtils.cpp
	$(CC) $(CFLAGS) -c B/cubeMainUtils.cpp

B/Hypercube.o: B/Hypercube.cpp
	$(CC) $(CFLAGS) -c B/Hypercube.cpp

B/CubeHashFunction.o: B/CubeHashFunction.cpp
	$(CC) $(CFLAGS) -c B/CubeHashFunction.cpp

D/clusterMain.o: D/clusterMain.cpp
	$(CC) $(CFLAGS) -c D/clusterMain.cpp

D/Algorithm.o: D/Algorithm.cpp
	$(CC) $(CFLAGS) -c D/Algorithm.cpp

D/Centroid.o: D/Centroid.cpp
	$(CC) $(CFLAGS) -c D/Centroid.cpp

D/Cluster.o: D/Cluster.cpp
	$(CC) $(CFLAGS) -c D/Cluster.cpp

D/clusterMainUtils.o: D/clusterMainUtils.cpp
	$(CC) $(CFLAGS) -c D/clusterMainUtils.cpp

D/Lloyds.o: D/Lloyds.cpp
	$(CC) $(CFLAGS) -c D/Lloyds.cpp

D/Silhouette.o: D/Silhouette.cpp
	$(CC) $(CFLAGS) -c D/Silhouette.cpp

general/HashTable.o: general/HashTable.cpp
	$(CC) $(CFLAGS) -c general/HashTable.cpp

general/Dataset.o: general/Dataset.cpp
	$(CC) $(CFLAGS) -c general/Dataset.cpp

general/distance.o: general/distance.cpp
	$(CC) $(CFLAGS) -c general/distance.cpp

general/functions.o: general/functions.cpp
	$(CC) $(CFLAGS) -c general/functions.cpp

general/ImageData.o: general/ImageData.cpp
	$(CC) $(CFLAGS) -c general/ImageData.cpp

.PHONY: clean

clean:
	rm -f lsh cube cluster *.o B/*.o D/*.o general/*.o
