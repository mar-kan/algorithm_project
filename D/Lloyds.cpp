//Kanellaki Maria-Anna - 1115201400060
//Litsas Nikolaos - 1115201400331

#include "Lloyds.h"
#define THRESHOLD 1.5

Lloyds::Lloyds(int k): Algorithm(k)     //initializes lloyd's algorithm with an empty list of centroids and the number of clusters
{
    hashTable = new HashTable(k);
    num_clusters = k;
}


Lloyds::~Lloyds()                       //deletes list of centroids
{
    delete hashTable;
}


void Lloyds::reassignToCentroids()      //reassigns all images of the centroids' list to a new centroid
{

}


void Lloyds::calculateMean(int* x, int *y)
{

}


void Lloyds::updateCentroids()
{
    for (int i=0; i<num_clusters; i++)
    {
        //kapws bres to group
        //new center = calculateMean();
    }
}


void Lloyds::executeAlgorithm()         //executes lloyd's algorithm
{
    while (getMaxCentroidDifference() > THRESHOLD)      //algorithm executes until all differences are below the threshold
    {
        reassignToCentroids();
        updateCentroids();
    }
}


void Lloyds::addCentroidToBucket(Centroid * centroid, int buck_pos)  //adds centroid to pos-th bucket of hash table
{
    hashTable->getBucket(buck_pos)->setMyCentroid(centroid);
}


void Lloyds::assignment(ImageData *image)          //assigns image to hash table
{
    hashTable->AssignInTableCluster(image);
}


float Lloyds::getMaxCentroidDifference()    //returns max difference between new and old centroids of the list
{
    float max=0.0;
    list<Centroid*>::iterator it;
    /*for (it=centroids->begin(); it!=centroids->end(); it++)
    {
        if ((*it)->getDiffX() > max)
            max = (*it)->getDiffX();
    }*/
    return max;
}