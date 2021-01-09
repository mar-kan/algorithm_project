//Kanellaki Maria-Anna - 1115201400060
//Litsas Nikolaos - 1115201400331

#ifndef ALGORITHM_H
#define ALGORITHM_H


#include "general/HashTable.h"
#include "general/Dataset.h"
#include "Centroid.h"

class Algorithm {

    string method;
    int num_clusters;

public:
    Algorithm(int);
    virtual ~Algorithm() = default;

    void executeAlgorithm(Dataset*);
    void initialization(int);
    //void assignment(ImageData*);  happens in subclasses

    void printClustersToFile(FILE *);
    virtual void addCentroidToBucket(Centroid*, int) {};

    void setMethod(const string &method);
    void setNumClusters(int numClusters);

    const string &getMethod() const;
};


#endif
