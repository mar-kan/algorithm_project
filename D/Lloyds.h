//Kanellaki Maria-Anna - 1115201400060
//Litsas Nikolaos - 1115201400331

#ifndef LLOYDS_H
#define LLOYDS_H

#include "Algorithm.h"
#include "Centroid.h"
#include "../general/functions.h"

class Lloyds: public Algorithm {

    HashTable * hashTable;           //hash table that stores tha data, has size k and each bucket represents a centroid
    int num_clusters;                //number of clusters used in the execution of the algorithm

public:
    Lloyds(int k);
    ~Lloyds();

    void reassignToCentroids();
    void calculateMean(int*,int*);
    void updateCentroids();
    void executeAlgorithm();

    void addCentroidToBucket(Centroid*, int);
    void assignment(ImageData*);

    float getMaxCentroidDifference();
};


#endif
