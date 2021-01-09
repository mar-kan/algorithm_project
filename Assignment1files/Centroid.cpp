//Kanellaki Maria-Anna - 1115201400060
//Litsas Nikolaos - 1115201400331

#include "Centroid.h"


Centroid::Centroid(unsigned char * vec)
{
    for (int i=0; i < 28*28; i++)
        centroid[i] = vec[i];

    distance = 100000;  //initialized with a big number
}


Centroid::~Centroid()
{
    //nothing to delete manually
}


unsigned char *Centroid::getCentroid() const
{
    return (unsigned char *)centroid;
}


int Centroid::getDistance() const
{
    return distance;
}
