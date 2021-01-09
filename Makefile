CC=g++
CFLAGS=-Wall -std=c++11 -O3 -g3 -pg -std=c++0x

all: search search.so

search: B/lshMain.o B/LSH.o B/lshMainUtils.o B/LSHashFunction.o B/NearestNeighbour.o general/HashTable.o general/Dataset.o general/distance.o general/functions.o general/ImageData.o D/Algorithm.o B/Hypercube.o D/Centroid.o B/CubeHashFunction.o
	$(CC) -o lsh lshMain.o LSH.o lshMainUtils.o LSHashFunction.o NearestNeighbour.o HashTable.o Dataset.o distance.o functions.o ImageData.o Algorithm.o Hypercube.o Centroid.o CubeHashFunction.o $(CFLAGS)

cluster: D/clusterMain.o D/Algorithm.o D/Centroid.o D/Cluster.o D/clusterMainUtils.o D/Lloyds.o D/Silhouette.o general/HashTable.o general/Dataset.o general/distance.o general/functions.o general/ImageData.o B/LSH.o B/Hypercube.o B/CubeHashFunction.o B/LSHashFunction.o
	$(CC) $(CFLAGS) -o cluster clusterMain.o Algorithm.o Centroid.o Cluster.o clusterMainUtils.o Lloyds.o Silhouette.o HashTable.o Dataset.o distance.o functions.o ImageData.o LSH.o Hypercube.o CubeHashFunction.o LSHashFunction.o $(CFLAGS)

B/lshMain.o: B/lshMain.cpp
	$(CC) $(CFLAGS) -c B/lshMain.cpp

B/LSH.o: Assignment1files/LSH.cpp
	$(CC) $(CFLAGS) -c Assignment1files/LSH.cpp

B/lshMainUtils.o: B/lshMainUtils.cpp
	$(CC) $(CFLAGS) -c B/lshMainUtils.cpp

B/LSHashFunction.o: Assignment1files/LSHashFunction.cpp
	$(CC) $(CFLAGS) -c Assignment1files/LSHashFunction.cpp

B/NearestNeighbour.o: Assignment1files/NearestNeighbour.cpp
	$(CC) $(CFLAGS) -c Assignment1files/NearestNeighbour.cpp

B/cubeMainUtils.o: Assignment1files/cubeMainUtils.cpp
	$(CC) $(CFLAGS) -c Assignment1files/cubeMainUtils.cpp

B/Hypercube.o: Assignment1files/Hypercube.cpp
	$(CC) $(CFLAGS) -c Assignment1files/Hypercube.cpp

B/CubeHashFunction.o: Assignment1files/CubeHashFunction.cpp
	$(CC) $(CFLAGS) -c Assignment1files/CubeHashFunction.cpp

D/clusterMain.o: Assignment1files/clusterMain.cpp
	$(CC) $(CFLAGS) -c Assignment1files/clusterMain.cpp

D/Algorithm.o: Assignment1files/Algorithm.cpp
	$(CC) $(CFLAGS) -c Assignment1files/Algorithm.cpp

D/Centroid.o: Assignment1files/Centroid.cpp
	$(CC) $(CFLAGS) -c Assignment1files/Centroid.cpp

D/Cluster.o: Assignment1files/Cluster.cpp
	$(CC) $(CFLAGS) -c Assignment1files/Cluster.cpp

D/clusterMainUtils.o: Assignment1files/clusterMainUtils.cpp
	$(CC) $(CFLAGS) -c Assignment1files/clusterMainUtils.cpp

D/Lloyds.o: Assignment1files/Lloyds.cpp
	$(CC) $(CFLAGS) -c Assignment1files/Lloyds.cpp

D/Silhouette.o: Assignment1files/Silhouette.cpp
	$(CC) $(CFLAGS) -c Assignment1files/Silhouette.cpp

general/HashTable.o: Assignment1files/general/HashTable.cpp
	$(CC) $(CFLAGS) -c Assignment1files/general/HashTable.cpp

general/Dataset.o: Assignment1files/general/Dataset.cpp
	$(CC) $(CFLAGS) -c Assignment1files/general/Dataset.cpp

general/distance.o: Assignment1files/general/distance.cpp
	$(CC) $(CFLAGS) -c Assignment1files/general/distance.cpp

general/functions.o: Assignment1files/general/functions.cpp
	$(CC) $(CFLAGS) -c Assignment1files/general/functions.cpp

general/ImageData.o: Assignment1files/general/ImageData.cpp
	$(CC) $(CFLAGS) -c Assignment1files/general/ImageData.cpp



# create static libraries for python
search.so: LSH.o lshMainUtils.o LSHashFunction.o NearestNeighbour.o HashTable.o Dataset.o distance.o functions.o ImageData.o Algorithm.o Hypercube.o Centroid.o CubeHashFunction.o
	$(CC) Assignment1files/LSH.cpp B/lshMainUtils.cpp Assignment1files/LSHashFunction.cpp Assignment1files/NearestNeighbour.cpp Assignment1files/general/HashTable.cpp Assignment1files/general/Dataset.cpp Assignment1files/general/distance.cpp Assignment1files/general/functions.cpp Assignment1files/general/ImageData.cpp Assignment1files/Algorithm.cpp Assignment1files/Hypercube.cpp Assignment1files/Centroid.cpp Assignment1files/CubeHashFunction.cpp -o search.so -fPIC -shared


#g++ -c -fPIC foo.cpp -o foo.o
#g++ -shared -Wl,-soname,libfoo.so -o libfoo.so  foo.o


.PHONY: clean

clean:
	rm -f lsh *.o #*.so
