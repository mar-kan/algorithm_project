//Kanellaki Maria-Anna - 1115201400060
//Litsas Nikolaos - 1115201400331

#ifndef CENTROID_H
#define CENTROID_H

#include <list>
#include <cstdio>
#include "../general/ImageData.h"
using namespace std;


class Centroid {                     //represents a centroid for the clustering algorithms

    unsigned char centroid[28*28];   //vector of centroid

    int distance;                    //l1 distance between new and old centroid

public:
    Centroid(unsigned char *);
    ~Centroid();

    unsigned char * getCentroid() const;
    int getDistance() const;
};


#endif
